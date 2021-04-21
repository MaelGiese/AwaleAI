#include "Joueur.h"

Joueur::Joueur() : nom(""), caseId(nullptr), caseIdSize(0), graine(0){}

Joueur::Joueur(std::string nom) : nom(nom), caseId(nullptr), caseIdSize(0), graine(0){}


void Joueur::ajoutCaseId(int* id, int size)
{
	Joueur::caseId = id;
	Joueur::caseIdSize = size;
}

void Joueur::incGraine(int g){
	graine += g;
}

void Joueur::printJoueur()
{
	std::cout << "\nJoueur : " << nom;
	std::cout << "\nCases : ";
	for (int i = 0; i < caseIdSize; i++) {
		std::cout << " " << caseId[i]+1;
	}
	std::cout << "\nGraines : " << graine;
}

bool Joueur::hasCase(int idCase)
{
	for (int i = 0; i < caseIdSize; i++) {
		if (caseId[i] == idCase) {
			return true;
		}
	}
	return false;
}

int Joueur::getGraine()
{
	return graine;
}

int Joueur::getCasesSize()
{
	return caseIdSize;
}

std::string Joueur::getNom()
{
	return nom;
}

int* Joueur::getCases()
{
	return caseId;
}
