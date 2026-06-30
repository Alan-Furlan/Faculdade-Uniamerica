#include <stdio.h>
#include <gtk/gtk.h>
#include "src/models/sistema.h"
#include "src/database/database.h"
#include "src/ui/interface.h"

int main(int argc, char *argv[]) {

    Widgets widgets = {0};
    Sistema sistema = {0};
    sistema.gtk = &widgets;

    sistema.db = abrirBanco();
    if (sistema.db == NULL) {
        printf("Falha ao abrir o banco de dados \n");
        return 1;
    }
    
    criarTabelasSistema(sistema.db);

    if (!inicializarInterface(&sistema, argc, argv)) {
        printf("Falha ao inicializar a interface grafica \n");
        return 1;
    }

    gtk_widget_show_all(sistema.gtk->window);
    gtk_main();
    return 0;
}