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
	cout << "A= " << a << "\tB= " << b << "\tC= " << c << endl;
	int temp;
	temp = c;
	c = b;
	b = a;
	a = temp;
	cout << "A= " << a << "\tB= " << b << "\tC= " << c;

	_getch;
	return 0;
}