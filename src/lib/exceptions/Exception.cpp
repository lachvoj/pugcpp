#include "Exception.hpp"

#include <regex>

namespace pugcpp
{
namespace exceptions
{
Exception::Exception(const string &error, std::exception *e) : Exception(error)
{
    if (e != nullptr)
        throwable_ = e;
}

Exception::Exception(const string &error, bool printStack) : printStack_(printStack)
{
    error_ = string(regex_replace(error, regex("\n"), string("\\n")));

    if (printStack_)
        error_ += getStackTrace();
}

const char *Exception::what() const noexcept
{
    return error_.c_str();
}

const string &Exception::getMessage() const noexcept
{
    return error_;
}

void Exception::printStackTrace()
{
    cout << getStackTrace();
}

string Exception::getStackTrace()
{
    string ret;
#ifdef __linux__
    size_t wantedSize = 100;
    void *array[wantedSize];
    char **strings;
    size_t size;

    size = backtrace(array, wantedSize);
    strings = backtrace_symbols(array, size);
    ret += "\nStack trace: \n";
    for (size_t j = 0; j < size; ++j)
    {
        ret += string(strings[j]) + "\n";
    }
#elif
    ret = "printStackTrace() not supported."
#endif
    return ret;
}

} // namespace exceptions
} // namespace pugcpp