#include "stdafx.h"
#include"connect.h"

void showSqlError(unsigned int handleType, const SQLHANDLE& handle)
{
	SQLCHAR SQLSTATE[1024];
	SQLCHAR message[1024];
	if (SQL_SUCCESS != SQLGetDiagRec(handleType, handle, 1, SQLSTATE, NULL, message, 1024, NULL))
	{
		cout << "Error";
		cout << "SQL drive message: " << message << "\nSQL state: " << SQLSTATE << "." << endl;
	}
}


void Connect(std::vector<Sklad> & tabl, char zapros[], int n)
{
	SQLHANDLE SQLEnvHandle = NULL;
	SQLHANDLE SQLConncetionHandle = NULL;
	SQLHANDLE SQLStatementHandle = NULL;
	SQLRETURN retCode = 0;

	do
	{

		SQLCHAR retConString[1024];
		switch (SQLDriverConnect(SQLConncetionHandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost,1433; DATABASE=master; UID=kursa4; PWD=123;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT))
		{
		case SQL_SUCCESS:

			break;
		case SQL_SUCCESS_WITH_INFO:

			break;
		case SQL_NO_DATA_FOUND:
			showSqlError(SQL_HANDLE_DBC, SQLConncetionHandle);
			retCode = -1;
			break;
		case SQL_INVALID_HANDLE:
			showSqlError(SQL_HANDLE_DBC, SQLConncetionHandle);
			retCode = -1;
			break;
		case SQL_ERROR:
			showSqlError(SQL_HANDLE_DBC, SQLConncetionHandle);
			retCode = -1;
			break;
		default:

			break;
		}

		if (retCode == -1)
		{
			cout << "--->5";
			break;
		}

		if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, SQLConncetionHandle, &SQLStatementHandle))
		{
			cout << "--->6";
			break;
		}

	} while (false);

	switch (n)
	{
	case 1:
		SQLExecDirect(SQLStatementHandle, (SQLCHAR*)zapros, SQL_NTS);
		break;
	case 2:
		SQLExecDirect(SQLStatementHandle, (SQLCHAR*)zapros, SQL_NTS);
		break;
	case 9:
		int id;
		int nomer;
		char data_[25];
		int shifr;
		char naimen[25];
		int kolichestvo;
		if (SQL_SUCCESS != SQLExecDirect(SQLStatementHandle, (SQLCHAR*)zapros, SQL_NTS))
		{

			showSqlError(SQL_HANDLE_STMT, SQLStatementHandle);
		}
		else
		{
			int i = 0;
			while (SQLFetch(SQLStatementHandle) == SQL_SUCCESS)
			{
				SQLGetData(SQLStatementHandle, 1, SQL_C_DEFAULT, &id, sizeof(int), NULL);
				SQLGetData(SQLStatementHandle, 2, SQL_C_DEFAULT, &nomer, sizeof(int), NULL);
				SQLGetData(SQLStatementHandle, 3, SQL_C_DEFAULT, &data_, sizeof(data_), NULL);
				SQLGetData(SQLStatementHandle, 4, SQL_C_DEFAULT, &shifr, sizeof(int), NULL);
				SQLGetData(SQLStatementHandle, 5, SQL_C_DEFAULT, &naimen, sizeof(naimen), NULL);
				SQLGetData(SQLStatementHandle, 6, SQL_C_DEFAULT, &kolichestvo, sizeof(int), NULL);

				tabl.push_back(Sklad());
				tabl[i].setId(id);
				tabl[i].setNomer(nomer);
				tabl[i].setData(data_);
				tabl[i].setShifr_mat(shifr);
				tabl[i].setNazvan_mat(naimen);
				tabl[i].setKolichestvo(kolichestvo);
				tabl[i].setIdsort(id);
				tabl[i].setNomersort(nomer);
				tabl[i].setShifr_matsort(shifr);
				tabl[i].setNazvan_matsort(naimen);
				tabl[i].setKolichestvosort(kolichestvo);
			}
		}

		break;
	default:
		break;
	}


	SQLFreeHandle(SQL_HANDLE_STMT, SQLStatementHandle);
	SQLDisconnect(SQLConncetionHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SQLConncetionHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, SQLEnvHandle);

}