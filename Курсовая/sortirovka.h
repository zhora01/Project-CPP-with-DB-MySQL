#pragma once
#include "Sklad.h"
#include<vector>


using std::vector;
class sortirovka :
	public Sklad
{
public:
	sortirovka();
	~sortirovka();
	void sortNomer(vector<Sklad> & tabl, int x2);
	void sortData(vector<Sklad> & tabl, int x2);
	void sortShifr(vector<Sklad> & tabl, int x2);
	void sortNaimen(vector<Sklad> & tabl, int x2);
	void sortKol(vector<Sklad> & tabl, int x2);
};



