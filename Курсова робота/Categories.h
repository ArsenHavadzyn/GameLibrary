#pragma once
#include "Libraries.h"
#include "GameMain.h"

/*****************************************************************\CATEGORIES/********************************************************************/

inline void Game::writeCategory(string strfind, int& pAgain) {
	pAgain = 0;
	int arrSize = objCounter;
	cout << ">>>\t";
	getline(cin, strfind);
	for (int i = 0; i < arrSize; i++) {
		if (tempGamesDB[i][0] == "") {
			break;
		}
	}

	for (int i = 0; i < arrSize; i++)
	{
		pAgain++;
		if (tempGamesDB[i][0] == strfind)
		{
			writeIn(categoriesFile, "categories.txt", tempGamesDB[i][0]);
			cout << "Гру успішно додано!" << endl;
			break;
		}
	}
}

inline void Game::createCategory() {
	cin.ignore();
	string categoryName, tempGameName;
	int nta = 0;
	int again = 0;
	int* pAgain = &again;
	categoriesFile.open("categories.txt", fstream::in | fstream::out | fstream::app);
	cout << "Створення категорій" << endl;
	cout << "Введіть назву категорії: ";
	getline(cin, categoryName);
	categoriesFile << design('.', 32, 0) << categoryName << "\n" << design('=', 32, 0);
	categoriesFile.close();
	showAllGames(gameName);
	cout << "Скільки ігор слід додати: ";
	cin >> nta;
	cin.ignore();
	cout << "Введіть назву гри, яку бажаєте додати: " << endl;
	for (int i = 0; i < nta; i++)
	{
		writeCategory(tempGameName, *pAgain);
		if (*pAgain == objCounter)
		{
			cout << "Шуканої вами гри не знайдено. Повторіть спробу" << endl;
			nta++;
		}
	}
	cout << endl;
}

class Category {
public:
	Category()
	{
		int tempCounter = 0;
		int tempCounter2 = 0;
		categoriesFile.open("categories.txt", fstream::in | fstream::out);
		while (getline(categoriesFile, tempData))
		{
			if (tempData == "................................") {
				cName = "";
				tempCounter2 = 0;
				continue;
			}
			else if (cName == "") {
				cName = tempData;
				cNamesList[tempCounter] = cName;
				tempCounter++;
			}
			else if (tempData == "================================") {
				continue;
			}
			else {
				gameName = tempData;
				gameNamesList[tempCounter][tempCounter2] = gameName;
				gameCounter++;
				tempCounter2++;
				gameName = "";
			}
		}
		categoriesFile.close();
	}
	inline void showCategories();
	int countOfCategories() {
		fstream categoriesFile;
		string countTemp;
		int count = 0;
		categoriesFile.open("categories.txt", fstream::in | fstream::out);
		while (getline(categoriesFile, countTemp))
		{
			if (countTemp == "................................")
			{
				count++;
			}
		}
		categoriesFile.close();
		return count;
	}
	void printCategories(int CN) {
	int SIZE = 0;
	while(gameNamesList[CN][SIZE] != "") {
		SIZE++;
	}
	for (int i = 0; i < SIZE; i++)
	{
		cout << i+1 << ". " << gameNamesList[CN][i] << endl;
	}
	design('=', 30, 1);
}
	~Category() {
	delete[] cNamesList;
}
private:
	fstream categoriesFile;
	string cName = "";
	string *cNamesList = new string[countOfCategories()];
	string tempData;
	string gameName;
	string gameNamesList[15][15];
	int counter = 0;
	int gameCounter = 0;
};

inline void Category::showCategories() {
	int choice = 0;
	string thisCategory;
	design('=', 45, true);
	cout << "Список категорій\t" << endl;
	design("=", 45, true);
	for (int i = 0; i < countOfCategories(); i++)
	{
		cout << i+1 << ". " << cNamesList[i] << endl;
	}
	design('=', 45, true);
	cout << "Оберіть категорію: ";
	cin >> choice;
	design('=', 45, true);
	system("pause");
	system("cls");
	if (choice > 0 && choice <= countOfCategories())
	{
		thisCategory = cNamesList[choice-1];
		design('=', 30, 1);
		cout << thisCategory << endl;
		design('=', 30, 1);
		printCategories(choice);
	}
	else {
		while (!(choice > 0 && choice < countOfCategories())) {
			cout << "\t\tКатегорії з таким номером не знайдено.\nПовторіть спробу: ";
			choice = 0;
			cin >> choice;
		}
	}
	
} 
