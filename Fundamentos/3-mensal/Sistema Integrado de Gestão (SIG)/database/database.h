#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3.h"
#include "../models/produto.h"
#include "../models/sistema.h"

sqlite3* abrirBanco();
void fecharBanco(sqlite3 *db);
void criarTabelaProdutos(sqlite3 *db);
void enviarProdutobanco(sqlite3 *db, Produto produto);
void carregarProdutos(sqlite3 *db, Sistema *sistema);

#endif