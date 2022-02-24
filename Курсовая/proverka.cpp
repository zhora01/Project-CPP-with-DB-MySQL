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
		throw exception("��������� ������ �����!");
	}
	if (atoi(nomer) < 0)
	{
		throw exception("������������ �����!");
	}

}
void proverka::CheckYY(char *s)
{
	if (strlen(s) < 1)
	{
		throw exception("��������� ������ ���");
	}
	if (strlen(s) < 4 || strlen(s) > 4)
	{
		throw exception("������������ ���!");
	}

}
void proverka::CheckDD(char* s)
{
	if (strlen(s) < 1)
	{
		throw exception("��������� ������ ����");
	}
	if (strlen(s) < 1 || strlen(s) > 2)
	{
		throw exception("������������ ����!");
	}
}

void proverka::CheckMM(char *s)
{
	if (strlen(s) < 1)
	{
		throw exception("��������� ������ �����!");
	}
	if (atoi(s) <= 0 || atoi(s) > 12)
	{
		throw exception("������������ �����!");
	}
}

void proverka::CheckShifr(char *s) {
	if (strlen(s) < 1)
	{
		throw exception("��������� ������ ����!");
	}
	if (strlen(s) != 6)
	{
		throw exception("������������ ����!");
	}

}
void proverka::CheckNaim(char *s) {
	if (strlen(s) < 1)
	{
		throw exception("��������� ������ ������������!");
	}

	if (strlen(s) >= 20)
	{
		throw exception("������������ ����� ������ ������������ 20 ��������!");
	}
	
}
void proverka::CheckKol(char *s) {
	if (strlen(s) < 1)
	{
		throw exception("��������� ������ ����������!");
	}
	if (atoi(s) < 0)
	{
		throw exception("������������ ����������!");
	}
}

