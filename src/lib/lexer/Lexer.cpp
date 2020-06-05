#include "Lexer.hpp"

namespace lexer
{
const regex Lexer::cleanRe = regex("^['\"]|['\"]$");
const regex Lexer::doubleQuotedRe = regex("^\"[^\"]*\"$");
const regex Lexer::quotedRe = regex("^'[^']*'$");
} // namespace lexer
