//#include "edelist.hpp"
//#include "nullstream.hpp"
#include "ostream.hpp"
#include "string.hpp"

using namespace ede;

int main(void)
{   
    string teststr = "Test string one.\n";
    string teststr2 = "Test string two.\n";
    
    cout << teststr;
    cerr << teststr2;

    cout << "\nThis should print to stdout.\n\n";
    cerr << "\nThis should print to stderr.\n\n";

    cout << 400 << "\n\n";
    cout << 400.0 << "\n\n";
}

