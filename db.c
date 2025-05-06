sqlite3 *db;
int rc = sqlite3_open("database.db", &db);
if (rc) {
    fprintf(stderr, "Erreur ouverture BDD: %s\n", sqlite3_errmsg(db));
    return 1;
}

#include <stdio.h>
#include "db.h"

int ouvrir_base(sqlite3 **db) {
    int rc = sqlite3_open("database.db", db);
    if (rc) {
        fprintf(stderr, "Erreur SQLite: %s\n", sqlite3_errmsg(*db));
        return 1;
    }
    return 0;
}


#include <sys/stat.h>

int fichier_existe(const char *nom) {
    struct stat buffer;
    return (stat(nom, &buffer) == 0);
}

int ouvrir_base(sqlite3 **db) {
    int existe = fichier_existe("database.db");
    int rc = sqlite3_open("database.db", db);
    if (rc) {
        fprintf(stderr, "Erreur SQLite: %s\n", sqlite3_errmsg(*db));
        return 1;
    }

    if (!existe) {
        // Crée les tables si elles n'existent pas
        const char *sql =
            "CREATE TABLE Joueur ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "pseudo TEXT NOT NULL,"
            "mot_de_passe TEXT NOT NULL);"
            "CREATE TABLE Match ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "joueur_id INTEGER,"
            "date TEXT,"
            "jeu TEXT,"
            "kills INTEGER,"
            "score INTEGER,"
            "placement INTEGER,"
            "mode_jeu TEXT,"
            "FOREIGN KEY(joueur_id) REFERENCES Joueur(id));";

        char *errMsg = NULL;
        if (sqlite3_exec(*db, sql, NULL, NULL, &errMsg) != SQLITE_OK) {
            fprintf(stderr, "Erreur création BDD : %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("Base de données initialisée.\n");
        }
    }

    return 0;
}
