#include "stdafx.h"
#include "connect.h"
#include "Курсовая.h"
#include "sortirovka.h"
#include "proverka.h"
#include "Sklad.h"
#include <vector>
#include <iostream>
#include<Windows.h>
#include<string.h>
#include<stdio.h>
#include<string>
#include<fstream>
#include<cstring>



using std::string;
using std::vector;
#define MAX_LOADSTRING 100
HFONT hFont;
HWND hwndList;
HWND listBox;
HWND combobox1, combobox2;
HWND button1, button2, button3, button4, button5, button6, button7, button8, button9;
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
vector<Sklad>tabl;
sortirovka sortTabl;
string nomera;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    AddProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DELL(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    DELLALL(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Search(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Sort(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Redact(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Filtr(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Dop(HWND, UINT, WPARAM, LPARAM);

int poz;
int kol = 0;
LPCSTR textf[6] = { "равно", "не равно", "содержит", "начинается с", "заканчивается на" };
LPCSTR chislf[5] = { "равно", "не равно" ,"меньше","больше" };



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);


	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

	MSG msg;

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;
	HMENU submenu = CreatePopupMenu();
	AppendMenu(submenu, MF_STRING, 1003, "Загрузить из БД");
	AppendMenu(submenu, MF_STRING, 1002, "Выход");
	HMENU submenu1 = CreatePopupMenu();
	AppendMenu(submenu1, MF_STRING, 1001, "About");

	HMENU mainmenu = CreateMenu();
	AppendMenu(mainmenu, MF_POPUP, (UINT)submenu, "Файл");
	AppendMenu(mainmenu, MF_POPUP, (UINT)submenu1, "О программе");


	HWND hWnd = CreateWindowW(szWindowClass, L"1", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, mainmenu, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
void Print()
{
	char s[200];
	sprintf_s(s, "%+10s", "Ничего не найдено");
	SendMessage(listBox, LB_ADDSTRING, 0, (LPARAM)s);
}
void PrintList()
{
	char s[200];
	sprintf_s(s, "%+10s", "Ничего не найдено");
	SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)s);
}
void print()
{
	ofstream file("1.txt");
	char data[30];
	char nazvanie[30];
	char s[400];
	string info;
	int j;
	for (auto &i : tabl)
	{
		info = i.getData();
		for (j = 0; j < info.size(); j++)
		{
			data[j] = info[j];
		}
		data[j] = '\0';
		info = i.getNazvan_mat();
		for (j = 0; j < info.size(); j++)
		{
			nazvanie[j] = info[j];
		}
		nazvanie[j] = '\0';
		sprintf_s(s, "%-7d  %-8d  %-15s %-13d %-24s %d",
			i.getId(), i.getNomer(), data, i.getShifr_mat(), nazvanie, i.getKolichestvo());
		SendMessage(listBox, LB_ADDSTRING, 0, (LPARAM)s);
		file << s << endl;
	}
}

void printOnList()
{
	char data[30];
	char nazvanie[30];
	char s[400];
	string info;
	int j;
	for (auto &i : tabl)
	{
		if (i.getALL_Kolichestvo() != 0) {
			info = i.getData();
			for (j = 0; j < info.size(); j++)
			{
				data[j] = info[j];
			}
			data[j] = '\0';
			info = i.getNazvan_mat();
			for (j = 0; j < info.size(); j++)
			{
				nazvanie[j] = info[j];
			}
			nazvanie[j] = '\0';
			sprintf_s(s, "%-7d  %-8d  %-15s %-13d %-24s %d",
				i.getId(), i.getNomer(), data, i.getShifr_mat(), nazvanie, i.getALL_Kolichestvo());
			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)s);
		}
	}
}

void printSort()
{
	char data[30];
	char nazvanie[30];
	char s[400];
	string info;
	int j;
	for (auto &i : tabl)
	{
		info = i.getDatasort();
		for (j = 0; j < info.size(); j++)
		{
			data[j] = info[j];
		}
		data[j] = '\0';
		info = i.getNazvan_matsort();
		for (j = 0; j < info.size(); j++)
		{
			nazvanie[j] = info[j];
		}
		nazvanie[j] = '\0';
		sprintf_s(s, "%-7d  %-8d  %-15s %-13d %-24s %d",
			i.getIdsort(), i.getNomersort(), data, i.getShifr_matsort(), nazvanie, i.getKolichestvosort());
		SendMessage(listBox, LB_ADDSTRING, 0, (LPARAM)s);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int result;
	switch (message)
	{
	case WM_CREATE:
		button1 = CreateWindow(TEXT("button"), TEXT("ДОБАВИТЬ"), WS_CHILD | WS_VISIBLE, 800, 40, 200, 50, (HWND)hWnd, (HMENU)1, hInst, NULL);
		button2 = CreateWindow(TEXT("button"), TEXT("УДАЛИТЬ"), WS_VISIBLE | WS_CHILD, 1100, 40, 200, 50, (HWND)hWnd, (HMENU)2, hInst, NULL);
		button3 = CreateWindow(TEXT("button"), TEXT("УДАЛИТЬ ВСЕ"), WS_VISIBLE | WS_CHILD, 1100, 120, 200, 50, (HWND)hWnd, (HMENU)3, hInst, NULL);
		button4 = CreateWindow(TEXT("button"), TEXT("РЕДАКТИРОВАТЬ"), WS_VISIBLE | WS_CHILD, 800, 120, 200, 50, (HWND)hWnd, (HMENU)4, hInst, NULL);
		button5 = CreateWindow(TEXT("button"), TEXT("ПОИСК"), WS_VISIBLE | WS_CHILD, 800, 200, 200, 50, (HWND)hWnd, (HMENU)5, hInst, NULL);
		button6 = CreateWindow(TEXT("button"), TEXT("СОРТИРОВАТЬ"), WS_VISIBLE | WS_CHILD, 1100, 200, 200, 50, (HWND)hWnd, (HMENU)6, hInst, NULL);
		button7 = CreateWindow(TEXT("button"), TEXT("ДОП."), WS_VISIBLE | WS_CHILD, 1100, 280, 200, 50, (HWND)hWnd, (HMENU)7, hInst, NULL);
		button8 = CreateWindow(TEXT("button"), TEXT("ФИЛЬТРОВАТЬ"), WS_VISIBLE | WS_CHILD, 800, 280, 200, 50, (HWND)hWnd, (HMENU)8, hInst, NULL);
		listBox = CreateWindow(TEXT("ListBox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LBS_NOTIFY, 30, 40, 750, 490, hWnd, (HMENU)NULL, hInst, 0);

		break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		char Select[] = "SELECT * FROM tabl";
		switch (wmId)
		{
		case 1:
			DialogBox(hInst, MAKEINTRESOURCE(20), hWnd, (DLGPROC)AddProc);
			break;
		case 2:
			poz = SendMessage(listBox, LB_GETCURSEL, 0, 0);
			if (poz < 0)
			{
				MessageBox(hWnd, "Выберите нужную строку!", NULL, MB_OK | MB_ICONWARNING);
				break;
			}
			else
			{
				DialogBox(hInst, MAKEINTRESOURCE(21), hWnd, (DLGPROC)DELL);
			}
			break;
		case 3:
			if (kol == 0) {
				MessageBox(
					hWnd,
					"Добавте строку или загрузите БД",
					NULL,
					MB_OK | MB_ICONWARNING
				);
				return FALSE;
			}
			DialogBox(hInst, MAKEINTRESOURCE(22), hWnd, (DLGPROC)DELLALL);
			break;
		case 4:
			poz = SendMessage(listBox, LB_GETCURSEL, 0, 0);
			if (poz < 0)
			{
				MessageBox(hWnd, "Выберите нужную строку!", NULL, MB_OK | MB_ICONWARNING);
				break;
			}
			else {
				DialogBox(hInst, MAKEINTRESOURCE(25), hWnd, (DLGPROC)Redact);
			}
			break;
		case 5:
			if (kol == 0) {
				MessageBox(
					hWnd,
					"Добавте строку или загрузите БД",
					NULL,
					MB_OK | MB_ICONWARNING
				);
				return FALSE;
			}
			DialogBox(hInst, MAKEINTRESOURCE(23), hWnd, (DLGPROC)Search);
			break;
		case 6:
			if (kol == 0) {
				MessageBox(
					hWnd,
					"Добавте строку или загрузите БД",
					NULL,
					MB_OK | MB_ICONWARNING
				);
				return FALSE;
			}
			DialogBox(hInst, MAKEINTRESOURCE(24), hWnd, (DLGPROC)Sort);
			break;
		case 7:
			if (kol == 0) {
				MessageBox(
					hWnd,
					"Добавте строку или загрузите БД",
					NULL,
					MB_OK | MB_ICONWARNING
				);
				return FALSE;
			}
			tabl.clear();
			Connect(tabl, Select, 1003);
			DialogBox(hInst, MAKEINTRESOURCE(27), hWnd, (DLGPROC)Dop);
			break;
		case 8:
			if (kol == 0) {
				MessageBox(
					hWnd,
					"Добавте строку или загрузите БД",
					NULL,
					MB_OK | MB_ICONWARNING
				);
				return FALSE;
			}
			DialogBox(hInst, MAKEINTRESOURCE(26), hWnd, (DLGPROC)Filtr);
			break;

		case 1001:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case 1002:
			result = MessageBox(
				hWnd,
				"Вы уверены?",
				"Подтверждение действия",
				MB_YESNO | MB_ICONQUESTION
			);
			if (result == IDYES) {
				DestroyWindow(hWnd);
			}
			break;
		case 1003:
			SendMessage(listBox, LB_RESETCONTENT, 0, 0);
			tabl.clear();
			Connect(tabl, Select, 1003);
			kol = tabl.size();
			print();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_CLOSE:
		result = MessageBox(
			hWnd,
			"Вы уверены?",
			"Подтверждение действия",
			MB_YESNO | MB_ICONQUESTION
		);
		if (result == IDYES) {
			DestroyWindow(hWnd);
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		HFONT hFont;
		static LOGFONT font;

		font.lfHeight = 17;
		font.lfWeight = 700;
		lstrcpy((LPSTR)&font.lfFaceName, "Courier");
		hFont = CreateFontIndirect(&font);
		SendMessage(listBox, WM_SETFONT, (WPARAM)hFont, TRUE);
		SendMessage(hwndList, WM_SETFONT, (WPARAM)hFont, TRUE);


		TextOut(hdc, 30, 10, "id", 2);
		TextOut(hdc, 60, 10, "Номер накладной", 15);
		TextOut(hdc, 190, 10, "Дата накладной", 14);
		TextOut(hdc, 320, 10, "Шифр материала", 14);
		TextOut(hdc, 470, 10, "Наименование материала", 22);
		TextOut(hdc, 680, 10, "Количество", 10);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


LRESULT CALLBACK AddProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	proverka chek = proverka();
	int wmId;
	int wmEvent;
	char SQLQuery[200];
	string dateW;

	char nomer[10];
	char data[15];
	char shifr_mat[7];
	char nazvan_mat[25];
	char kolichestvo[10];

	string zapros;
	char s[100];
	char Select[] = "SELECT * from tabl";
	switch (uMsg)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDOK:
			GetDlgItemText(hDlg, 10, nomer, 10);
			try
			{
				chek.CheckNomer(nomer);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
			
			GetDlgItemText(hDlg, 11, s, 3);
			try
			{
				chek.CheckDD(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
			if (strlen(s) == 1)
			{
				dateW += "0";
				dateW += s;
				dateW += ".";
			}
			else
			{
				dateW += s;
				dateW += ".";
			}
			GetDlgItemText(hDlg, 12, s, 3);
			try
			{
				chek.CheckMM(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
			if (strlen(s) == 1)
			{
				dateW += "0";
				dateW += s;
				dateW += ".";
			}
			else
			{
				dateW += s;
				dateW += ".";
			}
			GetDlgItemText(hDlg, 13, s, 5);
			try
			{
				chek.CheckYY(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
				dateW += s;

			int i;
			for (i = 0; i < dateW.size(); i++)
			{
				data[i] = dateW[i];
			}
			data[i] = '\0';
			dateW.clear();

			GetDlgItemText(hDlg, 14, shifr_mat, 7);
			try
			{
				chek.CheckShifr(shifr_mat);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}

			GetDlgItemText(hDlg, 15, nazvan_mat, 25);
			try
			{
				chek.CheckNaim(nazvan_mat);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}

			GetDlgItemText(hDlg, 16, kolichestvo, 4);
			try
			{
				chek.CheckKol(kolichestvo);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}


			zapros += "INSERT INTO tabl (nomer,data_,shifr,naimen,kolichestvo) VALUES ('";
			zapros += nomer;
			zapros += "', '";
			zapros += data;
			zapros += "', '";
			zapros += shifr_mat;
			zapros += "', '";
			zapros += nazvan_mat;
			zapros += "', '";
			zapros += kolichestvo;
			zapros += "')";
			for (i = 0; i < zapros.size(); i++)
			{
				SQLQuery[i] = zapros[i];
			}
			SQLQuery[i] = '\0';
			Connect(tabl, SQLQuery, 1);

			tabl.clear();
			Connect(tabl, Select, 1003);
			SendMessage(listBox, LB_RESETCONTENT, 0, 0);
			print();

			EndDialog(hDlg, 1);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 1);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 1);
		break;
		return true;
	}
	return false;
}

LRESULT CALLBACK DELL(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId;

	switch (uMsg)
	{

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDOK:

			SendMessage(listBox, LB_DELETESTRING, (WPARAM)poz, (LPARAM)lParam);
			tabl.erase(tabl.begin() + poz);

			EndDialog(hDlg, 1);
			break;
		case IDCANCEL:

			EndDialog(hDlg, 1);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 1);
		break;
		return true;
	}
	return false;
}

LRESULT CALLBACK DELLALL(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	switch (uMsg)
	{

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDYES:

			SendMessage(listBox, LB_RESETCONTENT, 0, 0);
			tabl.clear();

			EndDialog(hDlg, 1);
			break;
		case IDCANCEL:

			EndDialog(hDlg, 1);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 1);
		break;
		return true;
	}
	return false;
}

LRESULT CALLBACK Search(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	int wmEvent;
	static int x1;
	char s[100];
	char sort[100];
	string search;
	string dateW;
	switch (uMsg)
	{

	case WM_INITDIALOG:


		x1 = 1;
		CheckRadioButton(hDlg, 3, 7, 3);
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId)
		{

		case 3:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_RESTORE
			);
			
			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_HIDE
			);
			x1 = 1;
			break;
		case 4:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_HIDE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_RESTORE
			);
			x1 = 2;
			break;
		case 5:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_RESTORE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_HIDE
			);
			x1 = 3;
			break;
		case 6:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_RESTORE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_HIDE
			);
			x1 = 4;
			break;
		case 7:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_RESTORE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_HIDE
			);
			x1 = 5;
			break;
		case IDOK:
			switch (x1)
			{
			case 1:
				GetDlgItemText(hDlg, 10, s, 40);
				search += "select * from tabl Where nomer = '"; search += s; search += "'";
				int i;
				for (i = 0; i < search.size(); i++) {
					sort[i] = search[i];
				}
				sort[i] = '\0';
				tabl.clear();
				Connect(tabl, sort, 1003);
				if (tabl.empty() == true) { SendMessage(listBox, LB_RESETCONTENT, 0, 0); Print(); }
				else { SendMessage(listBox, LB_RESETCONTENT, 0, 0); print(); }
				break;
			case 2:
				GetDlgItemText(hDlg, 11, s, 40);
				if (strlen(s) == 1)
				{
					dateW += "0";
					dateW += s;
					dateW += ".";
				}
				else
				{
					dateW += s;
					dateW += ".";
				}
				GetDlgItemText(hDlg, 12, s, 40);
				if (strlen(s) == 1)
				{
					dateW += "0";
					dateW += s;
					dateW += ".";
				}
				else
				{
					dateW += s;
					dateW += ".";
				}
				GetDlgItemText(hDlg, 13, s, 40);
				dateW += s;
				search += "select * from tabl Where data_ = '"; search += dateW; search += "'";
				for (i = 0; i < search.size(); i++) {
					sort[i] = search[i];
				}
				sort[i] = '\0';
				tabl.clear();
				Connect(tabl, sort, 1003);
				if (tabl.empty() == true) { SendMessage(listBox, LB_RESETCONTENT, 0, 0); Print(); }
				else { SendMessage(listBox, LB_RESETCONTENT, 0, 0); print(); }
				break;
			case 3:
				GetDlgItemText(hDlg, 10, s, 40);
				search += "select * from tabl Where shifr = '"; search += s; search += "'";
				for (i = 0; i < search.size(); i++) {
					sort[i] = search[i];
				}
				sort[i] = '\0';
				tabl.clear();
				Connect(tabl, sort, 1003);
				if (tabl.empty() == true) { SendMessage(listBox, LB_RESETCONTENT, 0, 0); Print(); }
				else { SendMessage(listBox, LB_RESETCONTENT, 0, 0); print(); }
				break;
			case 4:
				GetDlgItemText(hDlg, 10, s, 40);
				search += "select * from tabl Where naimen = '"; search += s; search += "'";
				for (i = 0; i < search.size(); i++) {
					sort[i] = search[i];
				}
				sort[i] = '\0';
				tabl.clear();
				Connect(tabl, sort, 1003);
				if (tabl.empty() == true) { SendMessage(listBox, LB_RESETCONTENT, 0, 0); Print(); }
				else { SendMessage(listBox, LB_RESETCONTENT, 0, 0); print(); }

				break;
				EndDialog(hDlg, 1);
				break;
			case 5:
				GetDlgItemText(hDlg, 10, s, 40);
				search += "select * from tabl Where kolichestvo = '"; search += s; search += "'";
				for (i = 0; i < search.size(); i++) {
					sort[i] = search[i];
				}
				sort[i] = '\0';
				tabl.clear();
				Connect(tabl, sort, 1003);
				if (tabl.empty() == true) { SendMessage(listBox, LB_RESETCONTENT, 0, 0); Print(); }
				else { SendMessage(listBox, LB_RESETCONTENT, 0, 0); print(); }

				break;
				EndDialog(hDlg, 1);
				break;
			}
		case IDCANCEL:
			EndDialog(hDlg, 1);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 1);
		break;
		return true;
	}
	return false;
}

LRESULT CALLBACK Sort(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	int wmEvent;
	static int x1, x2;

	switch (uMsg)
	{

	case WM_INITDIALOG:

		CheckRadioButton(hDlg, 3, 7, 3);
		CheckRadioButton(hDlg, 8, 9, 8);
		x1 = 1;
		x2 = 1;
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case 3:x1 = 1;
			break;
		case 4:x1 = 2;
			break;
		case 5:x1 = 3;
			break;
		case 6:x1 = 4;
			break;
		case 7:x1 = 5;
			break;
		case 8:x2 = 1;
			break;
		case 9:x2 = 2;
			break;
		case IDOK:
			switch (x1)
			{
			case 1:
				sortTabl.sortNomer(tabl, x2);
				break;
			case 2:
				sortTabl.sortData(tabl, x2);
				break;
			case 3:
				sortTabl.sortShifr(tabl, x2);
				break;
			case 4:
				sortTabl.sortNaimen(tabl, x2);
				break;
			case 5:
				sortTabl.sortKol(tabl, x2);
				break;
			}
			SendMessage(listBox, LB_RESETCONTENT, 0, 0);
			printSort();
			EndDialog(hDlg, 1);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 1);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 1);
		break;
		return true;
	}

	return false;
}

LRESULT CALLBACK Redact(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	proverka chek = proverka();
	int wmId;
	int wmEvent;
	int k, l;
	char SQLQuery[200];
	string dateW;
	int perem;
	char nomer[10];
	char data[15];
	char shifr_mat[7];
	char nazvan_mat[25];
	char kolichestvo[10];

	string zapros;
	string update;
	char s[200];
	char str[200];
	char Select[] = "SELECT * from tabl";
	switch (uMsg)
	{
	case WM_INITDIALOG:

		int i;
		update = std::to_string(tabl[poz].getNomer());
		for (i = 0; i < update.size(); i++) { str[i] = update[i]; }
		str[i] = '\0';
		SetDlgItemText(hDlg, 10, str);
		update.clear();
		
		update = tabl[poz].getData();
		for (i = 0; i < 2; i++) { str[i] = update[i]; }
		str[i] = '\0';
		SetDlgItemText(hDlg, 11, str);
		for (i = 0; i < 2; i++) { str[i] = update[i + 3]; }
		str[i] = '\0';
		SetDlgItemText(hDlg, 12, str);
		for (i = 0; i < 4; i++) { str[i] = update[i + 6]; }
		str[i] = '\0';
		SetDlgItemText(hDlg, 13, str);
		update.clear();

		update = std::to_string(tabl[poz].getShifr_mat());
		for (i = 0; i < update.size(); i++) { str[i] = update[i]; }
		str[i] = '\0';
		SetDlgItemText(hDlg, 14, str);
		update.clear();

		update = tabl[poz].getNazvan_mat();
		for (i = 0; i < update.size(); i++) { str[i] = update[i]; }
		str[i] = '\0';
		SetDlgItemText(hDlg, 15, str);
		update.clear();

		update = std::to_string(tabl[poz].getKolichestvo());
		for (i = 0; i < update.size(); i++) { str[i] = update[i]; }
		str[i] = '\0';
		SetDlgItemText(hDlg, 16, str);
		update.clear();

		break;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDOK:
			GetDlgItemText(hDlg, 10, nomer, 10);
			try
			{
				chek.CheckNomer(nomer);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}

			GetDlgItemText(hDlg, 11, s, 3);
			try
			{
				chek.CheckDD(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}

			if (strlen(s) == 1)
			{
				dateW += "0";
				dateW += s;
				dateW += ".";
			}
			else
			{
				dateW += s;
				dateW += ".";
			}
			GetDlgItemText(hDlg, 12, s, 3);
			try
			{
				chek.CheckMM(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
			if (strlen(s) == 1)
			{
				dateW += "0";
				dateW += s;
				dateW += ".";
			}
			else
			{
				dateW += s;
				dateW += ".";
			}
			GetDlgItemText(hDlg, 13, s, 5);
			try
			{
				chek.CheckYY(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
			dateW += s;

			int i;
			for (i = 0; i < dateW.size(); i++)
			{
				data[i] = dateW[i];
			}
			data[i] = '\0';
			dateW.clear();
			l = 0;
			SendMessage(listBox, LB_GETTEXT, poz, (LPARAM)str);
			k = strlen(str);
			str[k] = ' ';
			str[k + 1] = '\0';
			k = 0;
			for (i = 0; i < strlen(str); i++)
			{
				if (str[i] != ' ')
				{
					s[l++] = str[i];
				}
				else
				{
					s[l] = '\0';
					break;
				}
			}

			GetDlgItemText(hDlg, 14, shifr_mat, 7);
			try
			{
				chek.CheckShifr(shifr_mat);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}

			GetDlgItemText(hDlg, 15, nazvan_mat, 25);
			try
			{
				chek.CheckNaim(nazvan_mat);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}

			GetDlgItemText(hDlg, 16, kolichestvo, 4);
			try
			{
				chek.CheckKol(kolichestvo);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}

			zapros += "Update tabl SET nomer= '";
			zapros += nomer;
			zapros += "', data_= '";
			zapros += data;
			zapros += "', shifr= '";
			zapros += shifr_mat;
			zapros += "', naimen= '";
			zapros += nazvan_mat;
			zapros += "', kolichestvo= '";
			zapros += kolichestvo;
			zapros+= "' Where id = '";
			zapros+=s;
			zapros+="'";
			for (i = 0; i < zapros.size(); i++)
			{
				SQLQuery[i] = zapros[i];
			}
			SQLQuery[i] = '\0';
			Connect(tabl, SQLQuery, 1);
			SendMessage(listBox, LB_RESETCONTENT, 0, 0);
			tabl.clear();
			Connect(tabl, Select, 1003);
			print();
			EndDialog(hDlg, 1);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 1);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 1);
		break;
		return true;
	}
	return false;
}

LRESULT CALLBACK Filtr(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	int wmEvent;
	static int x1;
	char s[200];
	char str[200];
	char filtr[200];
	string zapros;
	string a = "равно"; string b = "не равно"; string c = "содержит"; string d = "начинается с"; string e = "заканчивается на";
	string f = "меньше"; string g = "больше";
	switch (uMsg)
	{

	case WM_INITDIALOG:
		combobox2 = GetDlgItem(hDlg, 14);
		combobox1 = GetDlgItem(hDlg, 15);

		for (int i = 0; i < 5; i++)
		{
			SendMessage(combobox1, CB_ADDSTRING, 0, (LPARAM)textf[i]);
		}
		for (int i = 0; i < 4; i++)
		{
			SendMessage(combobox2, CB_ADDSTRING, 0, (LPARAM)chislf[i]);
		}

		SendMessage(combobox1, CB_SETCURSEL, 0, 0);
		SendMessage(combobox2, CB_SETCURSEL, 0, 0);
		CheckRadioButton(hDlg, 3, 7, 3);
		x1 = 1;
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		switch (wmId)
		{
		case 3:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_RESTORE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 14),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 15),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 16),
				SW_HIDE
			);
			x1 = 1;
			break;
		case 4:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_HIDE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 14),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 15),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 16),
				SW_HIDE
			);
			x1 = 2;
			break;
		case 5:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_RESTORE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 14),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 15),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 16),
				SW_HIDE
			);
			x1 = 3;
			break;
		case 6:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 16),
				SW_RESTORE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 15),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 14),
				SW_HIDE
			);
			x1 = 4;
			break;
		case 7:
			ShowWindow
			(
				GetDlgItem(hDlg, 10),
				SW_RESTORE
			);

			ShowWindow
			(
				GetDlgItem(hDlg, 11),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 12),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 13),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 14),
				SW_RESTORE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 15),
				SW_HIDE
			);
			ShowWindow
			(
				GetDlgItem(hDlg, 16),
				SW_HIDE
			);
			x1 = 5;
			break;
		case IDOK:
			int i;
			switch (x1)
			{
			case 1:
				GetDlgItemText(hDlg, 14, str, 20);
				str[strlen(str)] = '\0';
				if (str == a) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where nomer = '";
					
					zapros += s;
					
					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == b) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where nomer <> '";
					
					zapros += s;
					
					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == f) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where nomer < '";
					
					zapros += s;
				
					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == g) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where nomer > '";
					
					zapros += s;
					
					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';

				}
				if (str != a && str != b && str != f && str != g) {
					MessageBox(hDlg, "Неккоректный параметр фильтрации!", NULL, MB_OK);
					return false;
				}
				break;
			case 2:
				GetDlgItemText(hDlg, 14, str, 20);
				str[strlen(str)] = '\0';
				if (str == a) {
					GetDlgItemText(hDlg, 11, s, 3);
					zapros += "select * from tabl Where data_ = '";
					zapros += s;
					zapros += '.';
					GetDlgItemText(hDlg, 12, s, 3);
					zapros += s;
					zapros += '.';
					GetDlgItemText(hDlg, 13, s, 5);
					zapros += s;
					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == b) {

					GetDlgItemText(hDlg, 11, s, 3);
					zapros += "select * from tabl Where data_ <> '";
					zapros += s;
					zapros += '.';
					GetDlgItemText(hDlg, 12, s, 3);
					zapros += s;
					zapros += '.';
					GetDlgItemText(hDlg, 13, s, 5);
					zapros += s;
					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == f) {
					GetDlgItemText(hDlg, 11, s, 3);
					zapros += "select * from tabl Where data_ < '";
					zapros += s;
					zapros += '.';
					GetDlgItemText(hDlg, 12, s, 3);
					zapros += s;
					zapros += '.';
					GetDlgItemText(hDlg, 13, s, 5);
					zapros += s;
					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == g) {
					GetDlgItemText(hDlg, 11, s, 3);
					zapros += "select * from tabl Where data_ > '";
					zapros += s;
					zapros += '.';
					GetDlgItemText(hDlg, 12, s, 3);
					zapros += s;
					zapros += '.';
					GetDlgItemText(hDlg, 13, s, 5);
					zapros += s;
					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';

				}
				if (str != a && str != b && str != f && str != g) {
					MessageBox(hDlg, "Неккоректный параметр фильтрации!", NULL, MB_OK);
					return false;
				}
				break;
			case 3:

				GetDlgItemText(hDlg, 14, str, 20);
				str[strlen(str)] = '\0';
				if (str == a) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where shifr = '";

					zapros += s;

					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == b) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where shifr <> '";

					zapros += s;

					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == f) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where shifr < '";

					zapros += s;

					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == g) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where shifr > '";

					zapros += s;

					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';

				}
				if (str != a && str != b && str != f && str != g) {
					MessageBox(hDlg, "Неккоректный параметр фильтрации!", NULL, MB_OK);
					return false;
				}
				break;
			case 4:
				GetDlgItemText(hDlg, 15, str, 20);
				str[strlen(str)] = '\0';
				if (str == a) {
					GetDlgItemText(hDlg, 16, s, 25);
					zapros += "select * from tabl Where naimen = '"; zapros += s; zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == b) {
					GetDlgItemText(hDlg, 16, s, 25);
					zapros += "select * from tabl Where naimen <> '"; zapros += s; zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == c) {
					GetDlgItemText(hDlg, 16, s, 25);
					zapros += "select * from tabl Where naimen LIKE '%"; zapros += s; zapros += "%'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == d) {
					GetDlgItemText(hDlg, 16, s, 25);
					zapros += "select * from tabl Where naimen LIKE '"; zapros += s; zapros += "%'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == e) {
					GetDlgItemText(hDlg, 16, s, 25);
					zapros += "select * from tabl Where naimen LIKE '%"; zapros += s; zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str != a && str != b && str != c && str != d && str != e) {
					MessageBox(hDlg, "Неккоректный параметр фильтрации!", NULL, MB_OK);
					return false;
				}
				break;
				
			case 5:
				GetDlgItemText(hDlg, 14, str, 20);
				str[strlen(str)] = '\0';
				if (str == a) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where kolichestvo = '";

					zapros += s;

					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == b) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where kolichestvo <> '";

					zapros += s;

					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == f) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where kolichestvo < '";

					zapros += s;

					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';
				}
				if (str == g) {
					GetDlgItemText(hDlg, 10, s, 10);
					zapros += "select * from tabl Where kolichestvo > '";

					zapros += s;

					zapros += "'";
					for (i = 0; i < zapros.size(); i++)
					{
						filtr[i] = zapros[i];
					}
					filtr[i] = '\0';

				}
				if (str != a && str != b && str != f && str != g) {
					MessageBox(hDlg, "Неккоректный параметр фильтрации!", NULL, MB_OK);
					return false;
				}
				break;
			}
			tabl.clear();
			Connect(tabl, filtr, 1003);
			SendMessage(listBox, LB_RESETCONTENT, 0, 0);
			print();
			EndDialog(hDlg, 1);
			break;
		case IDCANCEL:
			EndDialog(hDlg, 1);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 1);
		break;
		return true;
	}

	return false;
}



LRESULT CALLBACK Dop(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	proverka chek = proverka();
	char Select[] = "SELECT * from tabl";
	int wmId;
	int wmEvent;
	string update1, update2, update3;
	string update11, update22, update33;
	string nazvan_mat,data,mm,yy;
	int summa = 0;
	string proverka1;
	string proverka2;
	string proverka3;
	int proverka = 0;
	char s[100];
	hwndList = GetDlgItem(hDlg, 9);
	switch (uMsg)
	{

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDOK:
			proverka = 0;
			int i;
			int j;
			int k;
			GetDlgItemText(hDlg, 10, s, 25);
			try
			{
				chek.CheckNaim(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
			for (i = 0; i < strlen(s); i++) {
				nazvan_mat += s[i];
			}
			GetDlgItemText(hDlg, 11, s, 3);
			try
			{
				chek.CheckMM(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
			if (strlen(s) == 1) {
				mm += "0";
				mm += s[0];
			}

			else {
				for (i = 0; i < strlen(s); i++) {
					mm += s[i];
				}
			}
			GetDlgItemText(hDlg, 12, s, 5);
			try
			{
				chek.CheckYY(s);
			}
			catch (const std::exception&err) {
				MessageBox(hDlg, err.what(), NULL, MB_OK);
				return FALSE;
			}
			for (i = 0; i < strlen(s); i++) {
				yy += s[i];
			}

			update1 = nazvan_mat;
			update2 = mm;
			update3 = yy;
			k = 0;
			for (int i = 0; i < kol; i++) {

				proverka1 = update1;
				proverka2 = update2;
				proverka3 = update3;

				data = tabl[i].getData();
				for (k = 3; k <= 5; k++) {
					mm[k - 3] = data[k];
				}

				mm[2] = '\0';
				for (k = 6; k <= 9; k++) {
					yy[k - 6] = data[k];
				}
				yy[4] = '\0';
				update11 = tabl[i].getNazvan_mat();
				update22 = mm;
				update33 = yy;

				if (update11 == proverka1 && update22 == proverka2 && update33 == proverka3) {

					summa += tabl[i].getKolichestvo();
					nomera += i;
					proverka++;
				}
			}
			if (proverka != 0) {
				j = 0;
				for (int i = 0; i < kol; i++) {
					if (nomera[j] == i) {
						tabl[i].setALL_Kolichestvo(summa);
						j++;
					}
				}
			SendMessage(hwndList, LB_RESETCONTENT, 0, 0);
			printOnList();
			tabl.clear();
			Connect(tabl, Select, 1003);
			nomera.clear();
			}
			else{
				PrintList();
			}
	
			break;
		case IDCANCEL:
			EndDialog(hDlg, 1);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 1);
		break;
		return true;

	case WM_PAINT:
		HFONT hFont;
		static LOGFONT font;

		font.lfHeight = 16;
		font.lfWeight = 700;
		lstrcpy((LPSTR)&font.lfFaceName, "Courier");
		hFont = CreateFontIndirect(&font);
		SendMessage(hwndList, WM_SETFONT, (WPARAM)hFont, TRUE);
		break;
	}

	return false;
}