#pragma once
//#include<iostream>

template<class type>
class list
{
	struct lelem
	{
		using data_type = type;
		type data;
		lelem* next = NULL;
		lelem* prev = NULL;

		lelem() {}
		lelem(type x) { data = x; }
		lelem(type&& x) { data = static_cast<type&&>(x); }
	};
	lelem* head = NULL;
	lelem* tail = NULL;
	int l_size = 0;
public:
	class iterator
	{
		lelem* el;
		lelem* tail;
		friend class list;
	public:
		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = type;
		using difference_type = std::ptrdiff_t;
		using pointer = type*;
		typedef const type* const_pointer;
		using reference = type&;

		iterator(lelem*, lelem*);
		iterator operator++(int);
		iterator& operator++();
		type& operator*();
		iterator operator--(int);
		iterator& operator--();
		iterator& operator=(const iterator&);
		bool operator!=(const iterator&) const;
		bool operator==(const iterator&) const;
	};
	~list();
	list();
	list(const int);
	list(const type*, const int);
	template <class init>
	list(init, init);
	list(const list<type>&);
	list(list<type>&&);
	iterator begin();
	iterator end();
	void push_back(type);
	void push_front(type);
	int size();
	void pop_back();
	void pop_front();
	bool empty();
	list& operator=(const list<type>&);
	list& operator=(list<type>&&);
	void clear();
	void emplace(iterator, type&&);
	void emplace_back(type&&);
	void emplace_front(type&&);
	iterator erase(iterator);
	iterator erase(iterator, iterator);
	void swap(list<type>&);
	void resize(const int);
	void reverse();
	template <class pred>
	void remove_if(pred con);
	void merge(list<type>& right);
	template <class pred>
	void merge(list& right, pred con);
	void insert(iterator pl, int count, const type& val);
	template <class init>
	void insert(iterator pl, init first, init last);
};

template<class type>
list<type>::~list()
{
	clear();
}

template<class type>
list<type>::list() {}

template<class type>
list<type>::list(const int size) : l_size(size)
{
	head = new lelem;
	lelem* t = head;
	for (int i = 1; i < l_size; i++)
	{
		tail = new lelem;
		tail->prev = t;
		t->next = tail;
		t = t->next;
	}
}

template<class type>
list<type>::list(const type* a, const int s) : l_size(s)
{
	lelem* t = new lelem(*a);
	lelem* t = head;
	for (int i = 1; i < l_size; i++)
	{
		tail = new lelem;
		tail->data = *(a + i);
		tail->prev = t;
		t->next = tail;
		t = t->next;
	}
}

template<class type>
template<class init>
list<type>::list(init first, init last)
{
	lelem* t = new lelem(*(first++));
	lelem* t = head;
	++l_size;
	while (first != last)
	{
		t = new lelem(*first);
		tail->data = *(first++);
		tail->prev = t;
		t->next = tail;
		t = t->next;
		++l_size;
	}
}

template<class type>
list<type>::list(const list<type>& l)
{
	l_size = l.l_size;
	if (l.head != NULL)
	{
		head = new lelem((l.head)->data);
		lelem* t = head;
		lelem* tt = (l.head)->next;
		while (tt != NULL)
		{
			t->next = new lelem(tt->data);
			t->next->prev = t;
			t = t->next;
			tt = tt->next;
		}
		tail = t;
	}
}

template<class type>
list<type>::list(list<type>&& l)
{
	std::swap(head, l.head);
	std::swap(tail, l.tail);
	std::swap(l_size, l.l_size);
}

template<class type>
typename list<type>::iterator list<type>::begin()
{
	return { head, tail };
}

template<class type>
typename list<type>::iterator list<type>::end()
{
	return { NULL, tail };
}

template<class type>
void list<type>::push_back(type x)
{
	if (head == NULL)
	{
		head = new lelem(x);
		tail = head;
	}
	else
	{
		lelem* t = new lelem(x);
		t->prev = tail;
		tail->next = t;
		tail = t;
	}
		++l_size;
}

template<class type>
void list<type>::push_front(type x)
{
	if (head == NULL)
	{
		head = new lelem(x);
		tail = head;
	}
	else
	{
		lelem* t = new lelem(x);
		t->next = head;
		head->prev = t;
		head = t;
	}
		++l_size;
}

template<class type>
int list<type>::size()
{
	return l_size;
}

template<class type>
void list<type>::pop_back()
{
	lelem* t = tail->prev;
	delete tail;
	tail = t;
	t->next = NULL;
	--l_size;
}

template<class type>
void list<type>::pop_front()
{
	lelem* t = head->next;
	delete head;
	t->prev = NULL;
	head = t;
	--l_size;
}

template<class type>
bool list<type>::empty()
{
	return (l_size == 0) ? (true) : (false);
}

template<class type>
list<type>& list<type>::operator=(const list<type>& l)
{
	if (l_size >= l.l_size)
	{
		auto i = head, j = l.head;
		for (; i != NULL && j != NULL; i = i->next, j = j->next)
		{
			i->data = j->data;
		}
		if (l_size > l.l_size)
		{
			resize(l.l_size);
		}
	}
	else
	{
		resize(l.l_size);
		auto i = head, j = l.head;
		for (; i != NULL && j != NULL; i = i->next, j = j->next)
		{
			i->data = j->data;
		}
	}
	return *this;
}

template<class type>
list<type>& list<type>::operator=(list<type>&& l)
{
	std::swap(head, l.head);
	std::swap(tail, l.tail);
	std::swap(l_size, l.l_size);
	return *this;
}

template<class type>
void list<type>::clear()
{
	auto i = head;
	while (i != NULL)
	{
		auto j = i;
		i = i->next;
		delete j;
	}
	head = tail = NULL;
	l_size = 0;
}

template<class type>
void list<type>::emplace(iterator pl, type&& val)
{
	lelem* t = new lelem(static_cast<type&&>(val));
	if (pl.el == head)
	{
		head = t;
		t->next = pl.el;
		pl.el = t;
	}
	else
	{
		t->prev = pl.el->prev;
		t->next = pl.el;
		pl.el = t;
	}
	++l_size;
}

template<class type>
void list<type>::emplace_back(type&& val)
{
	lelem* t = new lelem(val);
	t->prev = tail;
	tail->next = t;
	tail = t;
	++l_size;
}

template<class type>
void list<type>::emplace_front(type&& val)
{
	lelem* t = new lelem(val);
	t->next = head;
	head->prev = t;
	head = t;
	++l_size;
}

template<class type>
typename list<type>::iterator list<type>::erase(iterator it)
{
	if (it.el == head)
	{
		head = head->next;
		delete head->prev;
		head->prev = NULL;
		it.el = head;
	}
	else if (it.el == tail)
	{
		tail = tail->prev;
		delete tail->next;
		tail->next = NULL;
		it.el = tail;
	}
	else
	{
		lelem* t = it.el->next;
		t->prev = it.el->prev;
		it.el->prev->next = t;
		delete it.el;
		it.el = t;
	}
	--l_size;
	return it;
}

template<class type>
typename list<type>::iterator list<type>::erase(iterator first, iterator last)
{
	if (first.el == head)
	{
		while (head != last.el)
		{
			--l_size;
			head = head->next;
			delete head->prev;
		}
		head->prev = NULL;
		first.el = head;
	}
	else
	{
		while (first != last)
		{
			--l_size;
			++first;
			delete first.el->prev;
		}
		head->prev = NULL;
	}
	return first;
}

template<class type>
void list<type>::swap(list<type>& l)
{
	std::swap(head, l.head);
	std::swap(tail, l.tail);
	std::swap(l_size, l.l_size);
}

template<class type>
void list<type>::resize(const int new_size)
{
	if (l_size != new_size)
	{
		if (l_size < new_size)
		{
			
			for (; l_size < new_size; ++l_size)
			{
				tail->next = new lelem;
				tail->next->prev = tail;
				tail = tail->next;
			}
		}
		else
		{
			for (; l_size != new_size; --l_size)
			{
				tail = tail->prev;
				delete tail->next;
				tail->next = NULL;
			}
		}
	}
}

template<class type>
void list<type>::reverse()
{
	auto i = head;
	while (i != NULL)
	{
		std::swap(i->next, i->prev);
		i = i->prev;
	}
	std::swap(head, tail);
}

template<class type>
template<class pred>
void list<type>::remove_if(pred con)
{
	auto i = head;
	while (i != NULL)
	{
		if (con(i->data))
		{
			if (i == head)
			{
				i->next->prev = NULL;
				head = i->next;
				delete i;
				i = head;
			}
			else if (i == tail)
			{
				i->prev->next = NULL;
				tail = i->prev;
				delete i;
				break;
			}
			else
			{
				i->next->prev = i->prev;
				i = i->next;
				delete i->prev->next;
				i->prev->next = i;
			}
			--l_size;
		}
		else
		{
			i = i->next;
		}
	}
}

template<class type>
void list<type>::merge(list<type>& right)
{
	lelem* t = right.head;
	while (t != NULL)
	{
		tail->next = t;
		t->prev = tail;
		tail = t;
		t = t->next;
	}
	right.head = right.tail = NULL;
	l_size += right.l_size;
	right.l_size = 0;
}

template<class type>
template<class pred>
inline void list<type>::merge(list& right, pred con)
{
	lelem* t = right.head;
	while (t != NULL)
	{
		if (con(t->data))
		{
			tail->next = t;
			t->prev = tail;
			tail = t;
			++l_size;
		}
		t = t->next;
	}
	right.head = right.tail = NULL;
	right.l_size = 0;
}

template<class type>
void list<type>::insert(iterator pl, int count, const type& val)
{
	if (pl.el == head)
	{
		while (count--)
		{
			push_front(val);
		}
	}
	if (pl.el == tail)
	{
		while (count--)
		{
			push_back(val);
		}
	}
	else
	{
		lelem* t;
		while (count--)
		{
			t = new lelem(val);
			pl.el->prev = t;
			t = pl.el->next;
			pl.el = t;
		}
	}
}

template<class type>
template<class init>
void list<type>::insert(iterator pl, init first, init last)
{
	if (pl.el == head)
	{
		while (first != last)
		{
			push_front(*(first++));
		}
	}
	if (pl.el == tail)
	{
		while (first != last)
		{
			push_back(*(first++));
		}
	}
	else
	{
		lelem* t = (pl.el)->prev;
		while (first != last)
		{
			t->next = new lelem(*(first++));
			t->next->prev = t;
			t = t->next;
		}
		t->next = (pl.el);
		(pl.el)->prev = t;
	}
}

//////////////////////////////////////////////////////

template<class type>
list<type>::iterator::iterator(lelem* in, lelem* t) : el(in), tail(t) {}


template<class type>
typename list<type>::iterator list<type>::iterator::operator++(int)
{
	iterator t(el);
	el = el->next;
	return t;
}

template<class type>
typename list<type>::iterator& list<type>::iterator::operator++()
{
	el = el->next;
	return *this;
}

template<class type>
typename type& list<type>::iterator::operator*()
{
	return el->data;
}

template<class type>
typename list<type>::iterator list<type>::iterator::operator--(int)
{
	iterator t(el);
	(el != NULL) ? (el = el->prev) : (el = tail);
	return t;
}

template<class type>
typename list<type>::iterator& list<type>::iterator::operator--()
{
	(el != NULL) ? (el = el->prev) : (el = tail);
	return *this;
}

template<class type>
typename list<type>::iterator& list<type>::iterator::operator=(const iterator& it)
{
	el = it.el;
	return *this;
}

template<class type>
bool list<type>::iterator::operator!=(const iterator& it) const
{
	return (el != it.el);
}

template<class type>
bool list<type>::iterator::operator==(const iterator& it) const
{
	return (el == it.el);
}