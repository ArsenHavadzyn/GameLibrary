#pragma once
#include "Libraries.h"
#include "GameMain.h"

/*****************************************************************\LEAVING SOON LIST/********************************************************************/
class leaveSoon : public Game {
public:
	inline void updateLeavingSoonList();
	inline void showLeavingSoonList();
private:
	fstream leavingSoonFile;
};

inline void leaveSoon::updateLeavingSoonList() {
	string gameToDelete;
	string deleteDate;
	int again = 0;
	int* pAgain = &again;
	showAllGames(gameName);
	cout << endl;
	cout << "Введіть назву гри-кандидата на видалення з сервісу:\n";
	cin.ignore();
	getline(cin, gameToDelete);
	cout << "Введіть дату видалення цієї гри: (dd.mm.yyyy)" << endl;
	getline(cin, deleteDate);
	if (findGame(gameToDelete, *pAgain, 999).size() > 0)
	{
		leavingSoonFile.open("leavingGames.txt", fstream::in | fstream::out | fstream::app);
		leavingSoonFile << findGame(gameToDelete, *pAgain, 999) << "\n" << deleteDate << "\n\n";
		leavingSoonFile.close();
	}
}

inline void leaveSoon::showLeavingSoonList() {
	string temp;
	bool skip = false;
	bool tempCounter = false;
	int counter = 0;
	cout << "Ігри, що скоро покинуть бібліотеку" << endl;
	design('=', 42, 1);
	leavingSoonFile.open("leavingGames.txt", fstream::in | fstream::out);
	cout << "#  Гра\t\t\tПокине бібліотеку" << endl;
	design('-', 42, 1);
	while (getline(leavingSoonFile, temp)) {
		if (temp == "") {
			if (skip) cout << endl;
			skip = true;
			tempCounter = true;
			counter++;
			continue;
		}
		if (tempCounter) cout << counter << ". ";
		if (temp != "") {
			cout << temp << "\t   ";
			if (temp.size() < 12) cout << "\t   ";
			tempCounter = false;
		}
	}
	design('=', 42, 1);
	leavingSoonFile.close();
}
