#include "./Utils.hpp"

#include "../util/StringUtils.hpp"

namespace pugcpp
{
namespace compiler
{
const regex Utils::interpolationPattern{"(\\\\)?([#!])\\{"};

void Utils::prepareInterpolate(vector<any> &ret, const string &str, bool xmlEscape)
{
    smatch matcher;
    string in = str;
    size_t start = 0;
    while (regex_search(in, matcher, interpolationPattern))
    {
        string before = matcher.prefix();
        if (xmlEscape)
            StringUtils::escapeHtml4(before);
        ret.push_back(make_any<string>(before));

        bool escape = matcher[1].matched;
        string flag = matcher.str(2);

        size_t openBrackets = 1;
        bool closingBracketFound = false;
        size_t matcherEnd = matcher.position(0) + matcher.length(0);
        size_t closingBracketIndex = matcherEnd;
        while (!closingBracketFound && closingBracketIndex < in.length())
        {
            char currentChar = in[closingBracketIndex];
            if (currentChar == '{')
                openBrackets++;
            else if (currentChar == '}')
            {
                openBrackets--;
                if (openBrackets == 0)
                    closingBracketFound = true;
            }
            closingBracketIndex++;
        }
        string code = in.substr(matcherEnd, closingBracketIndex - matcherEnd - 1);

        if (escape)
        {
            string escapedExpression = in.substr(matcher.position(0) + 1, closingBracketIndex - matcher.position(0));
            if (xmlEscape)
                StringUtils::escapeHtml4(escapedExpression);
            ret.push_back(make_any<string>(escapedExpression));
        }
        else
        {
            ExpressionString expr{code};
            if (flag == "#")
                expr.setEscape(true);
            ret.push_back(make_any<ExpressionString>(expr));
        }
        start = closingBracketIndex;
        in = matcher.suffix();
    }
    string last = str.substr(start);
    if (xmlEscape)
        StringUtils::escapeHtml4(last);
    ret.push_back(make_any<string>(last));
}

string Utils::interpolate(vector<any> &prepared, PugModel &model, shared_ptr<IExpressionHandler> expressionHandler)
{
    ostringstream ret;

    for (auto entry : prepared)
    {
        if (string *val = any_cast<string>(&entry))
        {
            ret << *val;
        }
        else if (ExpressionString *val = any_cast<ExpressionString>(&entry))
        {
            string *stringValue = nullptr;
            string value = expressionHandler->evaluateStringExpression(val->getValue(), model);
            if (!value.empty())
                stringValue = &value;
            if (stringValue && !stringValue->empty())
            {
                if (val->isEscape())
                    StringUtils::escapeHtml4(*stringValue);
                ret << *stringValue;
            }
        }
    }

    return ret.str();
}

string Utils::interpolate(
    const string &str,
    PugModel &model,
    bool escape,
    shared_ptr<IExpressionHandler> expressionHandler)
{
    vector<any> prepared;

    prepareInterpolate(prepared, str, escape);

    return interpolate(prepared, model, expressionHandler);
}

} // namespace compiler
} // namespace pugcpp