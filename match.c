#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "match.h"

void ajouter_match_menu(sqlite3 *db) {
    int joueur_id, kills, score, placement;
    char date[20], jeu[20], mode_jeu[20];

    printf("ID du joueur : ");
    scanf("%d", &joueur_id);
    getchar();

    printf("Date (YYYY-MM-DD) : ");
    fgets(date, 20, stdin);
    date[strcspn(date, "\n")] = '\0';

    printf("Jeu (Fortnite/RocketLeague) : ");
    fgets(jeu, 20, stdin);
    jeu[strcspn(jeu, "\n")] = '\0';

    printf("Mode de jeu : ");
    fgets(mode_jeu, 20, stdin);
    mode_jeu[strcspn(mode_jeu, "\n")] = '\0';

    printf("Kills : ");
    scanf("%d", &kills);
    printf("Score : ");
    scanf("%d", &score);
    printf("Placement : ");
    scanf("%d", &placement);
    getchar();

    const char *sql = "INSERT INTO Match(joueur_id, date, jeu, kills, score, placement, mode_jeu) VALUES (?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, joueur_id);
        sqlite3_bind_text(stmt, 2, date, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, jeu, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, kills);
        sqlite3_bind_int(stmt, 5, score);
        sqlite3_bind_int(stmt, 6, placement);
        sqlite3_bind_text(stmt, 7, mode_jeu, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            printf("Match ajouté avec succès !\n");
        } else {
            printf("Erreur lors de l'ajout du match.\n");
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Erreur dans la requête SQL.\n");
    }
}

void afficher_matchs_menu(sqlite3 *db) {
    const char *sql = "SELECT pseudo, jeu, date, kills, score, placement, mode_jeu FROM Match "
                      "JOIN Joueur ON Match.joueur_id = Joueur.id "
                      "ORDER BY date DESC";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        printf("\n--- Matchs enregistrés ---\n");
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("Joueur: %s | Jeu: %s | Date: %s | Kills: %d | Score: %d | Placement: %d | Mode: %s\n",
                sqlite3_column_text(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_text(stmt, 2),
                sqlite3_column_int(stmt, 3),
                sqlite3_column_int(stmt, 4),
                sqlite3_column_int(stmt, 5),
                sqlite3_column_text(stmt, 6)
            );
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Erreur dans la requête SELECT.\n");
    }
}


void afficher_stats(sqlite3 *db) {
    int joueur_id;
    printf("ID du joueur : ");
    scanf("%d", &joueur_id);
    getchar();

    const char *sql = "SELECT COUNT(*), AVG(kills), AVG(score), AVG(placement) FROM Match WHERE joueur_id = ?";
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, joueur_id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("\n--- Statistiques joueur ---\n");
            printf("Matchs joués : %d\n", sqlite3_column_int(stmt, 0));
            printf("Kills moyens : %.2f\n", sqlite3_column_double(stmt, 1));
            printf("Score moyen : %.2f\n", sqlite3_column_double(stmt, 2));
            printf("Placement moyen : %.2f\n", sqlite3_column_double(stmt, 3));
        }
        sqlite3_finalize(stmt);
    } else {
        printf("Erreur dans la requête de statistiques.\n");
    }
}
