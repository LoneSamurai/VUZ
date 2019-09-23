#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	cout << "Введите текст: ";
	string story;
	getline(cin, story);
	cout << "\n" << story;

	_getch();
	return 0;
}