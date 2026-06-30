#include <stdio.h>
#include "utils.h"

void formatarMoeda(char *buf, int tam, double valor) {
    snprintf(buf, tam, "R$ %.2f", valor);
    for (int i = 0; buf[i]; i++)
        if (buf[i] == '.') { buf[i] = ','; break; }
}
