#include "./Lexer.hpp"

namespace pugcpp
{
namespace lexer
{
const regex Lexer::m_rgCleanRe = regex("^['\"]|['\"]$");
const regex Lexer::m_rgDoubleQuotedRe = regex("^\"[^\"]*\"$");
const regex Lexer::m_rgQuotedRe = regex("^'[^']*'$");

Lexer::Lexer(const string &filename,
      shared_ptr<ITemplateLoader> templateLoader,
      shared_ptr<IExpressionHandler> expressionHandler)
{
}

Lexer::Lexer(const string &input,
      const string &filename,
      shared_ptr<ITemplateLoader> templateLoader,
      shared_ptr<IExpressionHandler> expressionHandler)
{
}

shared_ptr<Token> Lexer::next()
{
}

void vconsume(int len)
{
}

void Lexer::defer(shared_ptr<Token> tok)
{
}

shared_ptr<Token> Lexer::lookahead(int n)
{
}

} // namespace lexer
} // namespace pugcpp
