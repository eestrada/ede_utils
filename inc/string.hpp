#if !defined(_STRING_HPP_)
#define _STRING_HPP_

#include "ostream.hpp"

namespace ede
{

#include <string.h>
#include <stddef.h>

#if !defined(NULL)
#define NULL 0
#endif // defined NULL

template < typename T >
class basic_string
{
private:
    T *_strptr;
    size_t _len;
    size_t _capacity;

    size_t _strlen(const T *str)
    {
        size_t c = 0;
        
        while(*str != '\0')
        {
            ++str;
            ++c;
        }

        return c;
    }

    static void _strcopy(const T *src, T *dest)
    {
        if (src == dest) return;

        while(*src != '\0')
        {
            *dest = *src;
            ++src;
            ++dest;
        }

        *dest = '\0';
    }

public:
    static const size_t npos = -1;
public:
    basic_string() : _strptr(NULL), _len(0), _capacity(0) {}
    
    basic_string(const basic_string<T> &other) : 
    _strptr(NULL), _len(0), _capacity(0)
    {
//        std::cerr << "basic_string Constructor.\n";
        if(this == &other) return;

        this->_len = other._len;
        this->_capacity = this->_len + 1;

        this->_strptr = new T[this->_capacity];

        this->_strcopy(other._strptr, this->_strptr);
    }
    
    basic_string<T> & operator=(const basic_string<T> &other)
    {
//        std::cerr << "basic_string assignment.\n";
        if(this == &other) return *this;

        basic_string<T> tmp(other);

        basic_string<T>::swap(*this, tmp);

        return *this;
    }

    basic_string(const T *other) : _strptr(NULL), _len(0), _capacity(0)
    {
//        std::cerr << "char * Constructor.\n";
        if(this->_strptr == other) return;

        this->_len = this->_strlen(other);
        this->_capacity = this->_len + 1;

        this->_strptr = new T[this->_capacity];

        this->_strcopy(other, this->_strptr);
    }

    basic_string<T> & operator=(const T *other)
    {
//        std::cerr << "char * assignment.\n";
        if(this->_strptr == other) return *this;

        // Don't allocate space if the 'other' is the same size or smaller
        // than our currently allocated space.
        if(this->_strlen(other) < this->_capacity)
        {
            this->_strcopy(other, this->_strptr);
            this->_len = this->_strlen(this->_strptr);
            return *this;
        }
        // Otherwise allocate new space and delete the old space.
        basic_string<T> tmp(other);

        basic_string<T>::swap(*this, tmp);

        return *this;
    }

    ~basic_string()
    {
/*        if(this->_len)
            std::cerr << "String with a value of '" << this->_strptr << "' being deleted.\n";
        else
            std::cerr << "Empty string being deleted.\n";
*/           
        delete[] this->_strptr;
        this->_strptr = NULL;
    }

    static void swap(basic_string <T> & lha, basic_string <T> & rha)
    {
        T *tmp_str_ptr = lha._strptr;
        size_t tmp_len = lha._len;
        size_t tmp_capacity = lha._capacity;

        lha._strptr = rha._strptr;
        lha._len = rha._len;
        lha._capacity = rha._capacity;

        rha._strptr = tmp_str_ptr;
        rha._len = tmp_len;
        rha._capacity = tmp_capacity;
    }

    size_t size() const {return this->_len;}
    size_t length() const {return this->size();}
    size_t capacity() const {return this->_capacity;}
    bool empty() const {return !(this->size());}

    basic_string<T> & operator+=(const basic_string<T> &other)
    {
        basic_string<T> workstr(other);
        size_t s = (workstr.size() + this->size());
        if(s >= this->capacity())
        {
            this->_capacity = s + 1;
            T *tmp = new T[_capacity];
            T *todelete = this->_strptr;

            this->_strcopy(todelete, tmp);

            this->_strptr = tmp;
            delete[] todelete;
        }
        this->_strcopy(workstr._strptr, this->_strptr + this->_len);

        this->_len = s;

        return *this;
    }

    basic_string<T> & operator+=(const T *other)
    {
        basic_string<T> tmp(other);

        this->operator+=(tmp);

        return *this;
    }

    const T* c_str() const
    {
        return this->_strptr;
    }

    T& operator[](size_t index)
    {
        return this->_strptr[index];
    }

    const T& operator[](size_t index) const
    {
        return this->_strptr[index];
    }
    
    T& at(size_t index)
    {
        if(index > this->size())
            {throw "Index out of bounds.";}

        return this->_strptr[index];
    }
    
    const T& at(size_t index) const
    {
        if(index > this->size())
            {throw "Index out of bounds.";}

        return this->_strptr[index];
    }
};// End of basic_string template class

typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;

}// End namespace "ede"

template < typename U >
ede::ostream & operator<<(ede::ostream & out, const ede::basic_string<U> &str)
{
    out << str.c_str();
    return out;
}

/*
template < typename U >
std::istream & operator>>(std::istream & in, ede::basic_string<U> &str)
{
    U cstr[2048];
    in >> cstr;
    str = cstr;
    return in;
}
*/
#endif // defined _STRING_HPP_
