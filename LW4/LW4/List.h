#pragma once
#include<iostream>

template<class Type>
class list
{
public:
    class iterator;

    virtual ~list();
    list() = default;
    list(const int);
    template <class Init>
    list(Init, Init);
    list(const Type*, const int);
    list(list<Type>&);
    list(list<Type>&&);
    iterator begin();
    iterator end();
    void push_back(Type);
    void push_front(Type);
    int32_t size();
    void pop_back();
    void pop_front();
    bool empty();
    list& operator=(list<Type>&);
    list& operator=(list<Type>&&);
    void clear();
    void emplace(iterator, Type&&);
    void emplace_back(Type&&);
    void emplace_front(Type&&);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    void swap(list<Type>&);
    void resize(const int32_t);
    void reverse();
    template <class Pred>
    void remove_if(Pred con);
    void merge(list<Type>& right);
    template <class Pred>
    void merge(list& right, Pred con);
    void insert(iterator pl, int count, const Type& val);
    template <class Init>
    void insert(iterator pl, Init first, Init last);

private:
    struct lelem
    {
        Type data;
        lelem* next = nullptr;
        lelem* prev = nullptr;

        lelem() {};
        lelem(const Type& x) : data(x) {}
        lelem(Type&& x) : data(static_cast<Type&&> x) {}
    };
    lelem* head = nullptr;
    lelem* tail = nullptr;
    int32_t l_size = 0;

public:
    class iterator
    {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = Type*;
        typedef const Type* const_pointer;
        using reference = Type&;

        iterator(lelem*, lelem*);
        iterator operator++(int);
        iterator& operator++();
        Type& operator*();
        iterator operator--(int);
        iterator& operator--();
        iterator& operator=(const iterator&);
        bool operator!=(const iterator&) const;
        bool operator==(const iterator&) const;
    private:
        lelem* el = nullptr;
        lelem* tail = nullptr;
    };
};

template<class Type>
list<Type>::~list()
{
    clear();
}

template<class Type>
list<Type>::list(const int size) : l_size(size)
{
    head = new lelem;
    lelem* t = head;
    for (int i = 1; i < l_size; ++i)
    {
        tail = new lelem;
        tail->prev = t;
        t->next = tail;
        t = t->next;
    }
}

template<class Type>
template<class Init>
list<Type>::list(Init first, Init last)
{
    head = new lelem(*(first++));
    lelem* t = head;
    ++l_size;
    while (first != last)
    {
        t->next = new lelem(*(first++));
        t->next->prev = t;
        t = t->next;
        ++l_size;
    }
    tail = t;
}

template<class Type>
list<Type>::list(const Type* a, const int s) : list(a, a + s)
{}

template<class Type>
list<Type>::list(list<Type>& l) : list(l.begin(), l.end())
{}

template<class Type>
list<Type>::list(list<Type>&& l)
{
    std::swap(head, l.head);
    std::swap(tail, l.tail);
    std::swap(l_size, l.l_size);
}

template<class Type>
typename list<Type>::iterator list<Type>::begin()
{
    return { head, tail };
}

template<class Type>
typename list<Type>::iterator list<Type>::end()
{
    return { nullptr, tail };
}

template<class Type>
void list<Type>::push_back(Type x)
{
    if (head == nullptr)
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

template<class Type>
void list<Type>::push_front(Type x)
{
    if (head == nullptr)
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

template<class Type>
int32_t list<Type>::size()
{
    return l_size;
}

template<class Type>
void list<Type>::pop_back()
{
    if (l_size != 0)
    {
        lelem* t = tail->prev;
        delete tail;
        tail = t;
        if (t != nullptr)
        {
            t->next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        --l_size;
    }
}

template<class Type>
void list<Type>::pop_front()
{
    if (l_size != 0)
    {
        lelem* t = head->next;
        delete head;
        head = t;
        if (t != nullptr)
        {
            t->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }
        --l_size;
    }
}

template<class Type>
bool list<Type>::empty()
{
    return (l_size == 0);
}

template<class Type>
list<Type>& list<Type>::operator=(list<Type>& l)
{
    *this = list(l.begin(), l.end());
    return *this;
}

template<class Type>
list<Type>& list<Type>::operator=(list<Type>&& l)
{
    std::swap(head, l.head);
    std::swap(tail, l.tail);
    std::swap(l_size, l.l_size);
    return *this;
}

template<class Type>
void list<Type>::clear()
{
    auto i = head;
    while (i != nullptr)
    {
        auto j = i;
        i = i->next;
        delete j;
    }
    head = tail = nullptr;
    l_size = 0;
}

template<class Type>
void list<Type>::emplace(iterator pl, Type&& val)
{
    lelem* t = new lelem(static_cast<Type&&>(val));
    if (&*pl == &head->data)
    {
        t->next = head;
        head->prev = t;
        head = t;
    }
    else if (&*pl == nullptr)
    {
        t->prev = tail;
        tail->next = t;
        tail = t;
    }
    else
    {
        lelem* tt = head->next;
        while (&*pl != &tt->data)
        {
            tt = tt->next;
        }
        t->prev = tt->prev;
        t->next = tt;
        tt->prev = t;
    }
    ++l_size;
}

template<class Type>
void list<Type>::emplace_back(Type&& val)
{
    lelem* t = new lelem(static_cast<Type&&>(val));
    t->prev = tail;
    tail->next = t;
    tail = t;
    ++l_size;
}

template<class Type>
void list<Type>::emplace_front(Type&& val)
{
    lelem* t = new lelem(static_cast<Type&&>(val));
    t->next = head;
    head->prev = t;
    head = t;
    ++l_size;
}

template<class Type>
typename list<Type>::iterator list<Type>::erase(iterator it)
{
    if (&*it == &head->data)
    {
        ++it;
        pop_front();
    }
    else if (&*it == &tail->data)
    {
        --it;
        pop_back();
    }
    else if (&*it != nullptr)
    {
        lelem* t = head->next;
        while (&*it != &t->data)
        {
            t = t->next;
        }
        lelem* tt =t->next;
        tt->prev = t->prev;
        t->prev->next = tt;
        delete t;
        t = tt;
    }
    --l_size;
    return it;
}

template<class Type>
typename list<Type>::iterator list<Type>::erase(iterator first, iterator last)
{
    if (&*first == &head->data)
    {
        while (first != last)
        {
            --l_size;
            head = head->next;
            ++first;
            delete head->prev;
        }
        head->prev = nullptr;
    }
    else
    {
        lelem* t = head->next;
        while (&*first != &t->data)
        {
            t = t->next;
        }
        lelem* tt = t->prev;
        while (first != last)
        {
            --l_size;
            ++first;
            t = t->next;
            delete t->prev;
        }
        t->prev = tt;
        tt->next = t;
    }
    return first;
}

template<class Type>
void list<Type>::swap(list<Type>& l)
{
    std::swap(head, l.head);
    std::swap(tail, l.tail);
    std::swap(l_size, l.l_size);
}

template<class Type>
void list<Type>::resize(const int32_t new_size)
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
                tail->next = nullptr;
            }
        }
    }
}

template<class Type>
void list<Type>::reverse()
{
    auto i = head;
    while (i != nullptr)
    {
        std::swap(i->next, i->prev);
        i = i->prev;
    }
    std::swap(head, tail);
}

template<class Type>
template<class Pred>
void list<Type>::remove_if(Pred con)
{
    auto i = head;
    while (i != nullptr)
    {
        if (con(i->data))
        {
            if (i == head)
            {
                i->next->prev = nullptr;
                head = i->next;
                delete i;
                i = head;
            }
            else if (i == tail)
            {
                i->prev->next = nullptr;
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

template<class Type>
void list<Type>::merge(list<Type>& right)
{
    lelem* t = right.head;
    while (t != nullptr)
    {
        tail->next = t;
        t->prev = tail;
        tail = t;
        t = t->next;
    }
    right.head = right.tail = nullptr;
    l_size += right.l_size;
    right.l_size = 0;
}

template<class Type>
template<class Pred>
inline void list<Type>::merge(list& right, Pred con)
{
    lelem* t = right.head;
    while (t != nullptr)
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
    right.head = right.tail = nullptr;
    right.l_size = 0;
}

template<class Type>
void list<Type>::insert(iterator pl, int count, const Type& val)
{
    if (&*pl == &head->data)
    {
        while (count--)
        {
            push_front(val);
        }
    }
    else if (&*pl == nullptr)
    {
        while (count--)
        {
            push_back(val);
        }
    }
    else
    {
        lelem* t = head->next;
        while (&*pl != &t->data)
        {
            t = t->next;
        }
        while (count--)
        {
            lelem* tt = new lelem(val);
            t->prev->next = tt;
            tt->prev = t->prev;
            t->prev = tt;
            tt->next = t;
        }
    }
}

template<class Type>
template<class Init>
void list<Type>::insert(iterator pl, Init first, Init last)
{
    if (&*pl == &head->data)
    {
        while (first != last)
        {
            push_front(*(first++));
        }
    }
    else if (&*pl == nullptr)
    {
        while (first != last)
        {
            push_back(*(first++));
        }
    }
    else if(&*pl != nullptr)
    {
        lelem* t = head->next;
        while (&*pl != &t->data)
        {
            t = t->next;
        }
        while (first != last)
        {
            lelem* tt = new lelem(*(first++));
            t->prev->next = tt;
            tt->prev = t->prev;
            t->prev = tt;
            tt->next = t;
        }
    }
}

//////////////////////////////////////////////////////

template<class Type>
list<Type>::iterator::iterator(lelem* in, lelem* t) : el(in), tail(t) {}


template<class Type>
typename list<Type>::iterator list<Type>::iterator::operator++(int)
{
    if (el != nullptr)
    {
        iterator t(el, tail);
        el = el->next;
        return t;
    }
    return *this;
}

template<class Type>
typename list<Type>::iterator& list<Type>::iterator::operator++()
{
    if (el != nullptr)
    {
        el = el->next;
    }
    return *this;
}

template<class Type>
typename Type& list<Type>::iterator::operator*()
{
    return el->data;
}

template<class Type>
typename list<Type>::iterator list<Type>::iterator::operator--(int)
{
    iterator t(el, tail);
    (el != nullptr) ? (el = el->prev) : (el = tail);
    return t;
}

template<class Type>
typename list<Type>::iterator& list<Type>::iterator::operator--()
{
    (el != nullptr) ? (el = el->prev) : (el = tail);
    return *this;
}

template<class Type>
typename list<Type>::iterator& list<Type>::iterator::operator=(const iterator& it)
{
    el = it.el;
    tail = it.tail;
    return *this;
}

template<class Type>
bool list<Type>::iterator::operator!=(const iterator& it) const
{
    return (el != it.el && tail == it.tail);
}

template<class Type>
bool list<Type>::iterator::operator==(const iterator& it) const
{
    return (el == it.el && tail == it.tail);
}