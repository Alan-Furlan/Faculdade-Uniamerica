#ifndef VENDA_SERVICE_H
#define VENDA_SERVICE_H

#include <gtk/gtk.h>
#include "../models/sistema.h"

void carregarRelatorioTabela(Sistema *sistema);
void adicionarProdutoCarrinho(GtkButton *button, gpointer user_data);
void finalizarVenda(GtkButton *button, gpointer user_data);

#endif
