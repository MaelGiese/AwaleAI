#include "Plateau.h"
#include "MinMax.h"


void gameAIvsJoueur() {
	Joueur j1{ "j1" }, IA{ "IA" };
	Joueur* ptrJ1 = &j1, * ptrIA = &IA, * ptrJoueurCourant, * ptrJoueur2nd;
	std::string coup;
	int idCase = NULL, turn = 0, baseDepthMax = 5;
	bool j;
	Plateau p{};
	AIStarving minmax{};

	std::cout << "\nQui commence : \n0.Joueur\n1.IA";
	std::cin >> j;

	if (j) {
		p = Plateau{ ptrIA,ptrJ1 };
	}
	else {
		p = Plateau{ ptrJ1,ptrIA };
	}

	while (!p.finJeu(j1, IA)) {
		p.printPlateau();
		turn++;
		if (j) {
			j = !j;
			ptrJoueurCourant = ptrIA;
			ptrJoueur2nd = ptrJ1;

			coup = minmax.decisionMinMaxParallel(p, IA, j1, turn, baseDepthMax);
			ptrJoueurCourant->printJoueur();
			std::cout << "\n\nCoup : " << coup << std::endl;
		}
		else {
			j = !j;
			ptrJoueurCourant = ptrJ1;
			ptrJoueur2nd = ptrIA;

			ptrJoueurCourant->printJoueur();
			std::cout << "\n\nCoup : ";
			std::cin >> coup;
		}

		if (coup != "0") {
			if (p.isCoupValide(coup, ptrJoueurCourant)) {
				p.getCaseFromCoup(coup, &idCase);
				// id des cases de 0 a 15
				idCase--;
				p.jouerTour(ptrJoueurCourant, ptrJoueur2nd, idCase);
				std::cout << "Graines : " << ptrJoueurCourant->getGraine();
			}
			else {
				std::cout << "\nCette case est incorrecte";
				j = !j;
			}
		}
	}

	ptrJoueurCourant = p.getWinner(ptrIA, ptrJ1);

	if (ptrJoueurCourant != nullptr) {
		std::cout << "\n\n\nGAGNANT :";
		ptrJoueurCourant->printJoueur();
	}
	else {
		std::cout << "\n\nEGALITE !!" << std::endl;
	}
}

void gameAIvsAI(Joueur IA1, AIDiffNbGraine AI1minmax, Joueur IA2, AIStarving AI2minmax) {
	Joueur* ptrIA1 = &IA1, * ptrIA2 = &IA2, * ptrJoueurCourant, * ptrJoueur2nd;
	std::string coup;
	int idCase, turn = 0, baseDepthMax = 4;
	bool j;
	Plateau p{};
	


	std::cout << "\nQui commence : \n0."<<IA2.getNom()<<"\n1."<<IA1.getNom();
	std::cin >> j;

	if (j) {
		p = Plateau{ ptrIA2,ptrIA1 };
	}
	else {
		p = Plateau{ ptrIA1,ptrIA2 };
	}

	while (!p.finJeu(IA1, IA2)) {
		p.printPlateau();
		turn++;

		std::cout << "\n\nTour : " << turn << std::endl;
		//system("PAUSE");
		if (j) {
			j = !j;
			ptrJoueurCourant = ptrIA1;
			ptrJoueur2nd = ptrIA2;
			coup = AI1minmax.decisionMinMaxParallel(p, IA1, IA2, turn, baseDepthMax);
			ptrJoueurCourant->printJoueur();
			std::cout << "\n\nCoup : " << coup << std::endl;
		}
		else {
			j = !j;
			ptrJoueurCourant = ptrIA2;
			ptrJoueur2nd = ptrIA1;
			coup = AI2minmax.decisionMinMaxParallel(p, IA2, IA1, turn, baseDepthMax);
			
			
			ptrJoueurCourant->printJoueur();
			std::cout << "\n\nCoup : " << coup << std::endl;
		}

		if (coup != "0") {
			if (p.isCoupValide(coup, ptrJoueurCourant)) {

				p.getCaseFromCoup(coup, &idCase);
				// id des cases de 0 a 15
				idCase--;
				p.jouerTour(ptrJoueurCourant, ptrJoueur2nd, idCase);
				std::cout << "Graines : " << ptrJoueurCourant->getGraine();
			}
			else {
				std::cout << "\nCette case est incorrecte";
				j = !j;
			}
		}
	}

	
	ptrJoueurCourant = p.getWinner(ptrIA1, ptrIA2);

	if (ptrJoueurCourant != nullptr) {
		std::cout << "\n\n\nGAGNANT :";
		ptrJoueurCourant->printJoueur();
	}else {
		std::cout << "\n\nEGALITE !!" << std::endl;
	}
	return;
}


int main() {
	bool typeOfGame;

	std::cout << "\n\tChoisissez :\n\n\t\t0.AI vs AI\n\n\t\t1.AI vs Joueur" << std::endl;
	std::cin >> typeOfGame;
	if (typeOfGame) {
		gameAIvsJoueur();
	}else {
		Joueur AI1{ "NB GRAINES" }, AI2{ "STARVING" };
		AIDiffNbGraine minmax1= AIDiffNbGraine{};
		AIStarving minmax2 = AIStarving{};
		gameAIvsAI(AI1, minmax1, AI2, minmax2);
	}
	return 0;
}