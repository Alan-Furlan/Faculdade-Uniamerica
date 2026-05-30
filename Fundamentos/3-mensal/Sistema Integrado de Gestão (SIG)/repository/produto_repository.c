#include <stdio.h>
#include <string.h>

#include "../database/sqlite3.h"
#include "../models/produto.h"
#include "../utils/utils.h"

void enviarProdutobanco(sqlite3 *db, Produto produto){
    char sql[500];

    sprintf(
        sql,

        "INSERT INTO produtos(nome, preco, estoque, tipo) "
        "VALUES('%s', %f, %d, %d);",

        produto.nome,
        produto.preco,
        produto.estoque,
        produto.tipo
    );

    char *erro = NULL;

    int rc = sqlite3_exec(db, sql, 0, 0, &erro);

    if(rc != SQLITE_OK){
        printf("Erro SQL: %s\n", erro);
        sqlite3_free(erro);
    }else{
        printf("Produto salvo no banco!\n");
    }
}



void carregarProdutos(sqlite3 *db, Sistema *sistema){

    sqlite3_stmt *consulta; 
    
    char *sql = "SELECT * FROM produtos";

    if(sqlite3_prepare_v2(db, sql, -1, &consulta, NULL) != SQLITE_OK){
        printf("Erro no SELECT\n");
        return;
    }

    while(sqlite3_step(consulta) == SQLITE_ROW){

        //realloc
        aumentarCapacidadeProdutos(sistema);

        Produto *p = &sistema->produto[sistema->qtdProdutosC];

        p->id = sqlite3_column_int(consulta, 0);

        strcpy(p->nome,(const char*) sqlite3_column_text(consulta, 1));

        p->preco = sqlite3_column_double(consulta, 2);

        p->estoque = sqlite3_column_int(consulta, 3);

        p->tipo = sqlite3_column_int(consulta, 4);

        sistema->qtdProdutosC++;
    }

    sqlite3_finalize(consulta);
}