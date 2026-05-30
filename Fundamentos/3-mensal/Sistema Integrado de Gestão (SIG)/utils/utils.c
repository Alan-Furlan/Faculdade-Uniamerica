#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void aumentarCapacidadeProdutos(Sistema *sistema){
    if(sistema->qtdProdutosC >= sistema->tamanhoP){
    
        sistema->tamanhoP++;
    
        Produto *temp = realloc(sistema->produto, (sistema->tamanhoP) * sizeof(Produto));
    
        if(temp == NULL){
            free(temp);
            printf("erro de memória");
            return;
        }

        sistema->produto = temp;
        
    }
}