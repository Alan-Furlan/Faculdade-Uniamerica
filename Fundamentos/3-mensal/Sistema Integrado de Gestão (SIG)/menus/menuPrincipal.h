#ifndef MENU_PRINCIPAL_H
#define MENU_PRINCIPAL_H

#include "../models/sistema.h"
#include "../database/database.h"

void menuPrincipal(sqlite3 *db, Sistema *sistema);

#endif