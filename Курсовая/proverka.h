#pragma once
#include<string>
#include<exception>
using std::exception;
using std::string;
class proverka
{
public:
	proverka();
	~proverka();
	void CheckNomer(char *s);
	void CheckYY(char *s);
	void CheckMM(char *s);
	void CheckDD(char* s);
	void CheckShifr(char *s);
	void CheckNaim(char *s);
	void CheckKol(char *s);

};

