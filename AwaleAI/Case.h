#pragma once
#include <iostream>
class Case
{
private:
	int id;
	int nbGraine = 4;

public:
	Case();
	Case(int id);
	~Case();

	int getNbGraine();
	int getId();
	void setNbGraine(int g);
	void incNbGraine(int g);
};