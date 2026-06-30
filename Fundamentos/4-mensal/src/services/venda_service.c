#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <gtk/gtk.h>
#include "../models/sistema.h"
#include "../models/produto.h"
#include "produto_service.h"
#include "venda_service.h"
#include "../utils/utils.h"

int atualizarEstoque(sqlite3 *db, int produto_id, int quantidade) {
    const char *sql = "UPDATE produtos SET estoque = estoque - ? WHERE id = ?;";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;
    
    sqlite3_bind_int(stmt, 1, quantidade);
    sqlite3_bind_int(stmt, 2, produto_id);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE);
}

int inserirItemVenda(sqlite3 *db, int venda_id, int produto_id, int quantidade, double preco_unitario, double total) {
    const char *sql = "INSERT INTO itens_venda (venda_id, produto_id, quantidade, preco_unitario, total_item) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 0;

    sqlite3_bind_int(stmt, 1, venda_id);
    sqlite3_bind_int(stmt, 2, produto_id);
    sqlite3_bind_int(stmt, 3, quantidade);
    sqlite3_bind_double(stmt, 4, preco_unitario);
    sqlite3_bind_double(stmt, 5, total);
    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return (rc == SQLITE_DONE);
}

int getQuantidadeNoCarrinho(Sistema *sistema, int id_produto) {
    if (!sistema->gtk->liststore_carrinho) return 0;
    
    GtkTreeIter linha;
    int qtd_total = 0;
    
    if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha)) {
        do {
            int id_na_lista = 0, qtd_na_lista = 0;
            gtk_tree_model_get(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha, 0, &id_na_lista, 2, &qtd_na_lista, -1);
            if (id_na_lista == id_produto) qtd_total += qtd_na_lista;
        } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha));
    }
    return qtd_total;
}

void atualizarTotalCarrinho(Sistema *sistema) {
    if (!sistema->gtk->liststore_carrinho || !sistema->gtk->lblTotalComp) return;

    GtkTreeIter linha;
    double total = 0.0;

    if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha)) {
        do {
            double valor = 0.0;
            gtk_tree_model_get(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha, 6, &valor, -1);
            total += valor;
        } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha));
    }

    char buf[64];
    formatarMoeda(buf, sizeof(buf), total);
    gtk_label_set_text(GTK_LABEL(sistema->gtk->lblTotalComp), buf);
}

void carregarRelatorioTabela(Sistema *sistema) {
    gtk_list_store_clear(sistema->gtk->liststore_relatorio);

    const char *sql = 
        "SELECT v.id, (SELECT SUM(quantidade) FROM itens_venda WHERE venda_id = v.id), v.total_geral "
        "FROM vendas v ORDER BY v.id DESC;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(sistema->db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        GtkTreeIter linha;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int qtd = sqlite3_column_type(stmt, 1) == SQLITE_NULL ? 0 : sqlite3_column_int(stmt, 1);
            
            char txt_id[32], txt_qtd[32], txt_total[64];
            snprintf(txt_id, sizeof(txt_id), "%d", sqlite3_column_int(stmt, 0));
            snprintf(txt_qtd, sizeof(txt_qtd), "%d", qtd);
            formatarMoeda(txt_total, sizeof(txt_total), sqlite3_column_double(stmt, 2));

            gtk_list_store_append(sistema->gtk->liststore_relatorio, &linha);
            gtk_list_store_set(sistema->gtk->liststore_relatorio, &linha, 0, txt_id, 1, txt_qtd, 2, txt_total, -1);
        }
    }
    sqlite3_finalize(stmt);
}

void adicionarProdutoCarrinho(GtkButton *button, gpointer user_data) {
    Sistema *sistema = user_data;
    if (sistema->caixaAberto == 0) {
        printf("Abra o caixa primeiro\n");
        return;
    }

    GtkEntry *inputId = GTK_ENTRY(gtk_builder_get_object(sistema->gtk->builder, "entry_produto_id_carrinho"));
    GtkSpinButton *inputQtd = GTK_SPIN_BUTTON(gtk_builder_get_object(sistema->gtk->builder, "spin_quantidade"));

    int id_prod = atoi(gtk_entry_get_text(inputId));
    int qtd = gtk_spin_button_get_value_as_int(inputQtd);

    Produto p;
    if (!buscarProdutoPorIdDb(sistema->db, id_prod, &p)) {
        printf("Produto nao encontrado no banco de dados\n");
        return;
    }

    if (p.estoque < (qtd + getQuantidadeNoCarrinho(sistema, id_prod))) {
        printf("Quantidade excede o estoque disponivel\n");
        return;
    }

    double total_item = p.preco * qtd;
    char txt_preco[64], txt_total[64];
    formatarMoeda(txt_preco, sizeof(txt_preco), p.preco);
    formatarMoeda(txt_total, sizeof(txt_total), total_item);

    GtkTreeIter linha;
    gtk_list_store_append(sistema->gtk->liststore_carrinho, &linha);
    gtk_list_store_set(sistema->gtk->liststore_carrinho, &linha, 0, id_prod, 1, p.nome, 2, qtd, 3, txt_preco, 4, txt_total, 5, p.preco, 6, total_item, -1);

    atualizarTotalCarrinho(sistema);
    gtk_entry_set_text(inputId, "");
    gtk_spin_button_set_value(inputQtd, 1.0);
}

void finalizarVenda(GtkButton *button, gpointer user_data) {
    Sistema *sistema = user_data;
    GtkTreeIter linha;

    if (!gtk_tree_model_get_iter_first(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha)) {
        printf("O carrinho esta vazio\n");
        return;
    }

    double total_compra = 0.0;
    do {
        int id_prod = 0;
        double valor = 0.0;
        gtk_tree_model_get(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha, 0, &id_prod, 6, &valor, -1);
        
        Produto p;
        if (!buscarProdutoPorIdDb(sistema->db, id_prod, &p) || p.estoque < getQuantidadeNoCarrinho(sistema, id_prod)) {
            printf("Produto ID %d com problema de estoque ou nao encontrado\n", id_prod);
            return;
        }
        total_compra += valor;
    } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha));

    sqlite3_exec(sistema->db, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    sqlite3_stmt *stmt_venda;
    sqlite3_prepare_v2(sistema->db, "INSERT INTO vendas (total_geral) VALUES (?);", -1, &stmt_venda, NULL);
    sqlite3_bind_double(stmt_venda, 1, total_compra);
    sqlite3_step(stmt_venda);
    sqlite3_finalize(stmt_venda);
    
    int venda_id = (int)sqlite3_last_insert_rowid(sistema->db);

    int total_qtd = 0;
    gtk_tree_model_get_iter_first(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha);
    
    do {
        int id_prod, qtd;
        double preco, total;
        char *nome = NULL;

        gtk_tree_model_get(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha, 0, &id_prod, 1, &nome, 2, &qtd, 5, &preco, 6, &total, -1);

        inserirItemVenda(sistema->db, venda_id, id_prod, qtd, preco, total);
        atualizarEstoque(sistema->db, id_prod, qtd);
        total_qtd += qtd;

        if (sistema->gtk->liststore_produtos_vendidos) {
            GtkTreeIter iter_caixa;
            char txt_venda[32], txt_qtd[32], txt_total[64];
            snprintf(txt_venda, sizeof(txt_venda), "%d", venda_id);
            snprintf(txt_qtd, sizeof(txt_qtd), "%d", qtd);
            formatarMoeda(txt_total, sizeof(txt_total), total);

            gtk_list_store_appen(sistema->gtk->liststore_produtos_vendidos, &iter_caixa);
            gtk_list_store_set(sistema->gtk->liststore_produtos_vendidos, &iter_caixa, 0, txt_venda, 2, nome, 3, txt_qtd, 5, txt_total, -1);
        }
        if (nome) g_free(nome);
    } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(sistema->gtk->liststore_carrinho), &linha));

    sqlite3_exec(sistema->db, "END TRANSACTION;", NULL, NULL, NULL);

    sistema->caixa_qtd_itens_vendidos += total_qtd;
    sistema->caixa_faturamento_acumulado += total_compra;

    char buf[64];
    if (sistema->gtk->lbl_qtd_total_produtos) {
        snprintf(buf, sizeof(buf), "%d", sistema->caixa_qtd_itens_vendidos);
        gtk_label_set_text(sistema->gtk->lbl_qtd_total_produtos, buf);
    }
    if (sistema->gtk->lbl_faturamento_total_produtos) {
        formatarMoeda(buf, sizeof(buf), sistema->caixa_faturamento_acumulado);
        gtk_label_set_text(sistema->gtk->lbl_faturamento_total_produtos, buf);
    }

    gtk_list_store_clear(sistema->gtk->liststore_carrinho);
    gtk_label_set_text(GTK_LABEL(sistema->gtk->lblTotalComp), "R$ 0,00");
    carregarProdutosTabela(sistema);
    carregarRelatorioTabela(sistema);

    printf("Venda finalizada\n");
}