#include "MinMax.h"
#include <time.h>
#include <windows.h>
#include <omp.h>

MinMax::MinMax(){}

std::string MinMax::decisionMinMaxParallel(Plateau p, Joueur j1, Joueur j2, int turn, int baseDepthMax)
{
	int nbJoueurCases = p.getNbCase()/2;
	int* moves = (int*)calloc(nbJoueurCases, sizeof(int));
	int size, nbCoupAdv;
	bool computerPlay = false;
	int depth = 1;

	// Récupère le nombre de coups jouable par l'adversaire
	nbCoupAdv = p.getNbCoupPossible(j2);
	// Récupère tous les coups jouable pour le joueur courant
	p.setAllpossibleMove(j1, moves, &size);

	if (size == 0) {
		return "0";
	}

	int* value = (int*)calloc(size, sizeof(int));

	//// Calcul de temps
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	double interval;

	// Décide de la profondeur maximum
	int depthMax = baseDepthMax + decisionDepthMax(size + nbCoupAdv);
	std::cout << "\nDepth Max : " << depthMax << "\nnb coups : " << size + nbCoupAdv;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);
	
#pragma omp parallel 
	{
#pragma omp sections
		{
#pragma omp section
			{
				for (int j = 0; j < size; j++) {
					if (moves) {
						value[j] = MinMaxValueAplhaBeta(INT_MIN, INT_MAX, p, j1, j2, computerPlay, moves[j], 1, turn, depth, depthMax);
					}
				}
			}
		}
	}
	

	/*
	for (int j = 0; j < size; j++) {
		if (moves) {
			value[j] = MinMaxValueAplhaBeta(INT_MIN, INT_MAX, p, j1, j2, computerPlay, moves[j], 1, turn, depth, depthMax);
		}
	}
	*/
		// Affichage
		for (int j = 0; j < size; j++) {
			if (moves) {
				std::cout << "\n" << moves[j] + 1;
				std::cout << ": " << value[j];
			}
		}
	
		QueryPerformanceCounter(&end);
		interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		std::cout <<"\nexecution time : " << interval<<std::endl;

		if (interval > 2 || interval < 1) {
			//system("PAUSE");
		}

		int maxIndex = INT_MIN;
		bool maxCouleur = NULL;

		maxArrayValueIndex(value, size, &maxIndex);

		if (moves) {
			std::string s = std::to_string(moves[maxIndex] + 1);
			free(moves);
			return s;
		}
	return "";
}

/*
std::string MinMax::decisionMinMax(Plateau p, Joueur j1, Joueur j2, int turn, int baseDepthMax)
{
	int nbJoueurCases = p.getNbCase() / 2;
	int* bleuMoves = (int*)calloc(nbJoueurCases, sizeof(int));
	int* rougeMoves = (int*)calloc(nbJoueurCases, sizeof(int));
	int bleuSize, rougeSize, nbCoupAdv;
	bool maxCouleur = NULL, computerPlay = false;
	int max = INT_MIN, maxIndex = 0;
	int depth = 1;
	int tmp = 0;

	// Récupère le nombre de coups jouable par l'adversaire
	nbCoupAdv = p.getNbCoupPossible(j2);
	// Récupère tous les coups jouable pour le joueur courant
	p.setAllpossibleMove(j1, bleuMoves, &bleuSize);

	if (bleuSize == 0 && rougeSize == 0) {
		return "0";
	}

	// Calcul de temps
	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	double interval;



	int depthMax = baseDepthMax + decisionDepthMax(bleuSize + rougeSize + nbCoupAdv);
	std::cout << "\ndepthMax : " << depthMax << "\nnb coups : " << bleuSize + rougeSize + nbCoupAdv;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	for (int i = 0; i < rougeSize; i++) {
		if (rougeMoves) {
			std::cout << "\n" << rougeMoves[i] + 1 << "R :  ";
			tmp = MinMaxValueAplhaBeta(INT_MIN, INT_MAX, p, j1, j2, computerPlay, rougeMoves[i], 0, turn, depth, depthMax);
			std::cout << tmp;
		}

		if (tmp >= max) {
			max = tmp;
			maxIndex = i;
			maxCouleur = 0;
		}
	}

	for (int i = 0; i < bleuSize; i++) {
		if (bleuMoves) {
			std::cout << "\n" << bleuMoves[i] + 1 << "B :  ";
			tmp = MinMaxValueAplhaBeta(INT_MIN, INT_MAX, p, j1, j2, computerPlay, bleuMoves[i], 1, turn, depth, depthMax);
			std::cout << tmp;
		}

		if (tmp >= max) {
			max = tmp;
			maxIndex = i;
			maxCouleur = 1;
		}
	}

	QueryPerformanceCounter(&end);
	interval = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
	std::cout << "\nexecution time : " << interval << std::endl;

	if (interval > 2 || interval < 1) {
		//system("PAUSE");
	}

	if (maxCouleur) {
		if (bleuMoves) {
			std::string s = std::to_string(bleuMoves[maxIndex] + 1);
			free(bleuMoves);
			return s + 'B';
		}
	}
	else {
		if (rougeMoves) {
			std::string s = std::to_string(rougeMoves[maxIndex] + 1);
			free(rougeMoves);
			return s + 'R';
		}
	}
	return "";
}
*/

int MinMax::MinMaxValueAplhaBeta(int alpha, int beta, Plateau p, Joueur computer, Joueur j2, bool computer_play, int idCase, bool couleur, int turn, int depth, int depthMax)
{
	if (p.finJeu(computer, j2)) {
		if (p.isWinner(computer) || p.isStarving(j2)) {
			return INT_MAX - depth;
		}else if (p.isWinner(j2) || p.isStarving(computer)) {
			return INT_MIN + depth;
		}else if(computer.getGraine() > j2.getGraine()){
			return INT_MAX - depth;
		}
		else {
			return 0;
		}
	}

	if (depth == depthMax) {
		return evaluation(p, turn, j2, computer);
	}

	int nbJoueurCases = p.getNbCase() / 2;
	int* moves = (int*)calloc(nbJoueurCases, sizeof(int));
	int size, tmp;
	
	if (computer_play) {
		int max = INT_MIN;
		int alphaNode = INT_MIN;
		p.jouerTour(&computer, &j2, idCase);
		p.setAllpossibleMove(computer, moves, &size);

		for (int i = 0; i < size; i++) {
			tmp = MinMaxValueAplhaBeta(maxValue(alpha, alphaNode), beta, p, computer, j2, !computer_play, moves[i], 0, turn + 1, depth + 1, depthMax);

			alphaNode = maxValue(alphaNode, tmp);

			if (alphaNode >= beta) {
				return alphaNode;
			}

			if (tmp > max) {
				max = tmp;
			}
		}

		free(moves);

		return max;
	}else{
		int min = INT_MAX;
		int betaNode = INT_MAX;
		p.jouerTour(&j2, &computer, idCase);
		p.setAllpossibleMove(j2, moves, &size);


		for (int i = 0; i < size; i++) {
			tmp = MinMaxValueAplhaBeta(alpha, minValue(beta, betaNode), p, computer, j2, !computer_play, moves[i], 0, turn + 1, depth + 1, depthMax);

			betaNode = minValue(betaNode, tmp);

			if (alpha >= betaNode) {
				return betaNode;
			}

			if (tmp < min) {
				min = tmp;
			}
		}

		free(moves);

		return min;
	}
}

int MinMax::minValue(int a, int b)
{
	if (a <= b) {
		return a;
	}else {
		return b;
	}
}

int MinMax::maxValue(int a, int b)
{
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}

void MinMax::maxArrayValueIndex(int* value, int size, int* maxIndex)
{
	int max = INT_MIN;

	for (int i = 0; i < size; i++) {
		if (value[i] >= max) {
			max = value[i];
			*maxIndex = i;
		}
	}
}


int MinMax::decisionDepthMax(int nbCoup)
{

	if (nbCoup > 25) {
		return 0;
	}

	if (nbCoup > 22) {
		return 1;
	}

	if (nbCoup > 17) {
		return 2;
	}

	if (nbCoup > 14) {
		return 3;
	}

	if (nbCoup > 10) {
		return 4;
	}

	if (nbCoup > 4) {
		return 5;
	}

	return 6;
}


int AIDiffNbGraine::evaluation(Plateau p, int turn, Joueur joueurCourant, Joueur j2)
{
	int j1g = joueurCourant.getGraine(), j2g = j2.getGraine();
	return j1g - j2g;
}

int AIStarving::evaluation(Plateau p, int turn, Joueur joueurCourant, Joueur j2)
{
	int j1g = joueurCourant.getGraine(), j2g = j2.getGraine();

	return j1g - j2g;


	int diff = p.diff_nb_graines_plateau(joueurCourant, j2);


	return (j1g - j2g)*10 - diff;
}