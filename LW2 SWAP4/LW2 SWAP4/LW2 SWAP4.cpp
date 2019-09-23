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
	cout << "A= " << a << "\tB= " << b << "\tC= " << c << "\tD= " << d << endl;
	int temp;
	temp = d;
	d = c;
	c = b;
	b = a;
	a = temp;
	cout << "A= " << a << "\tB= " << b << "\tC= " << c << "\tD= " << d;

	_getch;
	return 0;
}