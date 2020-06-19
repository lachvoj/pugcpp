#include <iostream>
#include <regex>
#include <string>

#include "../lib/include/PugCpp.hpp"

using namespace std;

string input_ = "test test \n test 123";

void findInLine(const string &re)
{
    regex rgx(re);
    smatch sm;
    string s = "null";
    if (regex_search(input_, sm, rgx))
    {
        s = sm[0].str();
    }
    cout << s << endl;
    cout << sm.position(0) << endl;
    cout << sm[0].length() << endl;
}

int main(int argc, char const *argv[])
{
    string out = pugcpp::PugCpp::render("test.pug", nullptr);

    return 0;
}
