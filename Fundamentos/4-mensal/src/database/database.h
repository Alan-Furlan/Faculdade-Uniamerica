#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

sqlite3* abrirBanco();
void fecharBanco(sqlite3 *db);
void criarTabelasSistema(sqlite3 *db);

#endif
