#include "Case.h"


Case::Case() :id(0) {}

Case::Case(int id) : id(id){}

Case::~Case(){}


int Case::getNbGraine()
{
	return nbGraine;
}


int Case::getId()
{
	return id;
}

void Case::incNbGraine(int g)
{
	nbGraine+=g;
}

void Case::setNbGraine(int g)
{
	nbGraine=g;
}

