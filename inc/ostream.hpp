#if !defined(_OSTREAM_HPP_)
#define _OSTREAM_HPP_

#include <stdio.h>

namespace ede
{

#if !defined(NULL)
#define NULL 0
#endif // defined NULL

template < typename T >
class basic_ostream
{
private:
    FILE *strm;
    bool localfile, fileopen;
public:
    basic_ostream(FILE *fd): strm(fd), localfile(false), fileopen(!fd){}

    basic_ostream(const char *fname) : strm(NULL), localfile(true), fileopen(false)
    {
        strm = fopen(fname, "wa");
        fileopen = strm ? true : false;
    }

    ~basic_ostream()
    {
        if(localfile)
        {
            fclose(strm);
        }
    }

    basic_ostream& operator<<(const char *str)
    {
        fprintf(this->strm, "%s", str);
        return *this;
    }

    basic_ostream& operator<<(char c)
    {
        fprintf(this->strm, "%c", c);
        return *this;
    }

    basic_ostream& operator<<(long l)
    {
        fprintf(this->strm, "%i", l);
        return *this;
    }

    basic_ostream& operator<<(int i)
    {
        fprintf(this->strm, "%i", i);
        return *this;
    }

    basic_ostream& operator<<(float f)
    {
        fprintf(this->strm, "%f", f);
        return *this;
    }

    basic_ostream& operator<<(double d)
    {
        fprintf(this->strm, "%f", d);
        return *this;
    }
};

typedef basic_ostream<char> ostream;

extern ostream cout;
extern ostream cerr;
ostream cout(stdout);
ostream cerr(stderr);
}

#endif // defined _OSTREAM_HPP_
