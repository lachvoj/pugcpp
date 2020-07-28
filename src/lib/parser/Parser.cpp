
#include "./Parser.hpp"

namespace pugcpp
{
namespace parser
{
const regex Parser::FILE_EXTENSION_PATTERN((".*\\.\\w+$"));

Parser::Parser(
    const string &filename,
    shared_ptr<tmpl::ITemplateLoader> templateLoader,
    shared_ptr<expression::IExpressionHandler> expressionHandler)
: fileName_(filename), templateLoader_(templateLoader), expressionHandler_(expressionHandler),
  lexer_(filename, templateLoader, expressionHandler)
{
}

Parser::Parser(
    const string &src,
    const string &filename,
    shared_ptr<tmpl::ITemplateLoader> templateLoader,
    shared_ptr<expression::IExpressionHandler> expressionHandler)
: fileName_(filename), templateLoader_(templateLoader), expressionHandler_(expressionHandler),
  lexer_(src, filename, templateLoader, expressionHandler)
{
}

shared_ptr<Node> Parser::parse()
{
    shared_ptr<BlockNode> block = make_shared<BlockNode>();

    block->setLineNumber(line());
    block->setFileName(fileName_);

    while (peek()->getType() != e_Eos)
    {
        if (peek()->getType() == e_Newline)
        {
            advance();
        }
        else
        {
            shared_ptr<Node> expr;
            parseExpr(expr);
            if (expr)
                block->push(expr);
        }
    }
    if (!extending_)
        return block;

    getContexts().push(extending_);
    shared_ptr<Node> rootNode = extending_->parse();
    getContexts().pop();

    // hoist mixins
    for (map<string, shared_ptr<MixinNode>>::iterator it = mixins_.begin(); it != mixins_.end(); ++it)
    {
        rootNode->getNodes().push_back(it->second);
    }

    return rootNode;
}

void Parser::setBlocks(const map<string, shared_ptr<BlockNode>> &blocks)
{
    blocks_ = blocks;
}

map<string, shared_ptr<BlockNode>> &Parser::getBlocks()
{
    return blocks_;
}

void Parser::setContexts(const stack<shared_ptr<Parser>> &contexts)
{
    contexts_ = contexts;
}

stack<shared_ptr<Parser>> &Parser::getContexts()
{
    return contexts_;
}

void Parser::setMixins(const map<string, shared_ptr<MixinNode>> &mixins)
{
    mixins_ = mixins;
}

void Parser::parseExpr(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok = peek();

    switch (tok->getType())
    {
    case e_Tag: parseTag(ret); break;
    case e_Mixin: parseMixin(ret); break;
    case e_Block: parseBlock(ret); break;
    case e_MixinBlock: parseMixinBlock(ret); break;
    case e_CaseToken: parseCase(ret); break;
    case e_ExtendsToken: parseExtends(ret); break;
    case e_Include: parseInclude(ret); break;
    case e_Doctype: parseDoctype(ret); break;
    case e_Filter: parseFilter(ret); break;
    case e_Comment: parseComment(ret); break;
    case e_Text: parseText(ret); break;
    case e_Each: parseEach(ret); break;
    case e_Expression: parseCode(ret); break;
    case e_BlockCode: parseBlockCode(ret); break;
    case e_Call: parseCall(ret); break;
    case e_Interpolation: parseInterpolation(ret); break;
    case e_Yield: parseYield(ret); break;
    case e_CssClass:
    case e_CssId: parseCssClassOrId(ret); break;
    case e_While: parseWhile(ret); break;
    case e_If: parseConditional(ret); break;

    default: throw PugParserException(fileName_, line(), templateLoader_, *tok); break;
    }
}

void Parser::parseBlockCode(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok = expect(TokenType::e_BlockCode);
    shared_ptr<Token> body = peek();
    string text = "";
    if (body->getType() == e_PipelessText)
    {
        advance();
        text = StringUtils::join(body->getValues(), "\n");
    }
    shared_ptr<ExpressionNode> nd = make_shared<ExpressionNode>();
    nd->setValue(text);
    nd->setLineNumber(tok->getLineNumber());
    ret = nd;
}

void Parser::parseComment(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok = expect(TokenType::e_Comment);
    shared_ptr<Node> block;

    parseTextBlock(block);
    if (block)
    {
        shared_ptr<BlockCommentNode> nd = make_shared<BlockCommentNode>();
        nd->setBlock(block);
        nd->setBuffered(tok->isBuffer());
        nd->setLineNumber(tok->getLineNumber());
        nd->setFileName(fileName_);
        nd->setValue(tok->getValue());
        ret = nd;
    }
    else
    {
        shared_ptr<CommentNode> nd = make_shared<CommentNode>();
        nd->setBuffered(tok->isBuffer());
        nd->setLineNumber(tok->getLineNumber());
        nd->setFileName(fileName_);
        nd->setValue(tok->getValue());
        ret = nd;
    }
}

void Parser::parseMixin(shared_ptr<Node> &ret)
{
}

void Parser::parseCall(shared_ptr<Node> &ret)
{
}

void Parser::parseCssClassOrId(shared_ptr<Node> &ret)
{
    lexer_.defer(make_shared<Tag>("div", line()));
    lexer_.defer(advance());
    parseExpr(ret);
}

void Parser::parseBlock(shared_ptr<Node> &ret)
{
}

void Parser::parseMixinBlock(shared_ptr<Node> &ret)
{
}

void Parser::parseInclude(shared_ptr<Node> &ret)
{
}

void Parser::parseExtends(shared_ptr<Node> &ret)
{
}

void Parser::parseInterpolation(shared_ptr<Node> &ret)
{
}

void Parser::parseText(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok = expect(e_Text);
    vector<shared_ptr<Node>> tokens;

    parseInlineTagsInText(tokens, tok->getValue());
    if (tokens.size() == 1)
    {
        ret = tokens[0];
        return;
    }
    shared_ptr<BlockNode> nd = make_shared<BlockNode>();
    for (auto token : tokens)
    {
        nd->push(token);
    }
    nd->setValue(tok->getValue());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
    ret = nd;
}

void Parser::parseEach(shared_ptr<Node> &ret)
{
}

void Parser::parseWhile(shared_ptr<Node> &ret)
{
}

void Parser::parseAssignment(shared_ptr<Node> &ret)
{
}

void Parser::parseTag(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok = advance();
    string name = tok->getValue();
    shared_ptr<TagNode> nd = make_shared<TagNode>();
    nd->setLineNumber(line());
    nd->setFileName(fileName_);
    nd->setName(name);
    nd->setValue(name);
    nd->setSelfClosing(tok->isSelfClosing());
    shared_ptr<AttrsNode> attrsNode = static_pointer_cast<AttrsNode>(nd);
    tag(attrsNode);
    ret = nd;
}

void Parser::tag(shared_ptr<AttrsNode> &tagNode)
{
    bool seenAttrs = false;
    bool isTagToken = true;
    while (isTagToken)
    {
        switch (peek()->getType())
        {
        case e_CssId: tagNode->setAttribute("id", advance()->getValue(), false); break;
        case e_CssClass: tagNode->setAttribute("class", advance()->getValue(), false); break;
        case e_AttributeList:
        {
            if (seenAttrs)
            {
                throw PugParserException(
                    fileName_,
                    line(),
                    templateLoader_,
                    fileName_ + ", line " + to_string(peek()->getLineNumber()) +
                        ":\nYou should not have jade tags with multiple attributes.");
            }
            seenAttrs = true;
            shared_ptr<AttributeList> tok = static_pointer_cast<AttributeList>(advance());
            const vector<Attribute> &attrs = tok->getAttributes();
            tagNode->setSelfClosing(tok->isSelfClosing());

            for (Attribute attr : attrs)
            {
                tagNode->setAttribute(attr.getName(), attr.getValue(), attr.isEscaped());
            }
        }
        break;
        case e_AttributesBlock: tagNode->addAttributes(advance()->getValue()); break;

        default: isTagToken = false; break;
        }
    }

    // check immediate '.'
    bool dot = false;
    if (peek()->getType() == e_Dot)
    {
        dot = true;
        tagNode->setTextOnly(true);
        advance();
    }

    // (text | code | ':')?
    switch (peek()->getType())
    {
    case e_Text:
    {
        shared_ptr<Node> text;
        parseText(text);
        tagNode->getBlock()->push(text);
    }
    break;
    case e_Expression:
    {
        shared_ptr<Node> code;
        parseCode(code);
        tagNode->setCodeNode(code);
    }
    break;
    case e_Colon:
    {
        shared_ptr<BlockNode> block = make_shared<BlockNode>();
        block->setLineNumber(advance()->getLineNumber());
        block->setFileName(fileName_);
        shared_ptr<Node> expr;
        parseExpr(expr);
        block->push(expr);
        tagNode->setBlock(block);
    }
    break;
    default: break;
    }

    // newline*
    while (peek()->getType() == e_Newline)
    {
        advance();
    }
    if (tagNode->isTextOnly())
    {
        shared_ptr<Node> bl;
        parseTextBlock(bl);
        if (!bl)
            bl = static_pointer_cast<Node>(make_shared<BlockNode>());
        tagNode->setBlock(bl);
    }
    else if (peek()->getType() == e_Indent)
    {
        shared_ptr<BlockNode> bl;
        block(bl);
        for (auto nd : bl->getNodes())
        {
            tagNode->getBlock()->push(nd);
        }
    }
}

void Parser::parseTextBlock(shared_ptr<Node> &ret)
{
    shared_ptr<Token> body = peek();
    if (body->getType() != TokenType::e_PipelessText)
    {
        return;
    }

    shared_ptr<BlockNode> nd = make_shared<BlockNode>();
    nd->setLineNumber(line());
    nd->setFileName(&fileName_);
    advance();
    const vector<string> &values = body->getValues();
    vector<shared_ptr<Node>> &textNodes = nd->getNodes();
    for (const string &value : values)
    {
        parseInlineTagsInText(textNodes, value);
    }

    ret = nd;
}

void Parser::parseConditional(shared_ptr<Node> &ret)
{
}

void Parser::parseBlockExpansion(shared_ptr<Node> &ret)
{
}

void Parser::parseCase(shared_ptr<Node> &ret)
{
}

void Parser::parseWhen(shared_ptr<Node> &ret)
{
}

void Parser::parseDefault(shared_ptr<Node> &ret)
{
}

void Parser::parseCode(shared_ptr<Node> &ret)
{
    shared_ptr<Expression> tok = static_pointer_cast<Expression>(expect(e_Expression));
    shared_ptr<ExpressionNode> nd = make_shared<ExpressionNode>();
    nd->setValue(tok->getValue());
    nd->setBuffer(tok->isBuffer());
    nd->setEscape(tok->isEscape());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
    if (peek()->getType() == e_Indent)
    {
        shared_ptr<BlockNode> bl;
        block(bl);
        nd->setBlock(bl);
    }
    ret = nd;
}

void Parser::parseDoctype(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok = expect(TokenType::e_Doctype);
    shared_ptr<DoctypeNode> nd = make_shared<DoctypeNode>();
    nd->setValue(tok->getValue());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
    ret = nd;
}

void Parser::parseFilter(shared_ptr<Node> &ret)
{
}

void Parser::parseASTFilter(shared_ptr<Node> &ret)
{
}

void Parser::parseYield(shared_ptr<Node> &ret)
{
}

shared_ptr<Node> Parser::blockExpansion()
{
}

void Parser::block(shared_ptr<BlockNode> &ret)
{
    ret = make_shared<BlockNode>();
    ret->setLineNumber(line());
    ret->setFileName(fileName_);
    expect(e_Indent);
    while (peek()->getType() != e_Outdent)
    {
        if (peek()->getType() == e_Newline)
        {
            advance();
        }
        else
        {
            shared_ptr<Node> pe;
            parseExpr(pe);
            if (pe)
            {
                pe->setFileName(fileName_);
                ret->push(pe);
            }
        }
    }
    expect(e_Outdent);
}

shared_ptr<list<shared_ptr<CaseConditionNode>>> Parser::whenBlock()
{
}

void Parser::parseInlineTagsInText(vector<shared_ptr<Node>> &ret, const string &str)
{
    int ln = line();
    smatch matcher;
    regex_search(str, matcher, regex("(\\\\)?#\\[((?:.|\\n)*)$"));
    shared_ptr<TextNode> text = make_shared<TextNode>();
    text->setLineNumber(ln);
    text->setFileName(fileName_);
    if (!matcher.empty() && matcher.size() > 2)
    {
        if (matcher[1].matched) // escape
        {
            text->setValue(str.substr(0, matcher.position(0)) + "#[");
            vector<shared_ptr<Node>> rest;
            parseInlineTagsInText(rest, matcher.str(2));
            if (rest.front()->getType() == e_TextNode)
            {
                text->setValue(text->getValue() + rest.front()->getValue());
                rest.erase(rest.begin());
            }
            ret.reserve(rest.size() + 1);
            ret.push_back(text);
            ret.insert(ret.end(), rest.begin(), rest.end());
        }
        else
        {
            text->setValue(str.substr(0, matcher.position(0)));
            string rest = matcher.str(2);
            shared_ptr<CharacterParser::Match> range;
            try
            {
                range = characterParser_.parseMax(rest);
            }
            catch (CharacterParser::SyntaxError &e)
            {
                throw PugParserException(fileName_, ln, templateLoader_, " See " + matcher.str(0));
            }
            unique_ptr<Parser> inner;
            try
            {
                inner = make_unique<Parser>(range->getSrc(), fileName_, templateLoader_, expressionHandler_);
            }
            catch (exception &e)
            {
                throw PugParserException(fileName_, ln, templateLoader_, "Could not parse text");
            }
            vector<shared_ptr<Node>> inlineTags;
            parseInlineTagsInText(inlineTags, rest.substr(range->getEnd() + 1));
            size_t reserve = 1 + inlineTags.size();
            shared_ptr<Node> nd = inner->parse();
            if (nd)
                ++reserve;
            ret.reserve(reserve);
            ret.push_back(text);
            if (nd)
                ret.push_back(nd);
            ret.insert(ret.end(), inlineTags.begin(), inlineTags.end());
        }
    }
    else
    {
        text->setValue(str);
        ret.push_back(text);
    }
}

shared_ptr<CaseConditionNode> Parser::parseCaseCondition()
{
}

shared_ptr<list<Attr>> Parser::convertToNodeAttributes(AttributeList &attr)
{
}

shared_ptr<Token> Parser::lookahead(int i)
{
    return lexer_.lookahead(i);
}

shared_ptr<Token> Parser::peek()
{
    return lookahead(1);
}

shared_ptr<Token> Parser::advance()
{
    return lexer_.advance();
}

shared_ptr<Token> Parser::accept(/*clazz*/)
{
}

shared_ptr<Token> Parser::expect(TokenType tokenType)
{
    shared_ptr<Token> tok = peek();

    if (tok->getType() == tokenType)
        return advance();

    throw PugParserException(fileName_, line(), templateLoader_, tokenType, tok->getType());
}

shared_ptr<Parser> Parser::createParser(const string &templateName)
{
}

string Parser::ensurePugExtension(const string &templateName)
{
}

int Parser::line()
{
    return lexer_.getLineno();
}
} // namespace parser
} // namespace pugcpp