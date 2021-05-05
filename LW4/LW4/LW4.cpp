#define DEBU

#ifdef DEBUG
#include <list>
#include <vector>
#else // DEBUG
#include "Vector.h"
#include "List.h"
#endif
#include <iostream>

using namespace std;

template<class incon, class outcon>
outcon Move(incon first, incon last, outcon beg)
{
	using smth = decltype(*first);

	/*if constexpr (_Is_random_iter_v<incon> || is_pointer_v<decay_t<incon>>)
	{
		if constexpr (_Is_random_iter_v<outcon> || is_pointer_v<decay_t<outcon>>)
		{
			int d = (last - first);
			if (&*beg > & *first && &*beg < &*last)
			{
				--last;
				for (auto i = beg + d - 1; first != last; --i, --last)
				{
					*i = *last;
				}
				*beg = *first;
				beg += d;
			}
			else
			{
				for (; first != last; ++beg, ++first)
				{
					*beg = *first;
				}
			}
		}
		else
		{
			for (; first != last; ++beg, ++first)
			{
				*beg = *first;
			}
		}
	}
	else*/
	{	
		auto tt = beg;
		for (auto t = first; t != last; ++t, ++tt)
		{
			if (t == beg || tt == last)
			{
				++t;
				while (t != last)
				{
					++tt;
					++t;
				}
				beg = tt;
				--last;
				for (; first != last; --tt, --last)
				{
					*tt = static_cast<smth&&>(*last);
				}
				*tt = *first;
				return beg;
			}
			if (tt == first)
			{
				break;
			}
		}
		for (; first != last; ++beg, ++first)
		{
			*beg = static_cast<smth&&>(*first);
		}
	}
	return beg;
}

const int MAX = 20;

int main()
{
	setlocale(0, "");
	list<int> aa, bb;
	vector<int> v2;
	int a[MAX];
	for (auto i = 0; i < MAX; ++i)
	{
		bb.push_back(i);
		aa.push_back(i);
		v2.push_back(i);
		a[i] = i;
		cout << i << " ";
	}

	cout << endl;
	auto ii = aa.begin();
	auto jj = aa.end();
	for (int i = 0; i < 3; ++i)
	{
		++ii;
		--jj;
	}
	cout << "Move:" << endl;
	Move(aa.begin(), jj, ii);
	Move(v2.begin() + 5, v2.end(), v2.begin());
	Move(a + 7, a + MAX - 1, a);
	cout << "Список" << endl;
	for (auto i : aa)
	{
		cout << i << " ";
	}
	cout << endl << "Вектор" << endl;
	for (auto i : v2)
	{
		cout << i << " ";
	}
	cout << endl << "Массив" << endl;
	for (int i = 0; i < MAX; ++i)
	{
		cout << a[i] << " ";
	}
#ifdef DEBUG
	cout << endl << endl;
	for (auto i = 0; i < MAX; ++i)
	{
		v2[i] = i;;
		a[i] = i;
	}
	ii = bb.begin();
	jj = bb.end();
	for (int i = 0; i < 3; ++i)
	{
		++ii;
		--jj;
	}
	cout << "Copy:" << endl;
	copy(bb.begin(), jj, ii);
	copy(v2.begin() + 5, v2.end(), v2.begin());
	copy(a + 7, a + MAX - 1, a);
	cout << "Список" << endl;
	for (auto i : bb)
	{
		cout << i << " ";
	}
	cout << endl << "Вектор" << endl;
	for (auto i : v2)
	{
		cout << i << " ";
	}
	cout << endl << "Массив" <<endl;
	for (int i = 0; i < MAX; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
#endif

	return 0;
}
