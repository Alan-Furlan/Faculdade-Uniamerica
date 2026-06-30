#include <gtk/gtk.h>
#include "../models/sistema.h"
#include "navigation.h"

void pgCadastrarProduto(GtkButton *button, gpointer data) {
    Sistema *sistema = data;
    gtk_stack_set_visible_child_name(sistema->gtk->pag_dashboard, "tela_cadastro");
}

void pgAbrirCaixa(GtkButton *button, gpointer data) {
    Sistema *sistema = data;
    gtk_stack_set_visible_child_name(sistema->gtk->pag_dashboard, "tela_abrir_caixa");
}

void pgVenderProduto(GtkButton *button, gpointer data) {
    Sistema *sistema = data;
    gtk_stack_set_visible_child_name(sistema->gtk->pag_dashboard, "tela_vender_produto");
}

void pgRelatorioVendas(GtkButton *button, gpointer data) {
    Sistema *sistema = data;
    gtk_stack_set_visible_child_name(sistema->gtk->pag_dashboard, "tela_relatorio_vendas");
}

void pgProdutosVendidos(GtkButton *button, gpointer data) {
    Sistema *sistema = data;
    gtk_stack_set_visible_child_name(sistema->gtk->pag_dashboard, "tela_produtos_vendidos");
}
