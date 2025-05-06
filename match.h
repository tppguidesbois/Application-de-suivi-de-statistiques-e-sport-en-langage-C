#ifndef MATCH_H
#define MATCH_H

#include <sqlite3.h>

void ajouter_match_menu(sqlite3 *db);
void afficher_matchs_menu(sqlite3 *db);

#endif
