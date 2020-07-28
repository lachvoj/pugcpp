#include "IndentWriter.hpp"

namespace pugcpp
{
namespace compiler
{
using namespace util;

IndentWriter::IndentWriter(ostringstream &writer) : writer_(writer)
{
}

void IndentWriter::add(const string &str)
{
    append(str);
}

void IndentWriter::append(const string &str)
{
    write(str);
}

void IndentWriter::write(const string &string)
{
    writer_ << string;
    empty_ = false;
}

void IndentWriter::increment()
{
    indent_++;
}

void IndentWriter::decrement()
{
    indent_--;
}

string IndentWriter::toString()
{
    return writer_.str();
}

void IndentWriter::newline()
{
    if (!isPp())
        return;

    write("\n" + StringUtils::repeat(pp_, indent_));
}

void IndentWriter::prettyIndent(int offset, bool newline)
{
    if (!isPp())
        return;

    string newlineChar = newline ? "\n" : "";
    write(newlineChar + StringUtils::repeat(pp_, indent_ + offset - 1));
}

void IndentWriter::setUseIndent(bool useIndent)
{
    useIndent_ = useIndent;
}

void IndentWriter::setEscape(bool escape)
{
    escape_ = escape;
}

bool IndentWriter::isEscape()
{
    return escape_;
}

bool IndentWriter::isPp()
{
    return (pp_.length() != 0 && useIndent_);
}

void IndentWriter::setCompiledTag(bool compiledTag)
{
    compiledTag_ = compiledTag;
}

bool IndentWriter::isCompiledTag()
{
    return compiledTag_;
}

void IndentWriter::setCompiledDoctype(bool compiledDoctype)
{
    compiledDoctype_ = compiledDoctype;
}

bool IndentWriter::isCompiledDoctype()
{
    return compiledDoctype_;
}
} // namespace compiler
} // namespace pugcpp
