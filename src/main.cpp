#include <iostream>
#include "edelist.hpp"
#include "nullstream.hpp"
#include "string.hpp"

using ede::nout;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using namespace ede;

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
    
    cout << "\nwstring::npos = " << wstring::npos << endl;

    ede::string teststr = "Test text.";
    ede::string teststr2 = "New text.";
    teststr2 += " Plus some more text!\n";
    
    teststr = "Test text.";

    teststr = teststr2;
    cout << teststr;
    cout << "Type a string in: ";
    cin >> teststr2;
    cout << "You typed: " << teststr2 << endl;

    cout << "The first character you typed is: " << teststr2.at(0) << endl;


//    cout << "This is the default program." << endl;
}

