#ifndef _NULLOSTREAM_HPP_
#define _NULLOSTREAM_HPP_

#include <streambuf>
#include <ostream>

// Include under ede namespace.
namespace ede
{

/*
 * A stream buffer class that points nowhere. Inherits from basic_streambuf.
 */

template < class cT, class traits = std::char_traits<cT> >
class nullbuf: public std::basic_streambuf<cT, traits>
{
private:

    /*
     * This always returns success.
     *
     * Since we are not actually writing to anything, we can never overflow.
     * 
     * @param c Character to be written to buffer. Never actually used.
     * @return An int always representing success
     * */
    typename traits::int_type overflow(typename traits::int_type c)
    {
        return traits::not_eof(c); // indicate success
    };
};

/*
 * A stream that points nowhere by using nullbuf class.
 */

template < class cT, class traits = std::char_traits<cT> >
class basic_onullstream: public std::basic_ostream<cT, traits>
{
private:
    nullbuf<cT, traits> m_sbuf;

public:
    basic_onullstream():
        std::basic_ios<cT, traits>(&m_sbuf),
        std::basic_ostream<cT, traits>(&m_sbuf)
    {
        init(&m_sbuf);
    };
};

typedef basic_onullstream<char> nullostream;
typedef basic_onullstream<wchar_t> wnullostream;

/*
 * Declares a null ostream object.
 */
nullostream nout;

};

#endif // define _NULLOSTREAM_HPP_

