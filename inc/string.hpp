#if !defined(_STRING_HPP_)
#define _STRING_HPP_

#if !defined(NULL)
#define NULL 0
#endif // defined NULL

#include <iostream>

namespace ede
{

//#include <string.h>

template < typename T >
class base_string
{
private:
    T *_strptr;
    int _len;

    int _strlen(const T *str)
    {
        int c = 0;
        
        while(*str != '\0')
        {
            ++str;
            ++c;
        }

        return c;
    }

    void _strcopy(const T * src, T *dest)
    {
        if (src == dest) throw -1;

        while(*src != '\0')
        {
            *dest = *src;
            ++src;
            ++dest;
        }

        *dest = '\0';
    }

public:
    base_string() : _strptr(NULL), _len(0) {}
    
    base_string(const base_string<T> &other) : _strptr(NULL), _len(0)
    {
        std::cerr << "base_string Constructor.\n";
        if(this == &other) return;

        this->_len = other._len;

        this->_strptr = new T[this->_len + 1];

        this->_strcopy(other._strptr, this->_strptr);
    }
    
    base_string<T> & operator=(const base_string<T> &other)
    {
        std::cerr << "base_string assignment.\n";
        if(this == &other) return;

        base_string<T> tmp(other);

        base_string<T>::swap;
    }

    base_string(const T *other) : _strptr(NULL), _len(0)
    {
        std::cerr << "char * Constructor.\n";
        if(this->_strptr == other) return;

        this->_len = this->_strlen(other);

        this->_strptr = new T[this->_len + 1];

        this->_strcopy(other, this->_strptr);
    }

    base_string<T> & operator=(const T *other)
    {
        std::cerr << "char * assignment.\n";
        if(this->_strptr == other) return *this;

        base_string<T> tmp(other);

        this->_strptr = tmp._strptr;
        tmp._strptr = NULL;
        this->_len = tmp._len;
        tmp._len = 0;

        return *this;
    }

    ~base_string()
    {
        if(this->_len)
            std::cerr << "String with a value of '" << this->_strptr << "' being deleted.\n";
        else
            std::cerr << "Empty string being deleted.\n";
            
        delete[] this->_strptr;
        this->_strptr = NULL;
    }

    static void swap(base_string <T> & lha, base_string <T> & rha)
    {
        T *tmp_str_ptr = lha._strptr;
        int tmp_len = lha._len;

        lha._strptr = rha._strptr;
        lha._len = rha._len;

        rha._strptr = tmp_str_ptr;
        rha._len = tmp_len;
    }

};

typedef base_string<char> string;

}// End namespace "ede"

#endif // defined _STRING_HPP_
