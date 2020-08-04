#include "./ArgumentSplitter.hpp"

namespace pugcpp
{
namespace util
{
void ArgumentSplitter::split(vector<string> &ret, const string &arguments)
{
    size_t argLength = arguments.length();
    bool insideQuotas = false;
    int bracesBlock = 0;
    string builder;
    builder.reserve(argLength);

    for (size_t i = 0; i < argLength; i++)
    {
        char ch = arguments[i];

        if (isQuoted(ch))
            insideQuotas = !insideQuotas;

        else if (isOpeningBraces(ch))
            bracesBlock++;

        else if (isClosingBraces(ch))
            bracesBlock--;

        // detect argument delimiter, then push argument
        else if (ch == ARGUMENT_DELIMITER && !insideQuotas && bracesBlock == 0)
        {
            addArgument(ret, builder);
            builder.clear();
        }
        builder.push_back(ch);
    }
    addArgument(ret, builder);
}

const bool ArgumentSplitter::isClosingBraces(const char ch)
{
    return (ch == ')' || ch == ']' || ch == '}');
}

const bool ArgumentSplitter::isOpeningBraces(const char ch)
{
    return (ch == '(' || ch == '[' || ch == '{');
}

const bool ArgumentSplitter::isQuoted(const char ch)
{
    return (ch == '"' || ch == '\'');
}

void ArgumentSplitter::addArgument(vector<string> &ret, string &argument)
{
    StringUtils::trim(argument);
    StringUtils::replaceAll(argument, "^,", "");
    StringUtils::trim(argument);

    ret.push_back(argument);
}

} // namespace util
} // namespace pugcpp