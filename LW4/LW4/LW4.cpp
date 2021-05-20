#define DEBU

#ifdef DEBUG
#include <list>
#include <vector>
#else
#include "Vector.h"
#include "List.h"
#endif
#include <iostream>

using namespace std;

template<class Incon, class Outcon>
Outcon Move(Incon first, Incon last, Outcon beg)
{
	using smth = decltype(*first);

	if constexpr (_Is_random_iter_v<Incon> || is_pointer_v<decay_t<Incon>>)
	{
		if constexpr (_Is_random_iter_v<Outcon> || is_pointer_v<decay_t<Outcon>>)
		{
			int d = (last - first);
			if (beg > first && beg < last)
			{
				--last;
				for (auto i = beg + d - 1; first != last; --i, --last)
				{
					*i = static_cast<smth&&> (*last);
				}
				*beg = *first;
				beg += d;
			}
			else
			{
				for (; first != last; ++beg, ++first)
				{
					*beg = static_cast<smth&&>(*first);
				}
			}
		}
		else
		{
			for (; first != last; ++beg, ++first)
			{
				*beg = static_cast<smth&&>(*first);
			}
		}
	}
	else
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

template<class Con>
void showcon(Con c)
{
	for (const auto& i : c)
	{
		cout << i << " ";
	}
}

template <typename Iter>
void displace_list_iter(typename Iter& ii, typename Iter& jj, const unsigned int s)
{
	for (int i = 0; i < s; ++i)
	{
		++ii;
		--jj;
	}
}

const int MAX = 20;

void init_con(list<int>& aa, vector<int>& v2, int* a)
{
	auto lit = aa.begin();
	for (auto i = 0; i < MAX; ++i, ++lit)
	{
		*lit = i;
		v2[i] = i;
		a[i] = i;
	}
}

int main()
{
	setlocale(0, "");
	list<int> aa(20);
	vector<int> v2(20);
	int a[MAX];
	const unsigned int s = 3;

	init_con(aa, v2, a);
	showcon(v2);
	cout << endl;

	auto ii = aa.begin();
	auto jj = aa.end();
	displace_list_iter(ii, jj, s);

	cout << "Move:" << endl;
	Move(aa.begin(), jj, ii);
	Move(v2.begin() + 5, v2.end(), v2.begin());
	Move(a + 7, a + MAX - 1, a);
	cout << "Список" << endl;
	showcon(aa);
	cout << endl << "Вектор" << endl;
	showcon(v2);
	cout << endl << "Массив" << endl;
	for (int i = 0; i < MAX; ++i)
	{
		cout << a[i] << " ";
	}
#ifdef DEBUG
	cout << endl << endl;
	init_con(aa, v2, a);

	cout << "Copy:" << endl;
	copy(aa.begin(), jj, ii);
	copy(v2.begin() + 5, v2.end(), v2.begin());
	copy(a + 7, a + MAX - 1, a);
	cout << "Список" << endl;
	showcon(aa);
	cout << endl << "Вектор" << endl;
	showcon(v2);
	cout << endl << "Массив" <<endl;

	for (int i = 0; i < MAX; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
#endif

	return 0;
}
