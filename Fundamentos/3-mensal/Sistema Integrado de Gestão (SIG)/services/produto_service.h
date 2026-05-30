#ifndef PRODUTO_SERVICE_H
#define PRODUTO_SERVICE_H

#include "../models/sistema.h"
#include "../database/database.h"

void cadastrarProduto(Sistema *sistema, sqlite3 *db);
Produto findById(Produto *produto, int id, int qtdProdutoC);

#endif