#include "Block.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
Block::Block(const string &value, int lineNumber) : Token::Token(value, lineNumber, e_Block)
{
}

Block::E_MODE Block::getMode() const
{
    return mode_;
}

void Block::setMode(const string &mode)
{
    string md = StringUtils::toLowerCase(mode);
    if (md == "append")
        mode_ = E_MODE::APPEND;
    else if(md == "prepend")
        mode_ = E_MODE::PREPEND;
    else
        mode_ = E_MODE::REPLACE;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp