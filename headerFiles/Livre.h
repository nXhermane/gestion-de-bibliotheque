#pragma once

struct Livre {
    char* titre;
    char* auteur;
    int nombreDePages;
};
struct ResultatDeRecherche {
    Livre livre;
    bool livreTrouver;
};