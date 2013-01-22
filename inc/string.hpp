#if !defined(_STRING_HPP_)
#define _STRING_HPP_

#if !defined(NULL)
#define NULL 0
#endif // defined NULL

#include <stddef.h>
#include <iostream>

namespace ede
{

//#include <string.h>

template < typename T >
class base_string
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
    base_string() : _strptr(NULL), _len(0), _capacity(0) {}
    
    base_string(const base_string<T> &other) : 
    _strptr(NULL), _len(0), _capacity(0)
    {
        std::cerr << "base_string Constructor.\n";
        if(this == &other) return;

        this->_len = other._len;
        this->_capacity = this->_len + 1;

        this->_strptr = new T[this->_capacity];

        this->_strcopy(other._strptr, this->_strptr);
    }
    
    base_string<T> & operator=(const base_string<T> &other)
    {
        std::cerr << "base_string assignment.\n";
        if(this == &other) return *this;

        base_string<T> tmp(other);

        base_string<T>::swap(*this, tmp);

        return *this;
    }

    base_string(const T *other) : _strptr(NULL), _len(0), _capacity(0)
    {
        std::cerr << "char * Constructor.\n";
        if(this->_strptr == other) return;

        this->_len = this->_strlen(other);
        this->_capacity = this->_len + 1;

        this->_strptr = new T[this->_capacity];

        this->_strcopy(other, this->_strptr);
    }

    base_string<T> & operator=(const T *other)
    {
        std::cerr << "char * assignment.\n";
        if(this->_strptr == other) return *this;

        // Don't allocate space if the 'other' is the same size or smaller
        // than our currently allocated space.
        if(this->_strlen(other) <= this->_len)
        {
            this->_strcopy(other, this->_strptr);
            this->_len = this->_strlen(this->_strptr);
            return *this;
        }
        // Otherwise allocate new space and delete the old space.
        base_string<T> tmp(other);

        base_string<T>::swap(*this, tmp);

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
        size_t tmp_len = lha._len;

        lha._strptr = rha._strptr;
        lha._len = rha._len;

        rha._strptr = tmp_str_ptr;
        rha._len = tmp_len;
    }

    size_t size() const {return this->_len;}
    size_t length() const {return this->size();}
    size_t capacity() const {return this->_capacity;}
    bool empty() const {return !(this->size());}

};

typedef base_string<char> string;

}// End namespace "ede"

#endif // defined _STRING_HPP_
