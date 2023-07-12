// Курсова робота
#include "Libraries.h"
#include "GameMain.h"
#include "login.h"

using namespace std;    

void startScreen() {
	fstream greetings;
	string temp;
	Sleep(500);
	design2('=', 208, 1);
	cout << endl;
	greetings.open("greetings.txt", fstream::in | fstream::out);
	while (getline(greetings, temp)) {
		Sleep(150);
		cout << "\t\t\t\t\t" << temp << endl;
	}
	greetings.close();
	Sleep(500);
	cout << endl;
	design2('=', 208, 1);
	system("pause");
	system("cls");
}

bool mainPage() {
	startScreen();
	int action = 0;
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t\t\t\t"; design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t\t" << "Перелік дій:\n";
		cout << "\t\t\t\t\t\t"; design('=', 50, 1);
		cout << "\t\t\t\t\t\t\t\t" << "1.    Вхід\n"; 
		cout << "\t\t\t\t\t\t\t"; design('-', 30, 1);
		cout << "\t\t\t\t\t\t\t\t" << "2. Реєстрація\n"; 
		cout << "\t\t\t\t\t\t\t"; design('-', 30, 1);
		cout << "\t\t\t\t\t\t\t\t" << "3.   Вихід" << endl; 
		cout << "\t\t\t\t\t\t\t"; design('-', 30, 1);
	cout << "\t\t\t\t\t\t\t\t" << "Оберіть дію: ";
	cin >> action;
	cout << "\t\t\t\t\t\t"; design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t";
	switch (action) {
	case 1:
		system("pause");
		system("cls");
		mainLogin();
		break;
	case 2:
		system("pause");
		system("cls");
		mainRegister();
		break;
	case 3:
		exit(1);
		break;
	default:
		system("pause");
		system("cls");
		return 1;
		break;
	}
	return 1;
}



/*********************************************************\MAIN/************************************************************/



int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (mainPage());
	return 0;
}