#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	setlocale(0, "");
	int a, b, c;
	cout << "A=";
	cin >> a;
	cout << "B=";
	cin >> b;
	cout << "C=";
	cin >> c;
	int temp;
	temp = b;
	b = a;
	a = c;
	c = temp;
	cout << "A= " << a << "\tB= " << b << "\tC= " << c;

	_getch;
	return 0;
}