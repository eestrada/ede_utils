#if !defined(__STREAMBUF_HPP__)
#define __STREAMBUF_HPP__

namespace ede
{

template <typename charT >
class basic_streambuf
{
public:
    // types:
    typedef charT char_type;
    typedef size_t streamsize;
    typedef int int_type;
    typedef int_type pos_type;

    virtual ~basic_streambuf()
    {
        delete ibuffer;
        ibuffer = NULL;
    }

    // 27.6.2.2.2 buffer and positioning:
    virtual basic_streambuf* pubsetbuf(char_type* s, streamsize n)
    {
        ibuffer = s;
        bufsize = n;

        return this;
    }

    virtual int pubsync()
    {
        return this->sync();
    }

    // 27.6.2.2.5 Put area:
    virtual int_type sputc(char_type c)
    {
        ibuffer[current_pos++] = c;
        if(current_pos >= bufsize)
        {
            current_pos = 0;
            return this->sync();
        }
        return c;
    }

    virtual streamsize sputn(const char_type* s, streamsize n)
    {
        for(size_t i = 0; i < n; ++i)
        {
            this->sputc(s[i]);
        }

        return n;
    }

protected:
    basic_streambuf() : ibuffer(NULL), bufsize(0), current_pos(0){}
    basic_streambuf(const basic_streambuf& rhs)
    {
        this->ibuffer = rhs.ibuffer;
        this->bufsize = rhs.bufsize;
        this->current_pos = rhs.current_pos;
    }

    virtual basic_streambuf& operator=(const basic_streambuf& rhs)
    {
        basic_streambuf tmp(rhs);

        this->swap(tmp);
    }

    virtual void swap(basic_streambuf& rhs)
    {
        char_type *tbuf = this->ibuffer;
        streamsize tbs = this->bufsize;
        int_type tcp = this->current_pos;

        this->ibuffer = rhs.ibuffer;
        this->bufsize = rhs.bufsize;
        this->current_pos = rhs.current_pos;

        rhs.ibuffer = tbuf;
        rhs.bufsize = tbs;
        rhs.current_pos = tcp;
    }

    virtual int sync() = 0;

    char_type *ibuffer;
    streamsize bufsize;
    int_type current_pos;
};

typedef basic_streambuf<char> streambuf;
}  // std

#endif // Defined __STREAMBUF_HPP__

