#ifndef CAIXA_SERVICE_H
#define CAIXA_SERVICE_H

#include <gtk/gtk.h>
#include "../models/sistema.h"

void abrirCaixa(GtkButton *button, gpointer user_data);
void abrirModalFecharCaixa(GtkButton *button, gpointer user_data);

#endif
