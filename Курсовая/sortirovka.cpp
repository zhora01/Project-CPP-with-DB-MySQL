#include "stdafx.h"
#include "sortirovka.h"


sortirovka::sortirovka()
{
}


void sortirovka::sortNomer(vector<Sklad> & tabl, int x2) {
	Sklad sorttabl;
	if (x2 == 1) {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				if (tabl[i].getNomer() > tabl[j].getNomer())
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
	else {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				if (tabl[i].getNomer()<tabl[j].getNomer())
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}

}
void sortirovka::sortData(vector<Sklad> & tabl, int x2) {
	Sklad sorttabl;
	string gg;
	string mm;
	string dd;
	string str1;
	string str2;

	if (x2 == 1) {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				str1 = tabl[i].getData();
				gg = str1[6];
				gg += str1[7];
				gg += str1[8];
				gg += str1[9];
				mm = str1[3];
				mm += str1[4];
				dd = str1[0];
				dd += str1[1];
				str1 = gg + mm + dd;

				str2 = tabl[i].getData();
				gg = str2[6];
				gg += str2[7];
				gg += str2[8];
				gg += str2[9];
				mm = str2[3];
				mm += str2[4];
				dd = str2[0];
				dd += str2[1];
				str2 = gg + mm + dd;

				if (str1.compare(str2) > 0)
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
	else {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				str1 = tabl[i].getData();
				gg = str1[6];
				gg += str1[7];
				gg += str1[8];
				gg += str1[9];
				mm = str1[3];
				mm += str1[4];
				dd = str1[0];
				dd += str1[1];
				str1 = gg + mm + dd;

				str2 = tabl[j].getData();
				gg = str2[6];
				gg += str2[7];
				gg += str2[8];
				gg += str2[9];
				mm = str2[3];
				mm += str2[4];
				dd = str2[0];
				dd += str2[1];
				str2 = gg + mm + dd;

				if (str1.compare(str2) < 0)
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
}
void sortirovka::sortShifr(vector<Sklad> & tabl, int x2) {

	Sklad sorttabl;
	if (x2 == 1) {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				if (tabl[i].getShifr_mat() > tabl[j].getShifr_mat())
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
	else {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				if (tabl[i].getShifr_mat() < tabl[j].getShifr_mat())
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
}
void sortirovka::sortNaimen(vector<Sklad> & tabl, int x2) {
	Sklad sorttabl;
	if (x2 == 1) {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				if (tabl[i].getNazvan_mat() > tabl[j].getNazvan_mat())
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
	else {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				if (tabl[i].getNazvan_mat() > tabl[j].getNazvan_mat())
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
}
void sortirovka::sortKol(vector<Sklad> & tabl, int x2) {
	Sklad sorttabl;
	if (x2 == 1) {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				if (tabl[i].getKolichestvo() > tabl[j].getKolichestvo())
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
	else {
		for (int i = 0; i < tabl.size() - 1; i++)
		{
			for (int j = i; j < tabl.size(); j++)
			{
				if (tabl[i].getKolichestvo() < tabl[j].getKolichestvo())
				{
					sorttabl = tabl[i];
					tabl[i] = tabl[j];
					tabl[j] = sorttabl;
				}
			}
		}
	}
}

sortirovka::~sortirovka()
{
}