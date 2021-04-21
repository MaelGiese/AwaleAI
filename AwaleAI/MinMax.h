#include "Plateau.h"

class MinMax
{
public:
	MinMax();
	std::string decisionMinMaxParallel(Plateau p, Joueur j1, Joueur j2, int turn, int baseDepthMax);
	// std::string decisionMinMax(Plateau p, Joueur j1, Joueur j2, int turn, int baseDepthMax);
	int MinMaxValueAplhaBeta(int alpha, int beta, Plateau p, Joueur joueurCourant, Joueur j2, bool computer_play, int idCase, bool couleur, int turn, int depth, int depthMax);
	int minValue(int a, int b);
	int maxValue(int a, int b);
	void maxArrayValueIndex(int* bleuValue, int bleuSize, int* maxIndex);
	int decisionDepthMax(int nbCoup);

protected :
	virtual int evaluation(Plateau p, int turn, Joueur joueurCourant, Joueur j2) = 0;
};

class AIDiffNbGraine : public MinMax
{
protected:
	int evaluation(Plateau p, int turn, Joueur joueurCourant, Joueur j2);
};

class AIStarving : public MinMax
{
protected:
	int evaluation(Plateau p, int turn, Joueur joueurCourant, Joueur j2);
};

