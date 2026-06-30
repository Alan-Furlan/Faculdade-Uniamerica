#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <gtk/gtk.h>
#include "../models/produto.h"
#include "../models/sistema.h"
#include "produto_service.h"
#include "../utils/utils.h"

void cadastrarProdutoDb(sqlite3 *db, Produto *produto) {
    const char *sql =
        "INSERT INTO produtos (nome, preco, estoque, tipo) VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return;

    sqlite3_bind_text(stmt, 1, produto->nome, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, produto->preco);
    sqlite3_bind_int(stmt, 3, produto->estoque);
    sqlite3_bind_int(stmt, 4, produto->tipo);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    printf("Produto '%s' cadastrado\n", produto->nome);
}

int buscarProdutoPorIdDb(sqlite3 *db, int id, Produto *produto) {
    const char *sql =
        "SELECT id, nome, preco, estoque, tipo FROM produtos WHERE id = ?;";
    sqlite3_stmt *stmt;
    int encontrado = 0;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            produto->id = sqlite3_column_int(stmt, 0);
            produto->preco = sqlite3_column_double(stmt, 2);
            produto->estoque = sqlite3_column_int(stmt, 3);
            produto->tipo = sqlite3_column_int(stmt, 4);
            strncpy(produto->nome, (const char *)sqlite3_column_text(stmt, 1), sizeof(produto->nome) - 1);
            produto->nome[sizeof(produto->nome) - 1] = '\0';
            encontrado = 1;
        }
    }
    sqlite3_finalize(stmt);
    return encontrado;
}

void carregarProdutosTabela(Sistema *sistema) {
    if (!sistema->gtk->list_store) return;
    gtk_list_store_clear(sistema->gtk->list_store);

    const char *sql = "SELECT id, nome, preco, estoque FROM produtos;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(sistema->db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        GtkTreeIter linha;
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            char txt_preco[64];
            formatarMoeda(txt_preco, sizeof(txt_preco), sqlite3_column_double(stmt, 2));

            gtk_list_store_append(sistema->gtk->list_store, &linha);
            gtk_list_store_set(sistema->gtk->list_store, &linha,
                0, sqlite3_column_int(stmt, 0),
                1, sqlite3_column_text(stmt, 1),
                2, txt_preco,
                3, sqlite3_column_int(stmt, 3), -1);
        }
    }
    sqlite3_finalize(stmt);
}

void cadastrarProduto(GtkButton *button, gpointer user_data) {
    Sistema *sistema = user_data;

    const char *nome = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(sistema->gtk->builder, "entry_nome_prod")));
    const char *tipo = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(sistema->gtk->builder, "entry_tipo_prod")));
    const char *preco = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(sistema->gtk->builder, "entry_preco_prod")));
    const char *estoque = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(sistema->gtk->builder, "entry_estoque_prod")));

    Produto produto;
    strncpy(produto.nome, nome, sizeof(produto.nome) - 1);
    produto.nome[sizeof(produto.nome) - 1] = '\0';
    produto.preco = atof(preco);
    produto.estoque = atoi(estoque);
    produto.tipo = atoi(tipo);

    cadastrarProdutoDb(sistema->db, &produto);
    carregarProdutosTabela(sistema);
}
