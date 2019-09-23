#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <iomanip>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Фамилия?=";
	string lastname;
	cin >> lastname;
	cout << "Имя?=";
	string name;
	cin >> name;
	cout << "Отчество?=";
	string fathername;
	cin >> fathername;
	cout << "Пол?=";
	string gender;
	cin >> gender;
	cout << "Дата рождения?=";
	string birthday;
	cin >> birthday;
	cout << "Адрес?=";
	string location;
	cin.ignore(32767, '\n');
	getline(cin, location);
	cout << "Номер телефона?=";
	string phone;
	cin >> phone;
	cout << "Место учёбы?=";
	string univ;
	cin.ignore(32767, '\n');
	getline(cin, univ);
	cout << "Класс?=";
	string Class;
	cin >> Class;
	cout << "Хобби?=";
	string hobby;
	cin >> hobby;
	int lastnamesize = lastname.length();
	int phonesize = phone.length();
	int namesize = name.length();
	int gendersize = gender.length();
	int birthdaysize = birthday.length();
	int fathernamesize = fathername.length();
	int startsize = 20;
	
	if (startsize < lastnamesize)
	{
		startsize = lastnamesize;
	};
	if (startsize < namesize)
	{
		startsize = namesize;
	};
	if (startsize < fathernamesize)
	{
		startsize = fathernamesize;
	};
	if (startsize < phonesize)
	{
		startsize = phonesize;
	};
	if (startsize < gendersize)
	{
		startsize = gendersize;
	};
	if (startsize < birthdaysize)
	{
		startsize = birthdaysize;
	};

	unsigned int finishsize = startsize + 10;

	system("cls");

	cout << setw(finishsize) << "Фамилия" << setw(finishsize) << "Имя" << setw(finishsize) << "Отчеcтво" << endl;
	cout << setw(finishsize) << "-------" << setw(finishsize) << "---" << setw(finishsize) << "--------" << endl;
	cout << setw(finishsize) << lastname << setw(finishsize) << name << setw(finishsize) << fathername << endl;
	cout << setw(finishsize) << "Пол" << setw(finishsize) << "Дата рождения" << setw(finishsize) << "Номер телефона" << endl;
	cout << setw(finishsize) << "---" << setw(finishsize) << "-------------" << setw(finishsize) << "--------------" << endl;
	cout << setw(finishsize) << gender << setw(finishsize) << birthday << setw(finishsize) << phone << endl;

	_getch();
	return 0;
}