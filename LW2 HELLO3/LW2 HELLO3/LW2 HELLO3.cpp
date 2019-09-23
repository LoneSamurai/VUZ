#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Как Вас зовут?=";
	string name;
	cin >> name;

	int age;
	cout << "Сколько Вам лет?=";
	cin >> age;
	while (age < 0)
	{
		cout << "Вы ввели неправильный возраст, введите его заного: ";
		cin >> age;
	}

	cout << "Где Вы учитесь?=";
	string school;
	cin.ignore(32767, '\n');
	getline(cin, school);

	system("cls");

	string age2;
	int age1;
	if (age % 100 != 11 && 12 && 13 && 14)
	{
		age1 = age % 10;
	}
	else
	{
		age1 = age;
	};

	switch (age1)
	{
	case 2:
		age2 = "года";
		break;
	case 3:
		age2 = "года";
		break;
	case 4:
		age2 = "года";
		break;
	case 1:
		age2 = "год";
		break;
	default:
		age2 = "лет";
		break;
	}

	cout << "Здравствуйте, " << name << "!\n";
	cout << "Поздравляю Вас, Вам всего " << age << " " << age2 << " , а Вы уже ведёте диалог с компьютером!" << endl;
	cout << school << " будет гордится Вами!";


	_getch;
	return 0;
}