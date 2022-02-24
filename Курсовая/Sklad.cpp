#include "stdafx.h"
#include "Sklad.h"

Sklad::Sklad() {
}


Sklad::Sklad(int id, int nomer, string data, int shifr_mat, string nazvan_mat, int kolichestvo, int idsort, int nomersort, string datasort, int shifr_matsort, string nazvan_matsort, int kolichestvosort,int all_kolichestvo) {
	this->id = id;
	this->nomer = nomer;
	this->data = data;
	this->shifr_mat = shifr_mat;
	this->nazvan_mat = nazvan_mat;
	this->kolichestvo = kolichestvo;
	this->all_kolichestvo = all_kolichestvo;
	this->idsort = idsort;
	this->nomersort = nomersort;
	this->datasort = datasort;
	this->shifr_matsort = shifr_matsort;
	this->nazvan_matsort = nazvan_matsort;
	this->kolichestvosort = kolichestvosort;

}

void Sklad::setId(int id) {
	this->id = id;
}
void Sklad::setNomer(int nomer) {
	this->nomer = nomer;
}
void Sklad::setData(string data) {
	this->data = data;
}
void Sklad::setShifr_mat(int shifr_mat) {
	this->shifr_mat = shifr_mat;
}
void Sklad::setNazvan_mat(string nazvan_mat) {
	this->nazvan_mat = nazvan_mat;
}

void Sklad::setKolichestvo(int kolichestvo) {
	this->kolichestvo = kolichestvo;
}
void Sklad::setALL_Kolichestvo(int all_kolichestvo) {
	this->all_kolichestvo = all_kolichestvo;
}
int Sklad::getId() {
	return id;
}
int Sklad::getNomer() {
	return nomer;
}
string Sklad::getData() {
	return data;
}
int Sklad::getShifr_mat() {
	return shifr_mat;
}
string Sklad::getNazvan_mat() {
	return nazvan_mat;
}
int Sklad::getKolichestvo() {
	return kolichestvo;
}
int Sklad::getALL_Kolichestvo() {
	return all_kolichestvo;
}

void Sklad::setIdsort(int idsort) {
	this->idsort = idsort;
}
void Sklad::setNomersort(int nomersort) {
	this->nomersort = nomersort;
}
void Sklad::setDatasort(string datasort) {
	this->datasort = datasort;
}
void Sklad::setShifr_matsort(int shifr_matsort) {
	this->shifr_matsort = shifr_matsort;
}
void Sklad::setNazvan_matsort(string nazvan_matsort) {
	this->nazvan_matsort = nazvan_matsort;
}

void Sklad::setKolichestvosort(int kolichestvosort) {
	this->kolichestvosort = kolichestvosort;
}


int Sklad::getIdsort() {
	return idsort;
}
int Sklad::getNomersort() {
	return nomersort;
}
string Sklad::getDatasort() {
	return datasort;
}
int Sklad::getShifr_matsort() {
	return shifr_matsort;
}
string Sklad::getNazvan_matsort() {
	return nazvan_matsort;
}
int Sklad::getKolichestvosort() {
	return kolichestvosort;
}
