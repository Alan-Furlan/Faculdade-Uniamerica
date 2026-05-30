#include <stdio.h>
#include "database.h"

sqlite3* abrirBanco(){

    sqlite3 *db;

    int rc = sqlite3_open("sistema.db", &db);

    if(rc){
        printf("Erro ao abrir banco\n");
        return NULL;
    }

    printf("Banco aberto!\n");

    return db;
}

void fecharBanco(sqlite3 *db){
    sqlite3_close(db);
}

void criarTabelaProdutos(sqlite3 *db){

    char *erro = NULL;

    const char *sql =
        "CREATE TABLE IF NOT EXISTS produtos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nome TEXT,"
        "preco REAL,"
        "estoque INTEGER,"
        "tipo INTEGER"
        ");";

    int rc = sqlite3_exec(db, sql, 0, 0, &erro);

    if(rc != SQLITE_OK){
        printf("Erro SQL: %s\n", erro);
        sqlite3_free(erro);
    }else{
        printf("Tabela produtos criada!\n");
    }
}