#include <chrono>
#include <functional>
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

string replace(const string &input, regex &rgx, function<string(smatch &)> callback)
{
    string ret = "";
    smatch matcher;

    string in = input;
    while (regex_search(in, matcher, rgx))
    {
        ret += matcher.prefix();
        ret += callback(matcher);
        in = matcher.suffix();
    }
    ret += in;

    return ret;
}

int main(int argc, char const *argv[])
{
    // regex rgx("test");
    // string out = replace(input_, rgx, [](smatch &m){
    //     string match = m.str(0);

    //     return "mega";
    // });
    auto t1 = std::chrono::high_resolution_clock::now();

    string inputFileName = "test.pug";
    if (argc > 1)
    {
        inputFileName = string(argv[1]);
    }

    string out = pugcpp::PugCpp::render(inputFileName, nullptr);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    cout << "duration: " << duration << " us" << endl;
    cout << "rendered:" << endl;
    cout << out << endl;
}
