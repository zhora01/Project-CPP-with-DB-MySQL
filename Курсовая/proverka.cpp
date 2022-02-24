#include "stdafx.h"
#include "proverka.h"


proverka::proverka()
{
}


proverka::~proverka()
{
}


void proverka::CheckNomer(char *nomer)
{
	if (strlen(nomer) < 1)
	{
		throw exception("Заполните строку Номер!");
	}
	if (atoi(nomer) < 0)
	{
		throw exception("Неккоректный Номер!");
	}

}
void proverka::CheckYY(char *s)
{
	if (strlen(s) < 1)
	{
		throw exception("Заполните строку Год");
	}
	if (strlen(s) < 4 || strlen(s) > 4)
	{
		throw exception("Неккоректный Год!");
	}

}
void proverka::CheckDD(char* s)
{
	if (strlen(s) < 1)
	{
		throw exception("Заполните строку День");
	}
	if (strlen(s) < 1 || strlen(s) > 2)
	{
		throw exception("Неккоректный День!");
	}
}

void proverka::CheckMM(char *s)
{
	if (strlen(s) < 1)
	{
		throw exception("Заполните строку Месяц!");
	}
	if (atoi(s) <= 0 || atoi(s) > 12)
	{
		throw exception("Неккоректный Месяц!");
	}
}

void proverka::CheckShifr(char *s) {
	if (strlen(s) < 1)
	{
		throw exception("Заполните строку Шифр!");
	}
	if (strlen(s) != 6)
	{
		throw exception("Неккоректный Шифр!");
	}

}
void proverka::CheckNaim(char *s) {
	if (strlen(s) < 1)
	{
		throw exception("Заполните строку Наименование!");
	}

	if (strlen(s) >= 20)
	{
		throw exception("Максимальная длина строки Наименование 20 символов!");
	}
	
}
void proverka::CheckKol(char *s) {
	if (strlen(s) < 1)
	{
		throw exception("Заполните строку Количество!");
	}
	if (atoi(s) < 0)
	{
		throw exception("Неккоректное Количество!");
	}
}

