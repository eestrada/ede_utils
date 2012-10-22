#include <iostream>
#include "header.hpp"
#include "edelist.hpp"
#include "nullstream.hpp"

using ede::nout;
using std::cout;
using std::cerr;
using std::endl;

void cprint(std::ostream &strm, const char *s)
{
    strm << s;
}

int main(void)
{   
    std::ostream *strmPtr;
    if(true)
        strmPtr = &cerr;
    else
        strmPtr = &nout;

    std::ostream &test = *strmPtr;
    cprint(cout, "\nThis should print.\n\n");
    cprint(nout, "\nThis should not print.\n\n");
    cprint(test, "\nWhat will this print?\n\n");

//    cout << "This is the default program." << endl;
}

