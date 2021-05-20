#pragma once
#include<iostream>
template<class type>
class vector
{
	type* v_beg = NULL;
	int vec_size = 0;
public:
	class iterator
	{
		type* index;
		iterator();
		friend class vector;
	public:
		using iterator_category = std::random_access_iterator_tag;
		using value_type = type;
		using difference_type = std::ptrdiff_t;
		using pointer = type*;
		typedef const type* const_pointer;
		using reference = type&;

		iterator(type*);
		typename iterator operator++(int);
		typename iterator& operator++();
		type& operator*();
		typename iterator operator--(int);
		typename iterator& operator--();
		typename iterator& operator-(const int);
		typename iterator& operator-=(const int);
		int operator-(const iterator&);
		typename iterator& operator+(const int);
		typename iterator& operator+=(const int);
		typename iterator& operator=(const iterator&);
		bool operator<(const iterator&);
		bool operator<=(const iterator&);
		bool operator>(const iterator&);
		bool operator>=(const iterator&);
		bool operator!=(const iterator&) const;
		bool operator==(const iterator&) const;
	};
	~vector();
	vector();
	vector(const int);
	vector(const type*, const int);
	vector(const vector<type>&);
	vector(vector<type>&&);
	template <class init>
	vector(init first, init last);
	typename iterator begin();
	typename iterator end();
	void push_back(type);
	int size();
	void pop_back();
	type& operator[](const int);
	type* at(const int);
	bool empty();
	bool operator==(const vector<type>&);
	vector& operator=(const vector<type>&);
	vector& operator=(vector<type>&&);
	void clear();
	typename iterator erase(iterator);
	typename iterator erase(iterator, iterator);
	void swap(vector<type>&);
	void resize(int new_size);
	template <class init>
	void assign(init first, init last);
	void assign(int count, const type& value);
	void insert(iterator pos, const int count, const type& value);
	template <class init>
	void insert(iterator pos, init first, init last);
};

template<class type>
vector<type>::~vector()
{
	if(v_beg!=NULL)
		delete v_beg;
}

template<class type>
vector<type>::vector() {}

template<class type>
vector<type>::vector(const int s) : vec_size(s)
{
	v_beg = new type[vec_size];
}

template<class type>
vector<type>::vector(const type* a, const int s) : vec_size(s)
{
	v_beg = new type[vec_size];
	for (int i = 0; i < vec_size; ++i)
	{
		v_beg + i = a[i];
	}
}

template<class type>
template<class init>
vector<type>::vector(init first, init last)
{
	
	for (auto it = first; it != last; ++it)
		++vec_size;
	
	v_beg = new type[vec_size];
	for (type* i = v_beg; first != last; ++i, ++first)
	{
		*i = *first;
	}
}

template<class type>
vector<type>::vector(const vector<type>& v)
{
	vec_size = v.vec_size;

	if (v_beg != NULL)
		delete v_beg;

	v_beg = new type[vec_size];
	for (int i = 0; i < vec_size; ++i)
	{
		v_beg[i] = v.v_beg[i];
	}
}

template<class type>
vector<type>::vector(vector<type>&& v)
{
	std::swap(v_beg, v.v_beg);
	std::swap(vec_size, v.vec_size);
}

template<class type>
void vector<type>::assign(int count, const type& value)
{
	if (v_beg != NULL)
		delete v_beg;
	vec_size = count;
	v_beg = new type[vec_size];
	while (count--)
	{
		v_beg[count] = value;
	}
}

template<class type>
template<class init>
void vector<type>::assign(init first, init last)
{
	if (v_beg != NULL)
	{
		delete[] v_beg;
		vec_size = 0;
	}
	for (auto it = first; it != last; ++it)
			++vec_size;
	v_beg = new type[vec_size];
	for (int i = 0; i < vec_size; ++i, ++first)
	{
		v_beg[i] = *first;
	}
}

template<class type>
void vector<type>::insert(iterator pos, const int count, const type& value)
{
	vec_size += count;
	type* new_vec = type[vec_size];
	int i = 0;
	for (; i < pos; ++i)
	{
		new_vec[i] = v_beg[i];
	}
	for (; i < pos + count; ++i)
	{
		new_vec[i] = value;
	}
	for (; i < vec_size; ++i)
	{
		new_vec[i] = v_beg[i - count];
	}
	if (v_beg != NULL)
		delete v_beg;
	v_beg = new_vec;
}

template<class type>
template<class init>
void vector<type>::insert(iterator pos, init first, init last)
{
	
	int d = 0;
	for (auto it = first; it != last; ++it)
		++d;
	vec_size += d;
	type* new_vec = new type[vec_size];
	int i = 0;
	for (; v_beg + i != pos.index; ++i)
	{
		new_vec[i] = v_beg[i];
	}
	for (; first != last; ++i,++first)
	{
		new_vec[i] = *first;
	}
	for (; i < vec_size; ++i)
	{
		new_vec[i] = v_beg[i - d];
	}
	if (v_beg != NULL)
		delete v_beg;
	v_beg = new_vec;
}

template<class type>
typename vector<type>::iterator vector<type>::begin()
{
	return v_beg;
}

template<class type>
typename vector<type>::iterator vector<type>::end()
{
	return v_beg + vec_size;
}

template<class type>
void vector<type>::push_back(type x)
{
	type* new_vec = new type[vec_size + 1];
	for (int i = 0; i < vec_size; ++i)
	{
		new_vec[i] = v_beg[i];
	}
	new_vec[vec_size] = x;
	if (v_beg != NULL)
		delete v_beg;
	++vec_size;
	v_beg = new_vec;
}

template<class type>
int vector<type>::size()
{
	return vec_size;
}

template<class type>
void vector<type>::pop_back()
{
	type* new_vec = new type[--vec_size];
	for (int i = 0; i < vec_size; ++i)
	{
		new_vec[i] = v_beg[i];
	}
	if (v_beg != NULL)
		delete v_beg;
	v_beg = new_vec;
}

template<class type>
type& vector<type>::operator[](const int p)
{
	return *(v_beg + p);
}

template<class type>
type* vector<type>::at(const int p)
{
	return (p >= 0 && p < vec_size) ? (v_beg + p) : (nullptr);
}

template<class type>
bool vector<type>::empty()
{
	return (vec_size < 1) ? (true) : (false);
}

template<class type>
bool vector<type>::operator==(const vector<type>& v)
{
	if (vec_size == v.vec_size)
	{
		for (int i = 0; i < vec_size; ++i)
		{
			if (*(v_beg + i) != *(v.v_beg+i))
				return false;
		}
		return true;
	}
	return false;
}

template<class type>
vector<type>& vector<type>::operator=(const vector<type>& v)
{
	if (vec_size == v.vec_size)
	{
		for (int i = 0; i < vec_size; ++i)
		{
			*(v_beg + i) = *(v.v_beg + i);
		}
	}
	else
	{
		if (v_beg != NULL)
			delete v_beg;
		vec_size = v.vec_size;
		v_beg = new type[vec_size];
		for (int i = 0; i < vec_size; ++i)
		{
			*(v_beg + i) = *(v.v_beg + i);
		}
	}
	return *this;
}

template<class type>
vector<type>& vector<type>::operator=(vector<type>&& v)
{
	std::swap(v_beg, v.v_beg);
	std::swap(vec_size, v.vec_size);
	return *this;
}

template<class type>
void vector<type>::clear()
{
	if (v_beg != NULL)
		delete v_beg;
	vec_size = 0;
}

template<class type>
typename vector<type>::iterator vector<type>::erase(iterator it)
{
	type* new_vec = new type[--vec_size];
	int i;
	for (i = 0; v_beg + i != it.index; ++i)
	{
		new_vec[i] = v_beg[i];
	}
	int j = i;
	for (; i < vec_size; ++i)
	{
		new_vec[i] = v_beg[i + 1];
	}
	if (v_beg != NULL)
		delete v_beg;
	v_beg = new_vec;
	return new_vec+j;
}

template<class type>
typename vector<type>::iterator vector<type>::erase(iterator first, iterator last)
{
	vec_size -= (last.index - first.index);
	type* new_vec = new type[vec_size];
	int i;
	for (i = 0; v_beg + i != first.index; ++i)
	{
		new_vec[i] = v_beg[i];
	}
	int j = i;
	for (; i != vec_size; ++i)
	{
		new_vec[i] = v_beg[i + (last.index - first.index)];
	}
	if (v_beg != NULL)
		delete v_beg;
	v_beg = new_vec;
	return new_vec+j;
}

template<class type>
void vector<type>::swap(vector<type>& v)
{
	std::swap(v_beg, v.v_beg);
	std::swap(vec_size, v.vec_size);
}

template<class type>
void vector<type>::resize(int new_size)
{
	if (vec_size != new_size)
	{
		type* new_vec = new type[new_size];
		for (int i = 0; i < new_size && i < vec_size; ++i)
		{
			new_vec[i] = v_beg[i];
		}
		if (v_beg != NULL)
			delete v_beg;
		vec_size = new_size;
		v_beg = new_vec;
	}
}

//////////////////////////////////////////////////////




template<class type>
vector<type>::iterator::iterator(type* in) : index(in) {}

template<class type>
typename vector<type>::iterator vector<type>::iterator::operator++(int)
{
	iterator t(index++);
	return t;
}

template<class type>
typename vector<type>::iterator& vector<type>::iterator::operator++()
{
	++index;
	return *this;
}

template<class type>
typename type& vector<type>::iterator::operator*()
{
	return *(index);
}

template<class type>
typename vector<type>::iterator vector<type>::iterator::operator--(int)
{
	iterator t(index--);
	return t;
}

template<class type>
typename vector<type>::iterator& vector<type>::iterator::operator--()
{
	--index;
	return *this;
}

template<class type>
typename vector<type>::iterator& vector<type>::iterator::operator-(int x)
{
	iterator t(index - x);
	return t;
}

template<class type>
inline typename vector<type>::iterator& vector<type>::iterator::operator-=(const int d)
{
	index -= d;
	return *this;
}

template<class type>
inline int vector<type>::iterator::operator-(const vector<type>::iterator& it)
{
	return index - it.index;
}

template<class type>
typename vector<type>::iterator& vector<type>::iterator::operator+(int x)
{
	iterator t(index + x);
	return t;
}

template<class type>
typename vector<type>::iterator& vector<type>::iterator::operator+=(const int d)
{
	index += d;
	return *this;
}

template<class type>
typename vector<type>::iterator& vector<type>::iterator::operator=(const iterator& it)
{
	index = it.index;
	return *this;
}

template<class type>
bool vector<type>::iterator::operator<(const iterator& it)
{
	return index < it.index;
}

template<class type>
bool vector<type>::iterator::operator<=(const iterator& it)
{
	return index <= it.index;
}

template<class type>
bool vector<type>::iterator::operator>(const iterator& it)
{
	return index > it.index;
}

template<class type>
bool vector<type>::iterator::operator>=(const iterator& it)
{
	return index >= it.index;
}

template<class type>
bool vector<type>::iterator::operator!=(const iterator& it) const
{
	return (index != it.index);
}

template<class type>
bool vector<type>::iterator::operator==(const iterator& it) const
{
	return (index == it.index);
}