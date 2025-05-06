1. Connexion
2. Ajouter un match
3. Afficher stats
4. Quitter

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "joueur.h"
#include "match.h"
#include "db.h"

int main() {
    sqlite3 *db;
    
    // Connexion à la base de données
    if (ouvrir_base(&db) != 0) {
        fprintf(stderr, "Erreur lors de l'ouverture de la base de données.\n");
        return 1;
    }

    int choix;
    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Ajouter un joueur\n");
        printf("2. Ajouter un match\n");
        printf("3. Afficher les matchs\n");
        printf("4. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar(); // pour consommer le \n

        switch (choix) {
            case 1:
                ajouter_joueur_menu(db);
                break;
            case 2:
                ajouter_match_menu(db);
                break;
            case 3:
                afficher_matchs_menu(db);
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 4);

    sqlite3_close(db);
    return 0;
}


printf("5. Statistiques d’un joueur\n");
// puis dans le switch :
case 5:
    afficher_stats(db);
    break;
