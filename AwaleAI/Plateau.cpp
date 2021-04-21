#include "Plateau.h"
#include "Case.h"

Plateau::Plateau() : nbCase(24), totalGraine(nbCase * 4), win_treshold((nbCase * 4)/2)
{
}

Plateau::Plateau(Joueur *joueur1, Joueur *joueur2) : nbCase(24),totalGraine(nbCase*4)
{
	int size = nbCase / 2;
	int* j1Id = new int[size];
	int i1 = 0;
	int* j2Id = new int[size];
	int i2 = 0;
	bool j = true;

	for (int i = 0; i < nbCase; i++) {
		plateau[i] = Case(i);

		if (j) {
			j1Id[i1] = i;
			j = !j;
			i1++;
		}
		else
		{
			j2Id[i2] = i;
			j = !j;
			i2++;
		}
	}

	joueur1->ajoutCaseId(j1Id, size);
	joueur2->ajoutCaseId(j2Id, size);
}

void Plateau::printPlateau()
{
	std::cout << "\n\n-------------------------------------------------------------------------------------------------------------";
	std::cout << "\n-------------------------------------------------------------------------------------------------------------\n\n";
	int halfSize = nbCase / 2;
	// Haut du plateau
	std::cout << "  ";
	for (int i = 0; i < halfSize; i++) {
		if (plateau[i].getId()+1 < 10) {
			std::cout << "   " << plateau[i].getId() + 1 << "   ";
		}
		else {
			std::cout << "   " << plateau[i].getId() + 1 << "  ";
		}
	}
	std::cout << std::endl;

	std::cout << " ";
	for (int i = 0; i < halfSize; i++) {
		std::cout << "-------";
	}
	std::cout << std::endl;
	for (int i = 0; i < halfSize; i++) {
		std::cout << "  |  ";
		if (plateau[i].getNbGraine() < 10) {
			std::cout << " " << plateau[i].getNbGraine();
		}
		else {
			std::cout << plateau[i].getNbGraine();
		}

	}

	std::cout << " |" << std::endl << " ";
	for (int i = 0; i < halfSize; i++) {
		std::cout << "-------";
	}
	std::cout << "\n";


	// Bas du plateau
	for (int i = nbCase - 1; i >= halfSize; i--) {
		std::cout << "  |  ";
		if (plateau[i].getNbGraine() < 10) {
			std::cout << " " << plateau[i].getNbGraine();
		}
		else {
			std::cout << plateau[i].getNbGraine();
		}

	}
	std::cout << " |" << std::endl;
	std::cout << " ";
	for (int i = nbCase - 1; i >= halfSize; i--) {
		std::cout << "-------";
	}

	std::cout << "\n  ";
	for (int i = nbCase - 1; i >= halfSize; i--) {
		if (plateau[i].getId() + 1 < 10) {
			std::cout << "   " << plateau[i].getId() + 1 << "   ";
		}
		else {
			std::cout << "   " << plateau[i].getId() + 1 << "  ";
		}
	}
}

bool Plateau::isCoupValide(std::string coup, Joueur *j)
{
	int idCase = NULL;
	getCaseFromCoup(coup, &idCase);
	idCase--;
	
	if (j->hasCase(idCase)) {
		if (plateau[idCase].getNbGraine() > 0) {
			return true;
		}
			
	}
	return false;
}


void Plateau::getCaseFromCoup(std::string coup, int* idCase)
{
	if (coup.length() == 1) {
		*idCase = coup[0] - '0';
	}else {

		if (coup.length() == 2) {
			int tmp1 = coup[0] - '0';
			int tmp2 = coup[1] - '0';
			*idCase = tmp1 * 10 + tmp2;
		}
	}
}

int Plateau::getNbCase()
{
	return nbCase;
}


void Plateau::jouerTour(Joueur *j, Joueur *j2, int idCase){
int nbGraine;

		nbGraine = plateau[idCase].getNbGraine();
		plateau[idCase].setNbGraine(0);
		for (int i = 0; i < nbGraine; i++) {
			idCase++;
			if (idCase > nbCase-1) {
					idCase = 0;
			}
			plateau[idCase].incNbGraine(1);
		}
		


		// finTour retourne le nombre de graine gagné par le joueur
		int gain = finTour(j, idCase);
		j->incGraine(gain);
		// on actualise le nombre de graine total sur le plateau
		totalGraine -= gain;
		// Si le joueur adeverse est affamé on ajoute son nombre de graine au joueur
		if (this->isStarving(*j2)) {
			j->incGraine(j2->getGraine());
			j2->incGraine(-j2->getGraine());
		}
}

// Retourne le nombre de graine gagné par le joueur j
int Plateau::finTour(Joueur *j, int idCase){
	int totalGraine = 0;
	int caseGraine = plateau[idCase].getNbGraine();
	
	while ((caseGraine == 3) || (caseGraine == 2)){
		totalGraine += caseGraine;
		plateau[idCase].setNbGraine(0);
		idCase--;
		if (idCase < 0) {
			idCase = nbCase-1;
		}
		caseGraine = plateau[idCase].getNbGraine();
	}
	return totalGraine;
}

bool Plateau::finJeu(Joueur j1, Joueur j2)
{
	if (j1.getGraine() > win_treshold || j2.getGraine() > win_treshold) {
		return true;
	}

	if (totalGraine < 8) {
		return true;
	}

	return false;
}

bool Plateau::isStarving(Joueur j1) {
	// Check if j1 has possible moves
	int nbCoupJ1 = this->getNbCoupPossible(j1);

	if (nbCoupJ1 == 0) {
		return true;
	}

	return false;

}

void Plateau::setAllpossibleMove(Joueur j, int* moves, int* movesSize)
{
	int* joueurCases = j.getCases();
	int size = j.getCasesSize();
	int index = 0;


	for (int i = 0; i < size; i++)
	{
		if (plateau[joueurCases[i]].getNbGraine() > 0) {
			moves[index] = joueurCases[i];
			index++;
		}
	}

	*movesSize = index;
}

int Plateau::getNbCoupPossible(Joueur j)
{
	int* joueurCases = j.getCases();
	int size = j.getCasesSize();
	int index = 0;


	for (int i = 0; i < size; i++)
	{
		if (plateau[joueurCases[i]].getNbGraine() > 0) {
			index++;
		}
	}
	return index;
}

Joueur* Plateau::getWinner(Joueur* joueur1, Joueur* joueur2)
{
	int g1 = joueur1->getGraine();
	int g2 = joueur2->getGraine();

	if (g1 == g2) {
		return nullptr;
	}
	if (g1 > g2) {
		return joueur1;
	}else{
		return joueur2;
	}
}

bool Plateau::isWinner(Joueur j1)
{
	if (j1.getGraine() > (nbCase*4)/2) {
		return true;
	}

	return false;
}


int Plateau::diff_nb_graines_plateau(Joueur j1, Joueur j2)
{
	int j1g = 0;
	int j2g = 0;
	int j1Size = j1.getCasesSize();
	int j2Size = j2.getCasesSize();
	int* j1Cases = j1.getCases();
	int* j2Cases = j2.getCases();

	for (int i = 0; i < j1Size; i++)
	{
		j1g += plateau[j1Cases[i]].getNbGraine();
	}
	
	for (int i = 0; i < j2Size; i++)
	{
		j2g += plateau[j2Cases[i]].getNbGraine();
	}

	return j1g - j2g;
}




