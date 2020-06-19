
#include "Parser.hpp"

namespace pugcpp
{
namespace parser
{
const regex Parser::FILE_EXTENSION_PATTERN((".*\\.\\w+$"));

Parser::Parser(const string &filename,
               shared_ptr<tmpl::ITemplateLoader> templateLoader,
               shared_ptr<expression::IExpressionHandler> expressionHandler)
: m_sFilename(filename), m_pTemplateLoader(templateLoader), m_pExpressionHandler(expressionHandler)
{
    m_pLexer = make_unique<Lexer>(filename, templateLoader, expressionHandler);
}

Parser::Parser(const string &src,
               const string &filename,
               shared_ptr<tmpl::ITemplateLoader> templateLoader,
               shared_ptr<expression::IExpressionHandler> expressionHandler)
{
}

shared_ptr<Node> Parser::parse()
{
}

void Parser::setBlocks(shared_ptr<map<string, BlockNode>> blocks)
{
}

map<string, BlockNode> &Parser::getBlocks()
{
}

void Parser::setContexts(shared_ptr<list<Parser>> contexts)
{
}

shared_ptr<list<Parser>> Parser::getContexts()
{
}

void Parser::setMixins(shared_ptr<map<string, MixinNode>> mixins)
{
}

shared_ptr<Node> Parser::parseExpr()
{
}

shared_ptr<Node> Parser::parseBlockCode()
{
}

shared_ptr<Node> Parser::parseComment()
{
}

shared_ptr<Node> Parser::parseMixin()
{
}

shared_ptr<Node> Parser::parseCall()
{
}

shared_ptr<Node> Parser::parseCssClassOrId()
{
}

shared_ptr<Node> Parser::parseBlock()
{
}

shared_ptr<Node> Parser::parseMixinBlock()
{
}

shared_ptr<Node> Parser::parseInclude()
{
}

shared_ptr<Node> Parser::parseExtends()
{
}

shared_ptr<Node> Parser::parseInterpolation()
{
}

shared_ptr<Node> Parser::parseText()
{
}

shared_ptr<Node> Parser::parseEach()
{
}

shared_ptr<Node> Parser::parseWhile()
{
}

shared_ptr<Node> Parser::parseAssignment()
{
}

shared_ptr<Node> Parser::parseTag()
{
}

shared_ptr<Node> Parser::parseTextBlock()
{
}

shared_ptr<Node> Parser::parseConditional()
{
}

shared_ptr<Node> Parser::parseBlockExpansion()
{
}

shared_ptr<Node> Parser::parseCase()
{
}

shared_ptr<Node> Parser::parseWhen()
{
}

shared_ptr<Node> Parser::parseDefault()
{
}

shared_ptr<Node> Parser::parseCode()
{
}

shared_ptr<Node> Parser::parseDoctype()
{
}

shared_ptr<Node> Parser::parseFilter()
{
}

shared_ptr<Node> Parser::parseASTFilter()
{
}

shared_ptr<BlockNode> parseYield()
{
}

shared_ptr<Node> Parser::blockExpansion()
{
}

shared_ptr<BlockNode> Parser::block()
{
}

shared_ptr<list<CaseConditionNode>> Parser::whenBlock()
{
}

shared_ptr<Node> Parser::tag(shared_ptr<AttrsNode> tagNode)
{
}

shared_ptr<vector<Node>> Parser::parseInlineTagsInText(const string &str)
{
}

shared_ptr<CaseConditionNode> Parser::parseCaseCondition()
{
}

shared_ptr<list<Attr>> Parser::convertToNodeAttributes(AttributeList &attr)
{
}

shared_ptr<Token> Parser::lookahead(int i)
{
}

shared_ptr<Token> Parser::peek()
{
}

shared_ptr<Token> Parser::advance()
{
}

shared_ptr<Token> Parser::accept(/*clazz*/)
{
}

shared_ptr<Token> Parser::expect(/*exptectTokenClass*/)
{
}

shared_ptr<Parser> Parser::createParser(const string &templateName)
{
}

string Parser::ensurePugExtension(const string &templateName)
{
}

void Parser::skip(int n)
{
}

int Parser::line()
{
}
} // namespace parser
} // namespace pugcpp