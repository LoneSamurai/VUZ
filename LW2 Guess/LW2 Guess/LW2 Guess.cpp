#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string yes;
	int x;
	cout << "Загадайте число, когда загадаете напишите \"Да\": ";
	while (yes != "Да")
	cin >> yes;
	cout << "Умножьте это число на его 10" << endl;
	cout << "Разделите на 2" << endl;
	cout << "Прибавьте загаданное число" << endl;
	cout << "Разделите на 3" << endl;
	cout << "Прибавьте 4" << endl;
	cout << "Разделите на 2" << endl;
	cout << "Вычтите 2" << endl;
	cout << "Напишите результат: ";
	cin >> x;
	cout << "Вы загадали число " << x;

	_getch();
	return 0;
}