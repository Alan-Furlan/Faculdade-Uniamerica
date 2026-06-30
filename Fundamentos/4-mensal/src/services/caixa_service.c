#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "../models/sistema.h"
#include "../utils/utils.h"
#include "caixa_service.h"

void abrirCaixa(GtkButton *button, gpointer user_data) {
    Sistema *sistema = user_data;

    if (sistema->caixaAberto == 1) return;

    GtkWidget *input = GTK_WIDGET(gtk_builder_get_object(sistema->gtk->builder, "entry_valor_caixa"));
    sistema->valorInicialCaixa = atof(gtk_entry_get_text(GTK_ENTRY(input)));
    sistema->caixaAberto = 1;

    GtkStyleContext *statusInd = gtk_widget_get_style_context(sistema->gtk->status_indicator);
    gtk_style_context_add_class(statusInd, "status-caixa-aberto");
    gtk_style_context_remove_class(statusInd, "status-caixa-fechado");
    gtk_label_set_text(sistema->gtk->lbl_status_caixa, "CAIXA ABERTO");

    printf("Aberto com R$ %.2f\n", sistema->valorInicialCaixa);
}

void abrirModalFecharCaixa(GtkButton *button, gpointer user_data) {
    Sistema *sistema = user_data;

    if (sistema->caixaAberto == 0) return;

    gtk_window_set_transient_for(GTK_WINDOW(sistema->gtk->dialog_fechamento), GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))));

    double total_caixa = sistema->valorInicialCaixa + sistema->caixa_faturamento_acumulado;

    char str_inicial[64], str_bruto[64], str_total[64], linha[128], markup_total[128];
    formatarMoeda(str_inicial, sizeof(str_inicial), sistema->valorInicialCaixa);
    formatarMoeda(str_bruto, sizeof(str_bruto),   sistema->caixa_faturamento_acumulado);
    formatarMoeda(str_total, sizeof(str_total), total_caixa);

    snprintf(linha, sizeof(linha), "Valor Inicial: %s", str_inicial);
    gtk_label_set_text(GTK_LABEL(sistema->gtk->lbl_inicial), linha);

    snprintf(linha, sizeof(linha), "Faturamento Bruto: %s", str_bruto);
    gtk_label_set_text(GTK_LABEL(sistema->gtk->lbl_bruto), linha);

    snprintf(markup_total, sizeof(markup_total), "<span weight='bold' foreground='#2E7D32'>Total em Caixa: %s</span>", str_total);
    gtk_label_set_markup(GTK_LABEL(sistema->gtk->lbl_total), markup_total);

    gtk_widget_show_all(sistema->gtk->dialog_fechamento);

    if (gtk_dialog_run(GTK_DIALOG(sistema->gtk->dialog_fechamento)) == GTK_RESPONSE_ACCEPT) {
        
        sistema->caixaAberto = 0;
        sistema->valorInicialCaixa = 0.0;
        sistema->caixa_faturamento_acumulado = 0.0;
        sistema->caixa_qtd_itens_vendidos = 0;

        if (sistema->gtk->liststore_produtos_vendidos)
            gtk_list_store_clear(sistema->gtk->liststore_produtos_vendidos);
        
        gtk_label_set_text(sistema->gtk->lbl_qtd_total_produtos, "0");
        gtk_label_set_text(sistema->gtk->lbl_faturamento_total_produtos, "R$ 0,00");

        GtkStyleContext *ctx = gtk_widget_get_style_context(sistema->gtk->status_indicator);
        gtk_style_context_remove_class(ctx, "status-caixa-aberto");
        gtk_style_context_add_class(ctx, "status-caixa-fechado");
        gtk_label_set_text(sistema->gtk->lbl_status_caixa, "CAIXA FECHADO");
    }

    gtk_widget_hide(sistema->gtk->dialog_fechamento);
}