#include <stdio.h>
#include <sqlite3.h>
#include "database.h"

sqlite3* abrirBanco() {
    sqlite3 *db;
    if (sqlite3_open("sistema.db", &db) != SQLITE_OK) {
        printf("Falha ao abrir o banco de dados\n");
        return NULL;
    }
    printf("Banco de dados aberto\n");
    return db;
}

void fecharBanco(sqlite3 *db) {
    sqlite3_close(db);
}

void criarTabelasSistema(sqlite3 *db) {
    char *sql_produtos =
        "CREATE TABLE IF NOT EXISTS produtos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome TEXT, preco REAL, estoque INTEGER, tipo INTEGER);";

    char *sql_vendas =
        "CREATE TABLE IF NOT EXISTS vendas ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "total_geral REAL"
        ");";

    char *sql_itens =
        "CREATE TABLE IF NOT EXISTS itens_venda ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "venda_id INTEGER, produto_id INTEGER,"
        "quantidade INTEGER, preco_unitario REAL, total_item REAL,"
        "FOREIGN KEY(venda_id) REFERENCES vendas(id),"
        "FOREIGN KEY(produto_id) REFERENCES produtos(id));";

    sqlite3_exec(db, sql_produtos, NULL, NULL, NULL);
    sqlite3_exec(db, sql_vendas, NULL, NULL, NULL);
    sqlite3_exec(db, sql_itens, NULL, NULL, NULL);

    printf("Tabelas criadas\n");
}
