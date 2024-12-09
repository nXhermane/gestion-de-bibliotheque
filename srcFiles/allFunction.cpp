#include "allFunction.h"
#include <iostream>
#include <cstring>
#include <limits>

Livre creerUnLivre()
{
	Livre livre;
	std::cout << "Creation d'un Live" << std::endl;
	const int maxChar = 200;
	livre.titre = new char[maxChar];
	std::cout << "Entrez le titre du livre : ";
	std::cin.getline(livre.titre, maxChar);
	livre.auteur = new char[maxChar];
	std::cout << "Entrez l'auteur du livre : ";
	std::cin.getline(livre.auteur, maxChar);
	while (true) {
		std::cout << "Entrez le nombre de pages que contient le livre : ";
		std::cin >> livre.nombreDePages;
		if (std::cin.fail()) {
			std::cout << "Erreur veillez entrer un nombre entier." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else break;
	}
	

	afficherUnLivre(livre);
	return livre;
}
Livre* choisirUnLivre(Livre* livres, int& taille, const char* raisonDuChoix) {
	char* titreOuAuteur = new char;
	const int maxChar = 200;
	std::cout << raisonDuChoix << std::endl;
	std::cout << "Entrez le titre ou l'auteur du livre : ";
	std::cin.getline(titreOuAuteur, maxChar);
	Livre* livre = rechercherUnLivre(livres, taille, titreOuAuteur);

	if (livre == NULL) std::cout << "Le livre avec le titre " << titreOuAuteur << " n'existe pas dans la bibliothèque." << std::endl;
	delete titreOuAuteur;
	return livre;
}

void afficherUnLivre(Livre livre, int isCreated)
{
	std::cout << ((isCreated == 0) ? "Voici le livre que vous avez creer" : "Voici votre livre") << std::endl;
	std::cout << "Titre           : " << livre.titre << "\n";
	std::cout << "Auteur          : " << livre.auteur << "\n";
	std::cout << "Nombre de Pages : " << livre.nombreDePages << std::endl;
}

int rechercherLIndexDunLivre(Livre* livres, int taille, Livre livre) {
	int index = -1;
	for (int i = 0; i < taille; i++) {
		Livre currentLivre = livres[i];
		if (strcmp(currentLivre.titre, livre.titre) == 0) index = i;
	}
	return index;
}

Livre rechercherUnLivreMaxNbPage(Livre* livres, int taille)
{

	Livre maxCurrentPageLivre = Livre();
	maxCurrentPageLivre.nombreDePages = 0;
	for (int i = 0; i < taille; i++) if (livres[i].nombreDePages > maxCurrentPageLivre.nombreDePages) maxCurrentPageLivre = livres[i];
	return maxCurrentPageLivre.nombreDePages == 0 ? livres[0] : maxCurrentPageLivre;
}

void BookLibraryManger()
{
	std::cout << "Wecome to my library manager" << std::endl;
	int taille = 0;
	Livre* livres = nullptr;
	bool condition = true;

	while (condition) {
		std::cout << "=== Menu ===" << std::endl;
		std::cout << "a - Ajouter un livre à la bibliothèque." << std::endl;
		std::cout << "d - Supprimer un livre de la bibliothèque." << std::endl;
		std::cout << "s - Afficher un livre." << std::endl;
		std::cout << "f - Rechercher un livre." << std::endl;
		std::cout << "m - Afficher le livre ayant le plus grand nombre de page." << std::endl;
		std::cout << "e - Quitter le programme ." << std::endl;

		char command;
		std::cin >> command;
		std::cin.ignore();
		switch (command)
		{
		case'a': {
			Livre livre = creerUnLivre();
			livres = ajouterUnLivre(livres, taille, livre);
		}; break;
		case'd': {
			Livre* livre = choisirUnLivre(livres, taille, "Choix du livre a suppimer");
			if (livre == NULL) continue;
			livres = supprimerUnLivre(livres, taille, *livre);
			std::cout << "Le livre a ete supprime." << std::endl;
		}; break;
		case's': {
			Livre* livre = choisirUnLivre(livres, taille, "Choix du livre a afficher");
			if (livre == NULL) continue;
			afficherUnLivre(*livre, 1);
		}; break;
		case'f': {
			Livre* livre = choisirUnLivre(livres, taille);
			if (livre == NULL) continue;
			afficherUnLivre(*livre, 1);
		}; break;
		case'm': {
			Livre livre = rechercherUnLivreMaxNbPage(livres, taille);
			afficherUnLivre(livre);
		}; break;
		case'e': {
			condition = false;
			std::cout << "Fin du Programme." << std::endl;
		}; break;
		default:
			std::cout << "La commande entree n'est pas prise ne charge." << std::endl;
			break;
		}
	}
	
	delete[] livres;
}


Livre* rechercherUnLivre(Livre* livres, int taille, char* charRechercher)
{
	for (int i = 0; i <= taille; i++) {
		Livre livre = livres[i];
		char* rechercheDansleTitre = strstr(livre.titre, charRechercher);
		if (rechercheDansleTitre != NULL) return &livres[i];
		char* rechercheAvecLauteur = strstr(livre.auteur, charRechercher);
		if (rechercheAvecLauteur != NULL) return &livres[i];
	}
	return NULL;
}

Livre* ajouterUnLivre(Livre* livres, int& taille, Livre& nouveauLivre)
{	
	//Allouer la memoire dynamique a une nouvelle liste de livre 
	Livre * nouvelleListe = new Livre[taille + 1];
	// Inserer les elements de l'ancienne liste dans la nouvelle liste 
	for (int i = 0; i < taille; i++) nouvelleListe[i] = livres[i];
	// Ajouter le nouveau elements
	nouvelleListe[taille] = nouveauLivre;
	delete[] livres;
	taille++;
	return nouvelleListe;
}

Livre* supprimerUnLivre(Livre* livres, int& taille, Livre& livreASuppimer) {
	if (taille == 0) {
		std::cout << "Vous n'avez aucun livre dans votre bibliothèque. Veillez en ajouter." << std::endl;
		return livres;
	}
	Livre* nouvelleListe = new Livre[taille - 1];

	int indexDuLivre = rechercherLIndexDunLivre(livres, taille, livreASuppimer);
	if (indexDuLivre == -1) {
		std::cout << "The book not found." << std::endl;
		return livres;
	}

	for (int i = 0, j = 0; i < taille; i++) if (i != indexDuLivre) nouvelleListe[j++] = livres[i];
	delete[] livres;
	taille--;
	return nouvelleListe;
}


