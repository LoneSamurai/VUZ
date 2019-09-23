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
	string name;
	cout << "Как вас зовут?=";
	cin >> name;
	cout << "\nЗдравстуйте, " << name << "!";
	
	_getch();
	return 0;
}