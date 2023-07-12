#pragma once
#include "Libraries.h"

/*****************************************************************\GAMES/********************************************************************/
class Game;
class Game {
public:
	static int count;
	const enum sortType { 
		gameName, gameAuthor, gamePublisher, gamePlatform, gameGenre, gameReleaseDate, gamePrice, defaultSort 
	};
	const enum filterType { 
		filterAuthor, filterPublisher, filterPlatform, filterGenre, filterReleaseDate, filterPrice
	};
	friend ostream& operator<< (ostream& out, const Game& game);
	Game() {
		if (count > objCounter) count = 1;
		allGamesFile.open(fileName1, fstream::in | fstream::out);
		while (getline(allGamesFile, tempData))
		{
			if (tempData == "================================") continue;
			else {
				if (name.size() == 0) {
					name = tempData;
					tempGamesDB[objCounter][0] = name;
				}
				else if (author.size() == 0) {
					author = tempData;
					tempGamesDB[objCounter][1] = author;
				}
				else if (publisher.size() == 0) {
					publisher = tempData;
					tempGamesDB[objCounter][2] = publisher;
				}
				else if (platform.size() == 0) {
					platform = tempData;
					tempGamesDB[objCounter][3] = platform;
				}
				else if (genre.size() == 0) {
					genre = tempData;
					tempGamesDB[objCounter][4] = genre;
				}
				else if (releaseDate.size() == 0) {
					releaseDate = tempData;
					tempGamesDB[objCounter][5] = releaseDate;
				}
				else if (price.size() == 0) {
					price = tempData;
					tempGamesDB[objCounter][6] = price;
					name = "";
					author = "";
					publisher = "";
					platform = "";
					genre = "";
					releaseDate = "";
					price = "";
					count++;
					objCounter++;
				}
			}
		}
		allGamesFile.close();
	}
	inline void addNewGame();
	inline void deleteGame();
	inline void showAllGames(sortType st);
	inline void sortBy() {
		int sortCase = 0;
		cout << "Типи сортування: \n"
			<< "1. Сортування за назвою гри\n"
			<< "2. Сортування за розробником гри\n"
			<< "3. Сортування за видавцем гри\n"
			<< "4. Сортування за платформами гри\n"
			<< "5. Сортування за жанром гри\n"
			<< "6. Сортування за датою виходу гри\n"
			<< "7. Сортування за ціною гри\n"
			<< "8. Без сортування" << endl;
		cout << "Оберіть тип сортування: ";
		cin >> sortCase;
		switch (sortCase)
		{
		case 1:
			showAllGames(gameName);
			break;
		case 2:
			showAllGames(gameAuthor);
			break;
		case 3:
			showAllGames(gamePublisher);
			break;
		case 4:
			showAllGames(gamePlatform);
			break;
		case 5:
			showAllGames(gameGenre);
			break;
		case 6:
			showAllGames(gameReleaseDate);
			break;
		case 7:
			showAllGames(gamePrice);
			break;
		case 8:
			showAllGames(defaultSort);
			break;
		default:
			showAllGames(defaultSort);
			break;
		}
	}
	inline void filterBy();
	inline string findGame(string strfind, int& pAgain, int state = 1);
	inline void writeCategory(string strfind, int& pAgain);
	inline void createCategory();
	inline void filter(filterType ft, string dataToFilter);
	inline string getRandomPrice();
private:
	int objCounter = 0;
	string name = "";
	string author = "";
	string publisher = "";
	string platform = "";
	string genre = "";
	string releaseDate = "";
	string price = "";
	string fileName1 = "gamesDB.txt";
	string tempData;
	string gameData[7];
	string tempGamesDB[100][7];
	fstream allGamesFile;
	fstream categoriesFile;
};

int Game::count = 1;

ostream& operator << (ostream& out, const Game& game)
{
	out << game.name;
	if (game.name.size() >= 6 && game.name.size() < 12)
	{
		out << "\t";
	}
	out << "\t" << game.author;
	if (game.author.size() >= 8 && game.author.size() <= 14)
	{
		out << "\t";
	}
	else if (game.author.size() < 8) out << "\t\t";
	out << "\t" << game.publisher;
	if (game.publisher.size() <= 15)
	{
		out << "\t";
		if (game.publisher.size() <= 7) out << "\t";
	}
	out << "\t" << game.platform;
	if (game.platform.size() < 5)
	{
		out << "\t";
	}
	out << "\t" << game.genre;
	if (game.genre.size() < 10)
	{
		out << "\t";
	}
	out << "\t " << game.releaseDate << " рік" << "\t" << game.price << endl;
	return out;
}

inline void Game::showAllGames(sortType st = defaultSort) {
	string tempName, tempAuthor, tempPublisher, tempPlatform, tempGenre, tempReleaseDate, tempPrice;
	int arrSize = objCounter;
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
	if (st == defaultSort)
	{
		design('=', 131, 1);
		cout << "#   Назва гри\t\tРозробник\t\tВидавець\t\tПлатформа\tЖанр\t\tДата виходу      Ціна" << endl;
		design('-', 131, 1);
		for (int i = 0; i < arrSize; i++)
		{
			if (allGames[i].name == "") {
				break;
			}
			cout << i + 1 << ". ";
			if (i < 10) cout << " ";
			cout << allGames[i];
		}
		design('=', 131, 1);
	}
	else {
		if (st == gameName)
		{
			for (int i = 0; i < arrSize; i++)
			{
				for (int j = 0; j < arrSize - i - 1; j++)
				{
					if (allGames[j].name > allGames[j + 1].name)
					{
						tempName = allGames[j].name;
						allGames[j].name = allGames[j + 1].name;
						allGames[j + 1].name = tempName;

						tempAuthor = allGames[j].author;
						allGames[j].author = allGames[j + 1].author;
						allGames[j + 1].author = tempAuthor;

						tempPublisher = allGames[j].publisher;
						allGames[j].publisher = allGames[j + 1].publisher;
						allGames[j + 1].publisher = tempPublisher;

						tempPlatform = allGames[j].platform;
						allGames[j].platform = allGames[j + 1].platform;
						allGames[j + 1].platform = tempPlatform;

						tempGenre = allGames[j].genre;
						allGames[j].genre = allGames[j + 1].genre;
						allGames[j + 1].genre = tempGenre;

						tempReleaseDate = allGames[j].releaseDate;
						allGames[j].releaseDate = allGames[j + 1].releaseDate;
						allGames[j + 1].releaseDate = tempReleaseDate;

						tempPrice = allGames[j].price;
						allGames[j].price = allGames[j + 1].price;
						allGames[j + 1].price = tempPrice;
					}
				}
			}
			design('=', 131, 1);
			cout << "#   Назва гри\t\tРозробник\t\tВидавець\t\tПлатформа\tЖанр\t\tДата виходу      Ціна" << endl;
			design('-', 131, 1);
			for (int i = 0; i < arrSize; i++)
			{
				Sleep(25);
				if (allGames[i].name == "") {
					break;
				}
				cout << i + 1 << ". ";
				if (i < 10) cout << " ";
				cout << allGames[i];
			}
			design('=', 131, 1);
		}
		else if (st == gameAuthor) {
			for (int i = 0; i < arrSize; i++)
			{
				for (int j = 0; j < arrSize - i - 1; j++)
				{
					if (allGames[j].author > allGames[j + 1].author)
					{
						tempName = allGames[j].name;
						allGames[j].name = allGames[j + 1].name;
						allGames[j + 1].name = tempName;

						tempAuthor = allGames[j].author;
						allGames[j].author = allGames[j + 1].author;
						allGames[j + 1].author = tempAuthor;

						tempPublisher = allGames[j].publisher;
						allGames[j].publisher = allGames[j + 1].publisher;
						allGames[j + 1].publisher = tempPublisher;

						tempPlatform = allGames[j].platform;
						allGames[j].platform = allGames[j + 1].platform;
						allGames[j + 1].platform = tempPlatform;

						tempGenre = allGames[j].genre;
						allGames[j].genre = allGames[j + 1].genre;
						allGames[j + 1].genre = tempGenre;

						tempReleaseDate = allGames[j].releaseDate;
						allGames[j].releaseDate = allGames[j + 1].releaseDate;
						allGames[j + 1].releaseDate = tempReleaseDate;

						tempPrice = allGames[j].price;
						allGames[j].price = allGames[j + 1].price;
						allGames[j + 1].price = tempPrice;

					}
				}
			}
			design('=', 131, 1);
			cout << "#   Назва гри\t\tРозробник\t\tВидавець\t\tПлатформа\tЖанр\t\tДата виходу      Ціна" << endl;
			design('-', 131, 1);
			for (int i = 0; i < arrSize; i++)
			{
				Sleep(25);
				if (allGames[i].name == "") {
					break;
				}
				cout << i + 1 << ". ";
				if (i < 10) cout << " ";
				cout << allGames[i];
			}
			design('=', 131, 1);
		}
		else if (st == gamePublisher) {
			for (int i = 0; i < arrSize; i++)
			{
				for (int j = 0; j < arrSize - i - 1; j++)
				{
					if (allGames[j].publisher > allGames[j + 1].publisher)
					{
						tempName = allGames[j].name;
						allGames[j].name = allGames[j + 1].name;
						allGames[j + 1].name = tempName;

						tempAuthor = allGames[j].author;
						allGames[j].author = allGames[j + 1].author;
						allGames[j + 1].author = tempAuthor;

						tempPublisher = allGames[j].publisher;
						allGames[j].publisher = allGames[j + 1].publisher;
						allGames[j + 1].publisher = tempPublisher;

						tempPlatform = allGames[j].platform;
						allGames[j].platform = allGames[j + 1].platform;
						allGames[j + 1].platform = tempPlatform;

						tempGenre = allGames[j].genre;
						allGames[j].genre = allGames[j + 1].genre;
						allGames[j + 1].genre = tempGenre;

						tempReleaseDate = allGames[j].releaseDate;
						allGames[j].releaseDate = allGames[j + 1].releaseDate;
						allGames[j + 1].releaseDate = tempReleaseDate;

						tempPrice = allGames[j].price;
						allGames[j].price = allGames[j + 1].price;
						allGames[j + 1].price = tempPrice;
					}
				}
			}
			design('=', 131, 1);
			cout << "#   Назва гри\t\tРозробник\t\tВидавець\t\tПлатформа\tЖанр\t\tДата виходу      Ціна" << endl;
			design('-', 131, 1);
			for (int i = 0; i < arrSize; i++)
			{
				Sleep(25);
				if (allGames[i].name == "") {
					break;
				}
				cout << i + 1 << ". ";
				if (i < 10) cout << " ";
				cout << allGames[i];
			}
			design('=', 131, 1);
		}
		else if (st == gamePlatform) {
			for (int i = 0; i < arrSize; i++)
			{
				for (int j = 0; j < arrSize - i - 1; j++)
				{
					if (allGames[j].platform.size() < allGames[j + 1].platform.size())
					{
						tempName = allGames[j].name;
						allGames[j].name = allGames[j + 1].name;
						allGames[j + 1].name = tempName;

						tempAuthor = allGames[j].author;
						allGames[j].author = allGames[j + 1].author;
						allGames[j + 1].author = tempAuthor;

						tempPublisher = allGames[j].publisher;
						allGames[j].publisher = allGames[j + 1].publisher;
						allGames[j + 1].publisher = tempPublisher;

						tempPlatform = allGames[j].platform;
						allGames[j].platform = allGames[j + 1].platform;
						allGames[j + 1].platform = tempPlatform;

						tempGenre = allGames[j].genre;
						allGames[j].genre = allGames[j + 1].genre;
						allGames[j + 1].genre = tempGenre;

						tempReleaseDate = allGames[j].releaseDate;
						allGames[j].releaseDate = allGames[j + 1].releaseDate;
						allGames[j + 1].releaseDate = tempReleaseDate;

						tempPrice = allGames[j].price;
						allGames[j].price = allGames[j + 1].price;
						allGames[j + 1].price = tempPrice;
					}
				}
			}
			design('=', 131, 1);
			cout << "#   Назва гри\t\tРозробник\t\tВидавець\t\tПлатформа\tЖанр\t\tДата виходу      Ціна" << endl;
			design('-', 131, 1);
			for (int i = 0; i < arrSize; i++)
			{
				Sleep(25);
				if (allGames[i].name == "") {
					break;
				}
				cout << i + 1 << ". ";
				if (i < 10) cout << " ";
				cout << allGames[i];
			}
			design('=', 131, 1);
		}
		else if (st == gameGenre) {
			for (int i = 0; i < arrSize; i++)
			{
				for (int j = 0; j < arrSize - i - 1; j++)
				{
					if (allGames[j].genre > allGames[j + 1].genre)
					{
						tempName = allGames[j].name;
						allGames[j].name = allGames[j + 1].name;
						allGames[j + 1].name = tempName;

						tempAuthor = allGames[j].author;
						allGames[j].author = allGames[j + 1].author;
						allGames[j + 1].author = tempAuthor;

						tempPublisher = allGames[j].publisher;
						allGames[j].publisher = allGames[j + 1].publisher;
						allGames[j + 1].publisher = tempPublisher;

						tempPlatform = allGames[j].platform;
						allGames[j].platform = allGames[j + 1].platform;
						allGames[j + 1].platform = tempPlatform;

						tempGenre = allGames[j].genre;
						allGames[j].genre = allGames[j + 1].genre;
						allGames[j + 1].genre = tempGenre;

						tempReleaseDate = allGames[j].releaseDate;
						allGames[j].releaseDate = allGames[j + 1].releaseDate;
						allGames[j + 1].releaseDate = tempReleaseDate;

						tempPrice = allGames[j].price;
						allGames[j].price = allGames[j + 1].price;
						allGames[j + 1].price = tempPrice;
					}
				}
			}
			design('=', 131, 1);
			cout << "#   Назва гри\t\tРозробник\t\tВидавець\t\tПлатформа\tЖанр\t\tДата виходу      Ціна" << endl;
			design('-', 131, 1);
			for (int i = 0; i < arrSize; i++)
			{
				Sleep(25);
				if (allGames[i].name == "") {
					break;
				}
				cout << i + 1 << ". ";
				if (i < 10) cout << " ";
				cout << allGames[i];
			}
			design('=', 131, 1);
		}
		else if (st == gameReleaseDate) {
			for (int i = 0; i < arrSize; i++)
			{
				for (int j = 0; j < arrSize - i - 1; j++)
				{
					if (allGames[j].releaseDate < allGames[j + 1].releaseDate)
					{
						tempName = allGames[j].name;
						allGames[j].name = allGames[j + 1].name;
						allGames[j + 1].name = tempName;

						tempAuthor = allGames[j].author;
						allGames[j].author = allGames[j + 1].author;
						allGames[j + 1].author = tempAuthor;

						tempPublisher = allGames[j].publisher;
						allGames[j].publisher = allGames[j + 1].publisher;
						allGames[j + 1].publisher = tempPublisher;

						tempPlatform = allGames[j].platform;
						allGames[j].platform = allGames[j + 1].platform;
						allGames[j + 1].platform = tempPlatform;

						tempGenre = allGames[j].genre;
						allGames[j].genre = allGames[j + 1].genre;
						allGames[j + 1].genre = tempGenre;

						tempReleaseDate = allGames[j].releaseDate;
						allGames[j].releaseDate = allGames[j + 1].releaseDate;
						allGames[j + 1].releaseDate = tempReleaseDate;

						tempPrice = allGames[j].price;
						allGames[j].price = allGames[j + 1].price;
						allGames[j + 1].price = tempPrice;
					}
				}
			}
			design('=', 131, 1);
			cout << "#   Назва гри\t\tРозробник\t\tВидавець\t\tПлатформа\tЖанр\t\tДата виходу      Ціна" << endl;
			design('-', 131, 1);
			for (int i = 0; i < arrSize; i++)
			{
				Sleep(25);
				if (allGames[i].name == "") {
					break;
				}
				cout << i + 1 << ". ";
				if (i < 10) cout << " ";
				cout << allGames[i];
			}
			design('=', 131, 1);
		}
		else if (st == gamePrice)
		{
			for (int i = 0; i < arrSize; i++)
			{
				for (int j = 0; j < arrSize - i - 1; j++)
				{
					if (stoi(allGames[j].price.substr(0, 4)) < stoi(allGames[j + 1].price.substr(0, 4)))
					{
						tempName = allGames[j].name;
						allGames[j].name = allGames[j + 1].name;
						allGames[j + 1].name = tempName;

						tempAuthor = allGames[j].author;
						allGames[j].author = allGames[j + 1].author;
						allGames[j + 1].author = tempAuthor;

						tempPublisher = allGames[j].publisher;
						allGames[j].publisher = allGames[j + 1].publisher;
						allGames[j + 1].publisher = tempPublisher;

						tempPlatform = allGames[j].platform;
						allGames[j].platform = allGames[j + 1].platform;
						allGames[j + 1].platform = tempPlatform;

						tempGenre = allGames[j].genre;
						allGames[j].genre = allGames[j + 1].genre;
						allGames[j + 1].genre = tempGenre;

						tempReleaseDate = allGames[j].releaseDate;
						allGames[j].releaseDate = allGames[j + 1].releaseDate;
						allGames[j + 1].releaseDate = tempReleaseDate;

						tempPrice = allGames[j].price;
						allGames[j].price = allGames[j + 1].price;
						allGames[j + 1].price = tempPrice;
					}
				}
			}
			design('=', 131, 1);
			cout << "#   Назва гри\t\tРозробник\t\tВидавець\t\tПлатформа\tЖанр\t\tДата виходу      Ціна" << endl;
			design('-', 131, 1);
			for (int i = 0; i < arrSize; i++)
			{
				Sleep(25);
				if (allGames[i].name == "") {
					break;
				}
				cout << i + 1 << ". ";
				if (i < 10) cout << " ";
				cout << allGames[i];
			}
			design('=', 131, 1);
		}
	}
}


