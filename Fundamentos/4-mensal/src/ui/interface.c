#include <stdio.h>
#include <gtk/gtk.h>
#include "../models/sistema.h"
#include "../services/produto_service.h"
#include "../services/venda_service.h"
#include "../services/caixa_service.h"
#include "navigation.h"
#include "interface.h"

static void conectarEventos(Sistema *sistema) {
    Widgets *w = sistema->gtk;

    g_signal_connect(w->btn_cadastrar_produto, "clicked", G_CALLBACK(pgCadastrarProduto), sistema);
    g_signal_connect(w->btn_abrir_pg_caixa, "clicked", G_CALLBACK(pgAbrirCaixa), sistema);
    g_signal_connect(w->btn_vender_produto, "clicked", G_CALLBACK(pgVenderProduto), sistema);
    g_signal_connect(w->btn_pg_relatorio_vendas, "clicked", G_CALLBACK(pgRelatorioVendas), sistema);
    g_signal_connect(w->btn_produtos_vendidos, "clicked", G_CALLBACK(pgProdutosVendidos), sistema);

    g_signal_connect(w->btn_salvar_produto, "clicked", G_CALLBACK(cadastrarProduto), sistema);
    g_signal_connect(w->btn_abrir_caixa, "clicked", G_CALLBACK(abrirCaixa), sistema);
    g_signal_connect(w->btn_fechar_caixa, "clicked", G_CALLBACK(abrirModalFecharCaixa), sistema);
    g_signal_connect(w->btn_add_carrinho, "clicked", G_CALLBACK(adicionarProdutoCarrinho), sistema);
    g_signal_connect(w->btn_finalizar_prod, "clicked", G_CALLBACK(finalizarVenda), sistema);

    g_signal_connect(w->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(w->btn_sair, "clicked", G_CALLBACK(gtk_main_quit), NULL);
}

static void carregarWidgets(Sistema *sistema) {
    Widgets *w = sistema->gtk;
    GtkBuilder *bld = w->builder;

    w->window = GTK_WIDGET(gtk_builder_get_object(bld, "menu_principal_window"));
    w->pag_dashboard = GTK_STACK(gtk_builder_get_object(bld,  "main_stack"));

    w->btn_cadastrar_produto = GTK_WIDGET(gtk_builder_get_object(bld, "btn_cadastrar_produto"));
    w->btn_abrir_pg_caixa = GTK_WIDGET(gtk_builder_get_object(bld, "btn_abrir_pg_caixa"));
    w->btn_vender_produto = GTK_WIDGET(gtk_builder_get_object(bld, "btn_abrir_pg_vender_produto"));
    w->btn_pg_relatorio_vendas = GTK_WIDGET(gtk_builder_get_object(bld, "btn_pg_relatorio_vendas"));
    w->btn_produtos_vendidos = GTK_WIDGET(gtk_builder_get_object(bld, "btn_produtos_vendidos"));
    w->btn_sair = GTK_WIDGET(gtk_builder_get_object(bld, "btn_sair"));

    w->btn_salvar_produto = GTK_WIDGET(gtk_builder_get_object(bld, "btn_salvar_produto"));
    w->btn_abrir_caixa = GTK_WIDGET(gtk_builder_get_object(bld, "btn_abrir_caixa"));
    w->btn_fechar_caixa = GTK_WIDGET(gtk_builder_get_object(bld, "btn_fechar_caixa"));
    w->btn_add_carrinho = GTK_WIDGET(gtk_builder_get_object(bld, "btn_add_carrinho"));
    w->btn_finalizar_prod = GTK_WIDGET(gtk_builder_get_object(bld, "btn_finalizar_prod"));

    w->status_indicator = GTK_WIDGET(gtk_builder_get_object(bld, "status_indicator"));
    w->lbl_status_caixa = GTK_LABEL(gtk_builder_get_object(bld, "lbl_status_caixa"));

    w->list_store = GTK_LIST_STORE(gtk_builder_get_object(bld, "liststore_produtos"));
    w->liststore_carrinho = GTK_LIST_STORE(gtk_builder_get_object(bld, "liststore_carrinho"));
    w->liststore_produtos_vendidos = GTK_LIST_STORE(gtk_builder_get_object(bld,"liststore_produtos_vendidos"));
    w->liststore_relatorio = GTK_LIST_STORE(gtk_builder_get_object(bld, "liststore_relatorio"));

    w->lbl_qtd_total_produtos = GTK_LABEL(gtk_builder_get_object(bld, "lbl_qtd_total_produtos"));
    w->lbl_faturamento_total_produtos = GTK_LABEL(gtk_builder_get_object(bld, "lbl_faturamento_total_produtos"));
    w->lblTotalComp = GTK_WIDGET(gtk_builder_get_object(bld, "label_total_compra"));

    w->dialog_fechamento = GTK_WIDGET(gtk_builder_get_object(bld, "dialog_fechamento"));
    w->lbl_inicial = GTK_WIDGET(gtk_builder_get_object(bld, "lbl_inicial"));
    w->lbl_bruto = GTK_WIDGET(gtk_builder_get_object(bld, "lbl_bruto"));
    w->lbl_total = GTK_WIDGET(gtk_builder_get_object(bld, "lbl_total"));
}


int inicializarInterface(Sistema *sistema, int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    sistema->gtk->builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(sistema->gtk->builder, "../ui/menuPrincipal.glade", &sistema->gtk->error)) {
        printf("ERRO GLADE %s\n", sistema->gtk->error->message);
        g_error_free(sistema->gtk->error);
        return 0;
    }

    sistema->gtk->css_provider = gtk_css_provider_new();
    if (!gtk_css_provider_load_from_path(sistema->gtk->css_provider, "../ui/menuPrincipal.css", &sistema->gtk->error)) {
        printf("css %s\n", sistema->gtk->error->message);
        g_error_free(sistema->gtk->error);
    } else {
        sistema->gtk->screen = gdk_screen_get_default();
        gtk_style_context_add_provider_for_screen(
            sistema->gtk->screen,
            GTK_STYLE_PROVIDER(sistema->gtk->css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
        );
    }

    carregarWidgets(sistema);
    conectarEventos(sistema);
    carregarProdutosTabela(sistema);
    carregarRelatorioTabela(sistema);

    return 1;
}
