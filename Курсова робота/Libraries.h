#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <fstream>
#include <windows.h>
#include <vector>

using namespace std;

template <typename T>
string design(const T ch, int number, bool outputType = false) {
	string complete = "";
	for (int i = 0; i < number; i++)
	{
		if (outputType)
		{
			cout << ch;
		}
		complete += ch;
	}
	cout << endl;
	complete += "\n";
	return complete;
}

template <typename T>
string design2(T ch, int number, bool outputType = false) {
	string complete = "";
	for (int i = 0; i < number; i++)
	{
		if (outputType)
		{
			Sleep(10);
			cout << ch;
		}
		complete += ch;
	}
	cout << endl;

	complete += "\n";
	return complete;
}

void writeIn(fstream& file, string fileName, string str, string str2) {
	file.open(fileName, fstream::in | fstream::out | fstream::app);
	file << design('-', 25, false) << str << "\n" << str2 << "\n" << design('-', 25, false);
	file.close();
}

void writeIn(fstream& file, string fileName, string str, string str2, string str3, string str4, string str5, string str6, string str7) {
	file.open(fileName, fstream::in | fstream::out | fstream::app);
	file << design('=', 32, 0) << str << "\n" << str2 << "\n" << str3 << "\n" << str4 << "\n" << str5 << "\n" << str6 << "\n" << str7 << "\n" << design('=', 32, 0);
	file.close();
}

void writeIn(fstream& file, string fileName, string completeString) {
	file.open(fileName, fstream::in | fstream::out | fstream::app);
	file << completeString << "\n";
	file.close();
}
