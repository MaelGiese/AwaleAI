#include "Case.h"
#include "Joueur.h"
#pragma once

class Plateau
{
private :
	int nbCase=24;
	int totalGraine;
	Case plateau[24];
	int win_treshold = (nbCase * 4) / 2;

public :
	Plateau();
	Plateau(Joueur *joueur1, Joueur *joueur2);
	void printPlateau();
	bool isCoupValide(std::string coup, Joueur* j);
	void getCaseFromCoup(std::string coup, int *idCase);
	int getNbCase();
	void jouerTour(Joueur* j, Joueur *j2, int idCase);
	int finTour(Joueur *j, int idCase);
	bool finJeu(Joueur j1, Joueur j2);
	bool isStarving(Joueur j1);
	void setAllpossibleMove(Joueur j, int* moves, int* size);
	int getNbCoupPossible(Joueur j);
	Joueur* getWinner(Joueur* joueur1, Joueur* joueur2);
	bool isWinner(Joueur j);
	int diff_nb_graines_plateau(Joueur j1, Joueur j2);
};

