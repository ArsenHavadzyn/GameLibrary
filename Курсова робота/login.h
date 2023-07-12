#pragma once
#include "Libraries.h"
#include "GameMain.h"
#include "Categories.h"
#include "LeaveList.h"
#include "GameFunctions.h"

/***************************************************\LOGIN/***********************************************************/

class Admin;
class User;

class Person {
public:
	virtual void loginAs() = 0;
	virtual bool showActions() = 0;
};

class User : public Person {
public:
	User() {
		fstream userInfo;
		userInfo.open("userInfo.txt", fstream::in | fstream::out);
		while (getline(userInfo, tempData))
		{
			if (tempData == "-------------------------") {
				continue;
			}
			else
			{
				if (login.size() == 0) {
					login = tempData;
					userDB[dbI][dbJ] = login;
					dbJ++;
				}
				else {
					password = tempData;
					userDB[dbI][dbJ] = password;
					login = "";
					password = "";
					dbI++;
					dbJ = 0;

				}

			}
		}
		userInfo.close();
	}

	void loginAs() override;

	inline bool showActions() override;

	inline void showUserInfo() {
		cout << "\t\tІнформація про користувача " << endl;
		design('=', 65, 1);
		int i = 0;
		string myInfo[6];
		string fileName = "users/" + loginToCheck + "_info.txt";
		string temp = "";
		fstream detailInfo;
		detailInfo.open(fileName, fstream::in | fstream::out);
		while (getline(detailInfo, temp))
		{
			myInfo[i] = temp;
			cout << "\t" << infoTitles[i] << "\t\t" << myInfo[i] << endl;
			i++;
		}
		detailInfo.close();
		design('=', 65, 1);
	}

	inline void updateUserInfo();

	inline bool userLibraryMenu();

	inline void updateUserLibrary(bool mode);

	inline void showUserLibrary();
private:
	fstream userLib;
	string infoTitles[6] = { 
		"E-mail:\t\t", "Номер телефону:\t", "Дата народження:", "Улюблений жанр:\t", "Платформа:\t" 
	};
	string userDB[100][2];
	string loginToCheck;
	string passToCheck;
	string tempData;
	string login;
	string password;
	int dbI = 0;
	int dbJ = 0;
};

inline void User::showUserLibrary() {
	string gameList[50];
	string libFile = "userLibs/" + loginToCheck + "_games.txt";
	string temp;
	int j = 0;
	userLib.open(libFile, fstream::in | fstream::out);
	cout << "Ваша міні-бібліотека" << endl;
	design('=', 25, 1);
	while (getline(userLib, temp)) {
		if (temp != "")
		{
			gameList[j] = temp;
			cout << j + 1 << ". " << gameList[j] << endl;
			j++;
		}
	}
	userLib.close();
	design('=', 25, 1);
}

inline void User::updateUserLibrary(bool mode) {
	string libFile = "userLibs/" + loginToCheck + "_games.txt";
	cin.ignore();
	if (mode)
	{
		Game game;
		string gameToAdd;
		int again = 0;
		int* pAgain = &again;
		cout << "Майстер додавання ігор" << endl;
		design('=', 50, 1);
		cout << "Введіть назву гри, яку бажаєте додати: \n" << ">>> ";
		getline(cin, gameToAdd);
		if (game.findGame(gameToAdd, *pAgain, 999).size() > 0) cout << "Гра успішно додана до списку" << endl;
		design('=', 50, 1);
		userLib.open(libFile, fstream::in | fstream::out | fstream::app);
		userLib << "\n" << game.findGame(gameToAdd, *pAgain, 999);
		userLib.close();
	}
	else {
		string gameList[50];
		string temp;
		int deletedGame = 0;
		int j = 0;
		cout << "Майстер видалення ігор" << endl;
		design('=', 25, 1);
		userLib.open(libFile, fstream::in | fstream::out);
		cout << "Ваша міні-бібліотека" << endl;
		design('=', 25, 1);
		while (getline(userLib, temp)) {
			if (temp != "")
			{
				gameList[j] = temp;
				cout << j + 1 << ". " << gameList[j] << endl;
				j++;
			}
		}
		userLib.close();
		design('=', 35, 1);
		cout << "Введіть номер гри, яку слід видалити зі списку: \n>>> ";
		cin >> deletedGame;
		design('=', 35, 1);
		deletedGame--;
		while (deletedGame > j || deletedGame < 0) {
			design('=', 35, 1);
			cout << "Введіть номер гри, яку слід видалити зі списку: \n>>> ";
			cin >> deletedGame;
			design('=', 35, 1);
			deletedGame--;
		}
		gameList[deletedGame] = "";
		userLib.open(libFile, fstream::in | fstream::out | fstream::trunc);
		for (int i = 0; i < 50; i++)
		{
			if (gameList[i] != "")
			{
				userLib << gameList[i] << "\n";
			}
			else if (gameList[i] == "") { if (gameList[i + 1] == "") break; }
		}
		userLib.close();
	}
}

inline void User::updateUserInfo() {
	string fileName = "users/" + loginToCheck + "_info.txt";
	string temp = "";
	string myInfo[5];
	string typeInfo[5] = { "новий e-mail","новий номер телефону","нову дату народження","новий улюблений жанр ігор", "нову платформу для ігор" };
	fstream detailInfo;
	showUserInfo();
	cout << endl;
	cout << "\t\tОновлення інформації про себе" << endl;
	design('=', 65, 1);
	detailInfo.open(fileName, fstream::in | fstream::out | fstream::trunc);
	for (int i = 0; i < 5; i++)
	{
		myInfo[i] = "";
		while (myInfo[i] == "")
		{
			cout << "Введіть " << typeInfo[i] << ":\n";
			cin >> myInfo[i];
		}
		detailInfo << myInfo[i] << "\n";
	}
	design('=', 65, 1);
	detailInfo.close();
}

inline bool User::userLibraryMenu() {
	system("pause");
	system("cls");
	int choice = 0;
	design('=', 25, 1);
	cout << "Меню вашої бібліотеки\n";
	design('=', 25, 1);
	cout << "0. Вихід з меню\n"
		<< "1. Переглянути міні-бібліотеку\n"
		<< "2. Додавання нової гри\n"
		<< "3. Видалення гри зі списку" << endl;
	design('=', 25, 1);
	cout << "Оберіть дію: "; cin >> choice;
	design('=', 25, 1);
	switch (choice) {
	case 0:
		return 0;
		break;
	case 1:
		system("pause");
		system("cls");
		showUserLibrary();
		break;
	case 2:
		system("pause");
		system("cls");
		updateUserLibrary(1);
		break;
	case 3:
		system("pause");
		system("cls");
		updateUserLibrary(0);
		break;
	default:
		break;
	}
	return 1;
}

inline void User::loginAs() {
	int a = 0;
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t\t\t\t";
	design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t\t" << "Авторизація:\n" << "\t\t\t\t\t\t";
	design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t\t";
	cout << "Введіть логін: ";
	cin >> loginToCheck;
	cout << "\t\t\t\t\t\t";
	design('-', 50, 1);
	cout << "\t\t\t\t\t\t\t\t";
	cout << "Введіть пароль: ";
	cin >> passToCheck;
	cout << "\t\t\t\t\t\t";
	design('=', 50, 1);
	if (loginToCheck == userDB[a][0] && passToCheck == userDB[a][1])
	{
		cout << "\t\t\t\t\t" << "Вхід виконано успішно. Натисніть будь-яку клавішу аби продовжити";
	}
	else {
		while (true)
		{
			if (loginToCheck != userDB[a][0] || passToCheck != userDB[a][1])
			{
				if (userDB[a][0] == "")
				{
					a = 0;
					loginToCheck = "";
					passToCheck = "";
					cout << "\t\t\t\t\t\t\t" << "Невірно введено дані. Повторіть спробу" << endl;
					cout << "\t\t\t\t\t\t";
					design('=', 50, 1);
					cout << "\t\t\t\t\t\t\t\t" << "Введіть логін: ";
					cin >> loginToCheck;
					cout << "\t\t\t\t\t\t";
					design('=', 50, 1);
					cout << "\t\t\t\t\t\t\t\t" << "Введіть пароль: ";
					cin >> passToCheck;
					cout << "\t\t\t\t\t\t";
					design('=', 50, 1);
				}
				a++;
			}
			else {
				cout << "\t\t\t\t\t" << "Вхід виконано успішно. Натисніть будь-яку клавішу аби продовжити";
				cout << "\n\t\t\t\t\t\t\t";
				break;
			}
		}

	}

}

inline bool User::showActions() {
	system("pause");
	system("cls");
	Game game;
	Category category;
	leaveSoon list;
	int action = 0;
	int again = 0;
	int* pAgain = &again;
	string gameNameToFind;
	cout << "Профіль користувача " << loginToCheck << endl;
	design('=', 60, 1);
	cout << "\tМеню дій\n";
	design('=', 60, 1);
	cout << "1. Переглянути особисті дані\n"
		<< "2. Оновити інформацію про себе\n"
		<< "3. Переглянути бібліотеку GAME PASS\n"
		<< "4. Відсортувати бібліотеку GAME PASS\n"
		<< "5. Переглянути категорії ігор\n"
		<< "6. Фільтрувати бібліотеку\n"
		<< "7. Знайти гру в бібліотеці\n"
		<< "8. Показати список ігор, що покидають бібліотеку\n"
		<< "9. Меню власної бібліотеки\n"
		<< "0. Вихід з програми" << endl;
	cout << "Оберіть дію: ";
	cin >> action;
	design('=', 60, 1);
	switch (action) {
	case 1:
		system("pause");
		system("cls");
		showUserInfo();
		break;
	case 2:
		system("pause");
		system("cls");
		updateUserInfo();
		break;
	case 3:
		system("pause");
		system("cls");
		game.showAllGames();
		break;
	case 4:
		system("pause");
		system("cls");
		game.sortBy();
		break;
	case 5:
		system("pause");
		system("cls");
		category.showCategories();
		break;
	case 6:
		cin.ignore();
		system("pause");
		system("cls");
		game.filterBy();
		break;
	case 7:
		cin.ignore();
		system("pause");
		system("cls");
		cout << "\t\t Майстер пошуку ігор \n";
		game.showAllGames();
		cout << "Введіть назву гри, яку слід знайти: ";
		getline(cin, gameNameToFind);
		system("pause");
		system("cls");
		cout << game.findGame(gameNameToFind, *pAgain) << endl;
		design('=', 131, 1);
		break;
	case 8:
		system("pause");
		system("cls");
		list.showLeavingSoonList();
		break;
	case 9:
		system("pause");
		system("cls");
		while (userLibraryMenu());
		break;
	case 0:
		exit(1);
	default:
		break;
	}
	return 1;
}

class Admin : public Person {
public:
	Admin() {
		fstream adminInfo;
		adminInfo.open("adminInfo.txt", fstream::in | fstream::out);
		while (getline(adminInfo, tempData))
		{
			if (tempData == "-------------------------") {
				continue;
			}
			else
			{
				if (login.size() == 0) {
					login = tempData;
					adminsDB[dbI][dbJ] = login;
					dbJ++;
				}
				else {
					password = tempData;
					adminsDB[dbI][dbJ] = password;
					login = "";
					password = "";
					dbI++;
					dbJ = 0;

				}

			}
		}
		adminInfo.close();
	}

	void loginAs() override
	{
		int a = 0;
		cout << "\n\n\n\n\n\n";
		cout << "\t\t\t\t\t\t";
		design('=', 50, 1);
		cout << "\t\t\t\t\t\t\t\t" << "Авторизація:\n" << "\t\t\t\t\t\t";
		design('=', 50, 1);
		cout << "\t\t\t\t\t\t\t\t";
		cout << "Введіть логін: ";
		cin >> loginToCheck;
		cout << "\t\t\t\t\t\t";
		design('-', 50, 1);
		cout << "\t\t\t\t\t\t\t\t";
		cout << "Введіть пароль: ";
		cin >> passToCheck;
		cout << "\t\t\t\t\t\t";
		design('=', 50, 1);
		if (loginToCheck == adminsDB[a][0] || passToCheck == adminsDB[a][1])
		{
			cout << "\t\t\t\t\t" << "Вхід виконано успішно. Натисніть будь-яку клавішу аби продовжити";
			cout << "\n\t\t\t\t\t\t\t";
		}
		else {
			while (true)
			{
				if (loginToCheck != adminsDB[a][0] || passToCheck != adminsDB[a][1])
				{
					if (adminsDB[a][0] == "")
					{
						a = 0;
						loginToCheck = "";
						passToCheck = "";
						cout << "\t\t\t\t\t\t\t" << "Невірно введено дані. Повторіть спробу" << endl;
						cout << "\t\t\t\t\t\t";
						design('=', 50, 1);
						cout << "\t\t\t\t\t\t\t\t" << "Введіть логін: ";
						cin >> loginToCheck;
						cout << "\t\t\t\t\t\t";
						design('=', 50, 1);
						cout << "\t\t\t\t\t\t\t\t" << "Введіть пароль: ";
						cin >> passToCheck;
						cout << "\t\t\t\t\t\t";
						design('=', 50, 1);
					}
					a++;
				}
				else {
					cout << "\t\t\t\t\t" << "Вхід виконано успішно. Натисніть будь-яку клавішу аби продовжити";
					cout << "\n\t\t\t\t\t\t\t";
					break;
				}
			}

		}

	}

	inline bool showActions() override;

private:
	int dbI = 0;
	int dbJ = 0;
	string loginToCheck;
	string passToCheck;
	string tempData;
	string login;
	string password;
	string adminsDB[10][2];
};

inline bool Admin::showActions() {
	Game game1;
	int choice = 0;
	system("pause");
	system("cls");
	cout << "Меню дій в режимі адміністратора:\n"
		<< "1. Переглянути бібліотеку ігор \n"
		<< "2. Додати гру до бібліотеки\n"
		<< "3. Створити категорію ігор\n"
		<< "4. Знайти гру в бібліотеці\n"
		<< "5. Оновити дані про ігри що покидають бібліотеку\n"
		<< "0. Вихід з програми" << endl;
	cout << "Оберіть дію: ";
	cin >> choice;
	if (choice == 1)
	{
		system("pause");
		system("cls");
		game1.showAllGames();
	}
	else if (choice == 2) {
		system("pause");
		system("cls");
		game1.addNewGame();
	}
	else if (choice == 3) {
		system("pause");
		system("cls");
		game1.createCategory();
	}
	else if (choice == 4) {
		cin.ignore();
		system("pause");
		system("cls");
		int again = 0;
		int* pAgain = &again;
		string gameNameToFind;
		cout << "\t\t Майстер пошуку ігор \n";
		game1.showAllGames();
		cout << "Введіть назву гри, яку слід знайти: ";
		getline(cin, gameNameToFind);
		system("pause");
		system("cls");
		cout << game1.findGame(gameNameToFind, *pAgain) << endl;
		design('=', 131, 1);
	}
	else if (choice == 5) {
		system("pause");
		system("cls");
		leaveSoon list1;
		list1.updateLeavingSoonList();
	}
	else if (choice == 0) exit(1);
	else if (choice == 6) game1.deleteGame();
	else {
		return 0;
	}
	return 1;

}

inline void performLogin(Person* person) {
	person->loginAs();
}

inline void displayMenu(Person* person) {
	person->showActions();
}

inline void mainLogin() {
	int casenumber = 0;
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t\t\t\t"; design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t\t" << "Доступні способи входу: \n";
	cout << "\t\t\t\t\t\t"; design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t" << "1.   Вхід для користувачів\n"
		<< "\t\t\t\t\t\t\t" << "2.   Вхід для адміністраторів\n"
		<< "\t\t\t\t\t\t\t" << "3.   Повернутися назад" << endl;
	cout << "\t\t\t\t\t\t"; design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t\t" << "Оберіть тип входу: ";
	cin >> casenumber;
	cout << "\t\t\t\t\t\t"; design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t";
	if (casenumber == 1)
	{
		system("pause");
		system("cls");
		User newUser;
		performLogin(&newUser);
		cout << "\n\t\t\t\t\t\t\t";
		while (newUser.showActions()) cin.ignore();
	}
	else if (casenumber == 2) {
		system("pause");
		system("cls");
		Admin leadAdmin;
		performLogin(&leadAdmin);
		cout << "\n\t\t\t\t\t\t\t";
		while (leadAdmin.showActions()) cin.ignore();
	}
	else {
		system("pause");
		system("cls");
		return;
	}

}

inline void mainRegister() {
	string userLogin;
	string userPassword;
	string userPassword2;
	fstream userInfo;
	cout << "\n\n\n\n\n\n";
	cout << "\t\t\t\t\t\t"; design('=', 50, 1);
	cout << "\t\t\t\t\t\t\t\tРеєстрація" << endl;
	cout << "\t\t\t\t\t\t"; design('=', 50, 1);
	cout << "\t\t\t\t\t\t\tПридумайте логін:\t";
	cin >> userLogin;
	cout << "\t\t\t\t\t\t\tПридумайте пароль:\t";
	cin >> userPassword;
	cout << "\t\t\t\t\t\t\tПовторіть пароль: \t";
	cin >> userPassword2;
	while (userPassword2 != userPassword)
	{
		userPassword2 = "";
		cout << "\t\t\t\t\t\t"; design('=', 50, 1);
		cout << "\t\t\t\t\t\t\tНеправильно введено пароль!\n"
			<< "\t\t\t\t\t\t\tПовторіть пароль: \t";
		cin >> userPassword2;
	}
	cout << "\t\t\t\t\t\t"; design('=', 50, true);
	writeIn(userInfo, "userInfo.txt", userLogin, userPassword);
	cout << "\t\t\t\t\t\t\t";
	system("pause");
	system("cls");
}