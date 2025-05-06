void ajouter_joueur(sqlite3 *db, const char *pseudo, const char *mdp) {
    char *sql = "INSERT INTO Joueur(pseudo, mot_de_passe) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pseudo, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, mdp, -1, SQLITE_STATIC);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void ajouter_joueur_menu(sqlite3 *db) {
    char pseudo[50], mdp[50];
    printf("Pseudo : ");
    fgets(pseudo, 50, stdin);
    pseudo[strcspn(pseudo, "\n")] = '\0';

    printf("Mot de passe : ");
    fgets(mdp, 50, stdin);
    mdp[strcspn(mdp, "\n")] = '\0';

    const char *sql = "INSERT INTO Joueur(pseudo, mot_de_passe) VALUES (?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, pseudo, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, mdp, -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Joueur ajouté avec succès !\n");
        } else {
            printf("Erreur lors de l'ajout.\n");
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Erreur de préparation de la requête.\n");
    }
}
