#pragma once
#include "Livre.h"

Livre creerUnLivre();
void afficherUnLivre(Livre livre,int isCreated=0);
Livre * rechercherUnLivre(Livre* livres, int taille, char* charRecherchre);
Livre * ajouterUnLivre(Livre* livres, int& taille, Livre &nouveauLivre);
Livre * supprimerUnLivre(Livre* livres, int& taille, Livre& livreASuppimer);
int rechercherLIndexDunLivre(Livre* livres, int taille, Livre livre);
Livre rechercherUnLivreMaxNbPage(Livre* livres, int taille);
void BookLibraryManger();
Livre* choisirUnLivre(Livre* livres, int& taille, const char* raisonDuChoix = "");