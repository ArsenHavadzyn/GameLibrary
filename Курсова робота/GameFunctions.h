#pragma once
#include "Libraries.h"
#include "GameMain.h"

/*****************************************************************\FIND GAME/********************************************************************/

inline string Game::findGame(string strfind, int& pAgain, int state) {
	pAgain = 0;
	int arrSize = objCounter;
	string result;
	for (int i = 0; i < arrSize; i++) {
		if (tempGamesDB[i][0] == "") {
			break;
		}
		pAgain++;
		if (tempGamesDB[i][0] == strfind)
		{
			if (state == 1) {
				design('=', 131, 1);
				cout << "#   ����� ���\t\t���������\t\t��������\t\t���������\t����\t\t���� ������      ֳ��" << endl;
				design('-', 131, 1);
				state++;
			}
			else if (state == 999) {
				return tempGamesDB[i][0];
			}
			result += to_string(i + 1) + ".  " + tempGamesDB[i][0];
			if (tempGamesDB[i][0].size() >= 7 && tempGamesDB[i][0].size() < 12) result += "\t";
			result += "\t" + tempGamesDB[i][1];
			if (tempGamesDB[i][1].size() >= 8 && tempGamesDB[i][1].size() <= 14) result += "\t";
			else if (tempGamesDB[i][1].size() < 8) result += "\t\t";
			result += "\t" + tempGamesDB[i][2];
			if (tempGamesDB[i][2].size() >= 8 && tempGamesDB[i][2].size() <= 15) result += "\t";
			result += "\t" + tempGamesDB[i][3];
			if (tempGamesDB[i][3].size() < 5) result += "\t";
			result += "\t" + tempGamesDB[i][4];
			if (tempGamesDB[i][4].size() < 12) result += "\t";
			result += "\t " + tempGamesDB[i][5] + " ��" + "\t" + tempGamesDB[i][6];
			return result;
		}
		else if (pAgain == arrSize) {
			strfind = "";
			cout << "���� ��� ���� � ��������. �������� ������" << endl;
			getline(cin, strfind);
			return findGame(strfind, pAgain, state);
		}
	}
}

/*****************************************************************\ADD & DELETE GAME/***************************************************************/

inline void Game::addNewGame() {
	design('=', 50, 0);
	cout << "\t\t\t��������� ��� �� ��������" << endl;
	design('=', 50, 0);
	cout << "������ ����� ���: ";
	cin.ignore();
	getline(cin, name);
	cout << "������ ���������� ���: ";
	getline(cin, author);
	cout << "������ ������� ���: ";
	getline(cin, publisher);
	cout << "������ ���������, �� ���� �������� ���: ";
	getline(cin, platform);
	cout << "������ ���� ���: ";
	getline(cin, genre);
	cout << "������ ���� ������ ��� (��): ";
	getline(cin, releaseDate);
	cout << "������ ���� ��� � Microsoft Store (UAN): ";
	getline(cin, price);
	price += " UAH";
	system("cls");
	cout << "\t��� ������ ������ �� ��������" << endl;
	writeIn(allGamesFile, "gamesDB.txt", name, author, publisher, platform, genre, releaseDate, price);
}

inline void Game::deleteGame() {
	system("cls");
	int n = 0;
	vector <string> gamesDBv;
	string temp;
	showAllGames(gameName);
	allGamesFile.open("gamesDB.txt", fstream::in | fstream::out);
	while (getline(allGamesFile, temp))
	{
		gamesDBv.push_back(temp);
	}
	allGamesFile.close();

	cout << "\n\n>>>"; cin >> n;
	n == 1 ? n-- : n = (n * 9);
	gamesDBv[n] = gamesDBv[n + 1] = gamesDBv[n + 2] = gamesDBv[n + 3] = gamesDBv[n + 4] = gamesDBv[n + 5] = gamesDBv[n + 6] = gamesDBv[n + 7] = gamesDBv[n + 8] = "";
	allGamesFile.open("gamesDB.txt", fstream::in | fstream::out | fstream::trunc);
	for (int i = 0; i < gamesDBv.size(); i++)
	{
		allGamesFile << gamesDBv[i] << "\n";
	}
	allGamesFile.close();
}

/*****************************************************************\FILTER GAMES/********************************************************************/

inline void Game::filterBy() {
	string dataToFilter;
	int filterCase = 0;
	design('=', 50, 1);
	cout << "\t������� ������������ ��������\n";
	design('=', 50, 1);
	cout << "���� ������������: \n"
		<< "1. Գ��������� �� ����������� ���\n"
		<< "2. Գ��������� �� �������� ���\n"
		<< "3. Գ��������� �� ����������� ���\n"
		<< "4. Գ��������� �� ������ ���\n"
		<< "5. Գ��������� �� ����� ������ ���\n"
		<< "6. Գ��������� �� ����� ��� (UAH)" << endl;
	cout << "������ ��� �������: ";
	cin >> filterCase;
	if (filterCase > 6 || filterCase < 1) {
		system("cls");
		filterBy();
	}
	cin.ignore();
	cout << "������ ��� ��� ������������: \n";
	getline(cin, dataToFilter);
	design('=', 50, 1);
	switch (filterCase)
	{
	case 1:
		filter(filterAuthor, dataToFilter);
		break;
	case 2:
		filter(filterPublisher, dataToFilter);
		break;
	case 3:
		filter(filterPlatform, dataToFilter);
		break;
	case 4:
		filter(filterGenre, dataToFilter);
		break;
	case 5:
		filter(filterReleaseDate, dataToFilter);
		break;
	case 6:
		filter(filterPrice, dataToFilter);
		break;
	default:
		break;
	}
}

inline void Game::filter(filterType ft, string dataToFilter) {
	int state = 0;
	int again = 0;
	int k = 1;
	int counter = 1;
	int arrSize = objCounter;
	string temp;
	shared_ptr <Game[]> allGames(new Game[arrSize]);
	for (int i = 0; i < arrSize; i++) {
		if (tempGamesDB[i][0] == "") {
			break;
		}
		allGames[i].name = tempGamesDB[i][0];
		allGames[i].author = tempGamesDB[i][1];
		allGames[i].publisher = tempGamesDB[i][2];
		allGames[i].platform = tempGamesDB[i][3];
		allGames[i].genre = tempGamesDB[i][4];
		allGames[i].releaseDate = tempGamesDB[i][5];
		allGames[i].price = tempGamesDB[i][6];
	}
	if (ft == filterAuthor) k = 1;
	else if (ft == filterPublisher) k = 2;
	else if (ft == filterPlatform) k = 3;
	else if (ft == filterGenre) k = 4;
	else if (ft == filterReleaseDate) k = 5;
	else if (ft == filterPrice) k = 6;
	system("pause");
	system("cls");
	for (int i = 0; i < arrSize; i++)
	{
		if (tempGamesDB[i][k] != dataToFilter) again++;
		if (tempGamesDB[i][k] == dataToFilter) {
			if (state == 0) {
				design('=', 131, 1);
				cout << "#   ����� ���\t\t���������\t\t��������\t\t���������\t����\t\t���� ������      ֳ��" << endl;
				design('-', 131, 1);
				state++;
			}
			cout << counter << ". ";
			if (counter < 10) cout << " ";
			cout << allGames[i];
			counter++;
		}
		if (again == arrSize) {
			cout << "�� ����� ������� �� �������� �����. �������� ������" << endl;
			system("pause");
			system("cls");
			filterBy();
		}
	}
	design('=', 131, 1);
}

inline string Game::getRandomPrice() {
	int r = rand() % 50;
	return tempGamesDB[r][6];
}
