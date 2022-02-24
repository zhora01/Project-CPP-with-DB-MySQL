#pragma once
#include<string>
using std::string;

class Sklad
{
private:
	int id;
	int nomer;
	string data;
	int shifr_mat;
	string nazvan_mat;
	int kolichestvo;

	int idsort;
	int nomersort;
	string datasort;
	int shifr_matsort;
	string nazvan_matsort;
	int kolichestvosort;

	int all_kolichestvo = 0;

public:
	Sklad();
	Sklad(int id, int nomer, string data, int shifr_mat, string nazvan_mat, int kolichestvo, int idsort, int nomesort, string datasort, int shifr_matsort, string nazvan_matsort, int kolichestvosort, int all_kolichestvo);
	void setId(int id);
	void setNomer(int nomer);
	void setData(string data);
	void setShifr_mat(int shifr_mat);
	void setNazvan_mat(string nazvan_mat);
	void setKolichestvo(int kolichestvo);
	void setALL_Kolichestvo(int all_kolichestvo);
	int getId();
	int getNomer();
	string getData();
	int getShifr_mat();
	string getNazvan_mat();
	int getKolichestvo();
	int getALL_Kolichestvo();

	void setIdsort(int idsort);
	void setNomersort(int nomersort);
	void setDatasort(string datasort);
	void setShifr_matsort(int shifr_matsort);
	void setNazvan_matsort(string nazvan_matsort);
	void setKolichestvosort(int kolichestvosort);
	int getIdsort();
	int getNomersort();
	string getDatasort();
	int getShifr_matsort();
	string getNazvan_matsort();
	int getKolichestvosort();
};