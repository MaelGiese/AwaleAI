#include <string>
#include "Case.h"

class Joueur
{
private:
	std::string nom;
	int* caseId;
	int caseIdSize;
	int graine;

public:
	Joueur();
	Joueur(std::string nom);
	void ajoutCaseId(int* id, int size);
	void incGraine(int g);
	void printJoueur();
	bool hasCase(int idCase);
	int getGraine();
	int getCasesSize();
	std::string getNom();
	int* getCases();
};

