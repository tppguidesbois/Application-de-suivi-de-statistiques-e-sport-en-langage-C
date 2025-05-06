CREATE TABLE Joueur (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    pseudo TEXT NOT NULL,
    mot_de_passe TEXT NOT NULL
);

CREATE TABLE Match (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    joueur_id INTEGER,
    date TEXT,
    jeu TEXT,
    kills INTEGER,
    score INTEGER,
    placement INTEGER,
    mode_jeu TEXT,
    FOREIGN KEY(joueur_id) REFERENCES Joueur(id)
);
