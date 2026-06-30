#ifndef PRODUTO_SERVICE_H
#define PRODUTO_SERVICE_H

#include <sqlite3.h>
#include <gtk/gtk.h>
#include "../models/produto.h"
#include "../models/sistema.h"

void cadastrarProdutoDb(sqlite3 *db, Produto *produto);
int  buscarProdutoPorIdDb(sqlite3 *db, int id, Produto *produto);
void carregarProdutosTabela(Sistema *sistema);
void cadastrarProduto(GtkButton *button, gpointer user_data);

#endif
