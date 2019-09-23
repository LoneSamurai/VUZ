#include <iostream>
#include <conio.h>

using namespace std;

int main()
{
	setlocale(0, "");
	int a, b, c, d;
	cout << "A=";
	cin >> a;
	cout << "B=";
	cin >> b;
	cout << "C=";
	cin >> c;
	cout << "D=";
	cin >> d;
	int temp;
	temp = b;
	b = a;
	a = d;
	d = c;
	c = temp;
	cout << "A= " << a << "\tB= " << b << "\tC= " << c << "\tD= " << d;

	_getch;
	return 0;
}