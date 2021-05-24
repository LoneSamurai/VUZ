#pragma once
#include<iostream>

template<class Type>
class vector
{
public:
    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = Type*;
        typedef const Type* const_pointer;
        using reference = Type&;

        iterator(Type*);
        typename iterator operator++(int);
        typename iterator& operator++();
        Type& operator*();
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
    private:
        Type* index = nullptr;
        iterator();
    };
    virtual ~vector();
    vector() = default;
    vector(const int);
    vector(const Type*, const int);
    vector(const vector<Type>&);
    vector(vector<Type>&&);
    template <class Init>
    vector(Init first, Init last);
    typename iterator begin();
    typename iterator end();
    void push_back(Type);
    int32_t size();
    void pop_back();
    Type& operator[](const int);
    Type* at(const int);
    bool empty();
    bool operator==(const vector<Type>&);
    vector& operator=(const vector<Type>&);
    vector& operator=(vector<Type>&&);
    void clear();
    typename iterator erase(iterator);
    typename iterator erase(iterator, iterator);
    void swap(vector<Type>&);
    void resize(const int32_t new_size);
    template <class Init>
    void assign(Init first, Init last);
    void assign(int count, const Type& value);
    void insert(iterator pos, const int count, const Type& value);
    template <class Init>
    void insert(iterator pos, Init first, Init last);
private:
    Type* v_beg = nullptr;
    int32_t vec_size = 0;
};

template<class Type>
vector<Type>::~vector()
{
    if(v_beg!=nullptr)
        delete v_beg;
}

template<class Type>
vector<Type>::vector(const int s) : vec_size(s)
{
    v_beg = new Type[vec_size];
}

template<class Type>
vector<Type>::vector(const Type* a, const int s) : vec_size(s)
{
    v_beg = new Type[vec_size];
    for (int i = 0; i < vec_size; ++i)
    {
        v_beg + i = a[i];
    }
}

template<class Type>
template<class Init>
vector<Type>::vector(Init first, Init last)
{
    
    for (auto it = first; it != last; ++it)
        ++vec_size;
    
    v_beg = new Type[vec_size];
    for (Type* i = v_beg; first != last; ++i, ++first)
    {
        *i = *first;
    }
}

template<class Type>
vector<Type>::vector(const vector<Type>& v)
{
    vec_size = v.vec_size;

    if (v_beg != nullptr)
        delete v_beg;

    v_beg = new Type[vec_size];
    for (int i = 0; i < vec_size; ++i)
    {
        v_beg[i] = v.v_beg[i];
    }
}

template<class Type>
vector<Type>::vector(vector<Type>&& v)
{
    std::swap(v_beg, v.v_beg);
    std::swap(vec_size, v.vec_size);
}

template<class Type>
void vector<Type>::assign(int count, const Type& value)
{
    if (v_beg != nullptr)
        delete v_beg;
    vec_size = count;
    v_beg = new Type[vec_size];
    while (count--)
    {
        v_beg[count] = value;
    }
}

template<class Type>
template<class Init>
void vector<Type>::assign(Init first, Init last)
{
    if (v_beg != nullptr)
    {
        delete[] v_beg;
        vec_size = 0;
    }
    for (auto it = first; it != last; ++it)
            ++vec_size;
    v_beg = new Type[vec_size];
    for (int i = 0; i < vec_size; ++i, ++first)
    {
        v_beg[i] = *first;
    }
}

template<class Type>
void vector<Type>::insert(iterator pos, const int count, const Type& value)
{
    vec_size += count;
    Type* new_vec = Type[vec_size];
    int i = 0;
    for (; v_beg + i < &*pos; ++i)
    {
        new_vec[i] = v_beg[i];
    }
    for (; v_beg + i < &*pos + count; ++i)
    {
        new_vec[i] = value;
    }
    for (; i < vec_size; ++i)
    {
        new_vec[i] = v_beg[i - count];
    }
    if (v_beg != nullptr)
        delete v_beg;
    v_beg = new_vec;
}

template<class Type>
template<class Init>
void vector<Type>::insert(iterator pos, Init first, Init last)
{
    
    int d = 0;
    for (auto it = first; it != last; ++it)
        ++d;
    vec_size += d;
    Type* new_vec = new Type[vec_size];
    int i = 0;
    for (; v_beg + i != &*pos; ++i)
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
    if (v_beg != nullptr)
        delete v_beg;
    v_beg = new_vec;
}

template<class Type>
typename vector<Type>::iterator vector<Type>::begin()
{
    return v_beg;
}

template<class Type>
typename vector<Type>::iterator vector<Type>::end()
{
    return v_beg + vec_size;
}

template<class Type>
void vector<Type>::push_back(Type x)
{
    Type* new_vec = new Type[vec_size + 1];
    for (int i = 0; i < vec_size; ++i)
    {
        new_vec[i] = v_beg[i];
    }
    new_vec[vec_size] = x;
    if (v_beg != nullptr)
        delete v_beg;
    ++vec_size;
    v_beg = new_vec;
}

template<class Type>
int32_t vector<Type>::size()
{
    return vec_size;
}

template<class Type>
void vector<Type>::pop_back()
{
    Type* new_vec = new Type[--vec_size];
    for (int i = 0; i < vec_size; ++i)
    {
        new_vec[i] = v_beg[i];
    }
    if (v_beg != nullptr)
        delete v_beg;
    v_beg = new_vec;
}

template<class Type>
Type& vector<Type>::operator[](const int p)
{
    return *(v_beg + p);
}

template<class Type>
Type* vector<Type>::at(const int p)
{
    return (p >= 0 && p < vec_size) ? (v_beg + p) : (nullptr);
}

template<class Type>
bool vector<Type>::empty()
{
    return (vec_size < 1);
}

template<class Type>
bool vector<Type>::operator==(const vector<Type>& v)
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

template<class Type>
vector<Type>& vector<Type>::operator=(const vector<Type>& v)
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
        if (v_beg != nullptr)
            delete v_beg;
        vec_size = v.vec_size;
        v_beg = new Type[vec_size];
        for (int i = 0; i < vec_size; ++i)
        {
            *(v_beg + i) = *(v.v_beg + i);
        }
    }
    return *this;
}

template<class Type>
vector<Type>& vector<Type>::operator=(vector<Type>&& v)
{
    std::swap(v_beg, v.v_beg);
    std::swap(vec_size, v.vec_size);
    return *this;
}

template<class Type>
void vector<Type>::clear()
{
    if (v_beg != nullptr)
        delete v_beg;
    vec_size = 0;
}

template<class Type>
typename vector<Type>::iterator vector<Type>::erase(iterator it)
{
    Type* new_vec = new Type[--vec_size];
    int i;
    for (i = 0; v_beg + i != &*it; ++i)
    {
        new_vec[i] = v_beg[i];
    }
    int j = i;
    for (; i < vec_size; ++i)
    {
        new_vec[i] = v_beg[i + 1];
    }
    if (v_beg != nullptr)
        delete v_beg;
    v_beg = new_vec;
    return new_vec+j;
}

template<class Type>
typename vector<Type>::iterator vector<Type>::erase(iterator first, iterator last)
{
    vec_size -= (&*last - &*first);
    Type* new_vec = new Type[vec_size];
    int i;
    for (i = 0; v_beg + i != &*last; ++i)
    {
        new_vec[i] = v_beg[i];
    }
    int j = i;
    for (; i != vec_size; ++i)
    {
        new_vec[i] = v_beg[i + (&*last - &*first)];
    }
    if (v_beg != nullptr)
        delete v_beg;
    v_beg = new_vec;
    return new_vec+j;
}

template<class Type>
void vector<Type>::swap(vector<Type>& v)
{
    std::swap(v_beg, v.v_beg);
    std::swap(vec_size, v.vec_size);
}

template<class Type>
void vector<Type>::resize(const int32_t new_size)
{
    if (vec_size != new_size)
    {
        Type* new_vec = new Type[new_size];
        for (int i = 0; i < new_size && i < vec_size; ++i)
        {
            new_vec[i] = v_beg[i];
        }
        if (v_beg != nullptr)
            delete v_beg;
        vec_size = new_size;
        v_beg = new_vec;
    }
}

//////////////////////////////////////////////////////




template<class Type>
vector<Type>::iterator::iterator(Type* in) : index(in) {}

template<class Type>
typename vector<Type>::iterator vector<Type>::iterator::operator++(int)
{
    iterator t(index++);
    return t;
}

template<class Type>
typename vector<Type>::iterator& vector<Type>::iterator::operator++()
{
    ++index;
    return *this;
}

template<class Type>
typename Type& vector<Type>::iterator::operator*()
{
    return *(index);
}

template<class Type>
typename vector<Type>::iterator vector<Type>::iterator::operator--(int)
{
    iterator t(index--);
    return t;
}

template<class Type>
typename vector<Type>::iterator& vector<Type>::iterator::operator--()
{
    --index;
    return *this;
}

template<class Type>
typename vector<Type>::iterator& vector<Type>::iterator::operator-(int x)
{
    iterator t(index - x);
    return t;
}

template<class Type>
inline typename vector<Type>::iterator& vector<Type>::iterator::operator-=(const int d)
{
    index -= d;
    return *this;
}

template<class Type>
inline int vector<Type>::iterator::operator-(const vector<Type>::iterator& it)
{
    return index - it.index;
}

template<class Type>
typename vector<Type>::iterator& vector<Type>::iterator::operator+(int x)
{
    iterator t(index + x);
    return t;
}

template<class Type>
typename vector<Type>::iterator& vector<Type>::iterator::operator+=(const int d)
{
    index += d;
    return *this;
}

template<class Type>
typename vector<Type>::iterator& vector<Type>::iterator::operator=(const iterator& it)
{
    index = it.index;
    return *this;
}

template<class Type>
bool vector<Type>::iterator::operator<(const iterator& it)
{
    return index < it.index;
}

template<class Type>
bool vector<Type>::iterator::operator<=(const iterator& it)
{
    return index <= it.index;
}

template<class Type>
bool vector<Type>::iterator::operator>(const iterator& it)
{
    return index > it.index;
}

template<class Type>
bool vector<Type>::iterator::operator>=(const iterator& it)
{
    return index >= it.index;
}

template<class Type>
bool vector<Type>::iterator::operator!=(const iterator& it) const
{
    return (index != it.index);
}

template<class Type>
bool vector<Type>::iterator::operator==(const iterator& it) const
{
    return (index == it.index);
}