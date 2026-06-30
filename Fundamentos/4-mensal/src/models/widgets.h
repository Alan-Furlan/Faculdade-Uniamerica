#ifndef WIDGETS_H
#define WIDGETS_H

#include <gtk/gtk.h>

typedef struct {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkCssProvider *css_provider;
    GdkScreen *screen;
    GError *error;
    GtkStack *pag_dashboard;

    GtkWidget *btn_cadastrar_produto;
    GtkWidget *btn_abrir_pg_caixa;
    GtkWidget *btn_vender_produto;
    GtkWidget *btn_pg_relatorio_vendas;
    GtkWidget *btn_produtos_vendidos;
    GtkWidget *btn_sair;

    GtkWidget *btn_salvar_produto;
    GtkWidget *btn_abrir_caixa;
    GtkWidget *btn_fechar_caixa;
    GtkWidget *btn_add_carrinho;
    GtkWidget *btn_finalizar_prod;

    GtkWidget *status_indicator;
    GtkLabel  *lbl_status_caixa;

    GtkListStore *list_store;
    GtkListStore *liststore_carrinho;
    GtkListStore *liststore_produtos_vendidos;
    GtkListStore *liststore_relatorio;

    GtkLabel  *lbl_qtd_total_produtos;
    GtkLabel  *lbl_faturamento_total_produtos;
    GtkWidget *lblTotalComp;

    GtkWidget *dialog_fechamento;
    GtkWidget *lbl_inicial;
    GtkWidget *lbl_bruto;
    GtkWidget *lbl_total;
} Widgets;

#endif
