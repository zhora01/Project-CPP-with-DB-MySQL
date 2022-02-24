#pragma once
#include<iostream>
#include"Sklad.h"
#include<vector>
#include<Windows.h>
#include <windows.h>
#include <sqlext.h>
#include<sqltypes.h>
#include<sql.h>
using namespace std;
void Connect(std::vector<Sklad> & tabl, char zapros[], int n);
void showSqlError(unsigned int handleType, const SQLHANDLE& handle);
