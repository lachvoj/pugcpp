#include "IndentWriter.hpp"

#include "../util/StringUtils.hpp"

namespace compiler
{

IndentWriter::IndentWriter(shared_ptr<stringstream> writer) : m_pWriter(writer)
{
}

IndentWriter &IndentWriter::add(const string &str)
{
    return append(str);
}

IndentWriter &IndentWriter::append(const string &str)
{
    write(str);

    return *this;
}

void IndentWriter::write(const string &string)
{
    (*m_pWriter) << string;
    m_bEmpty = false;
}

void IndentWriter::increment()
{
    m_nIndent++;
}

void IndentWriter::decrement()
{
    m_nIndent--;
}

string IndentWriter::toString()
{
    return m_pWriter->str();
}

void IndentWriter::newline()
{
    if (!isPp())
        return;

    write("\n" + util::StringUtils::repeat(m_sPp, m_nIndent));
}

void IndentWriter::prettyIndent(int offset, bool newline)
{
    if (!isPp())
        return;

    string newlineChar = newline ? "\n" : "";
    write(newlineChar + util::StringUtils::repeat(m_sPp, m_nIndent + offset - 1));
}

void IndentWriter::setUseIndent(bool useIndent)
{
    m_bUseIndent = useIndent;
}

void IndentWriter::setEscape(bool escape)
{
    m_bEscape = escape;
}

bool IndentWriter::isEscape()
{
    return m_bEscape;
}

bool IndentWriter::isPp()
{
    return (m_sPp.length() != 0 && m_bUseIndent);
}

void IndentWriter::setCompiledTag(bool compiledTag)
{
    m_bCompiledTag = compiledTag;
}

bool IndentWriter::isCompiledTag()
{
    return m_bCompiledTag;
}

void IndentWriter::setCompiledDoctype(bool compiledDoctype)
{
    m_bCompiledDoctype = compiledDoctype;
}

bool IndentWriter::isCompiledDoctype()
{
    return m_bCompiledDoctype;
}
} // namespace compiler
