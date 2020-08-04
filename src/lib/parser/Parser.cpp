
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
  lexer_(ensurePugExtension(filename, templateLoader->getExtension()), templateLoader, expressionHandler)
{
}

Parser::Parser(
    const string &src,
    const string &filename,
    shared_ptr<tmpl::ITemplateLoader> templateLoader,
    shared_ptr<expression::IExpressionHandler> expressionHandler)
: fileName_(filename), templateLoader_(templateLoader), expressionHandler_(expressionHandler),
  lexer_(src, ensurePugExtension(filename, templateLoader->getExtension()), templateLoader, expressionHandler)
{
}

shared_ptr<Node> Parser::parse()
{
    shared_ptr<BlockNode> block = make_shared<BlockNode>();

    block->setLineNumber(line());
    block->setFileName(fileName_);

    while (peekType() != e_Eos)
    {
        if (peekType() == e_Newline)
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
    switch (peekType())
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
    case e_Assignment: parseAssignment(ret); break;
    default: throw PugParserException(fileName_, line(), templateLoader_, *(peek())); break;
    }
}

void Parser::parseBlockCode(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok;
    expect(tok, TokenType::e_BlockCode);
    shared_ptr<Token> &body = peek();
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
    shared_ptr<Token> tok;
    expect(tok, TokenType::e_Comment);
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
    shared_ptr<Mixin> tok;
    expect(tok, e_Mixin);
    shared_ptr<MixinNode> nd = make_shared<MixinNode>();
    nd->setName(tok->getValue());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
}

void Parser::parseCall(shared_ptr<Node> &ret)
{
    shared_ptr<Call> tok;
    expect(tok, e_Call);
    shared_ptr<MixinNode> mixin = make_shared<MixinNode>();
    mixin->setBlock(make_shared<BlockNode>());
    mixin->setName(tok->getValue());
    mixin->setLineNumber(tok->getLineNumber());
    mixin->setFileName(fileName_);
    mixin->setCall(true);

    if (StringUtils::isNotBlank(tok->getArguments()))
        mixin->setArguments(tok->getArguments());

    shared_ptr<AttrsNode> atn = static_pointer_cast<AttrsNode>(mixin);
    shared_ptr<Node> emptyNode;
    tag(atn);
    if (mixin->hasCodeNode())
    {
        mixin->getBlock()->push(mixin->getCodeNode());
        mixin->setCodeNode(emptyNode);
    }
    if (mixin->hasBlock() && mixin->getBlock()->getNodes().empty())
        mixin->setBlock(emptyNode);

    ret = mixin;
}

void Parser::parseCssClassOrId(shared_ptr<Node> &ret)
{
    lexer_.defer(make_shared<Tag>("div", line()));
    shared_ptr<Token> tok;
    advance(tok);
    lexer_.defer(tok);
    parseExpr(ret);
}

void Parser::parseBlock(shared_ptr<Node> &ret)
{
    shared_ptr<Block> tok;
    expect(tok, e_Block);
    Block::E_MODE mode = tok->getMode();
    const string &name = tok->getName();

    inBlock_++;
    shared_ptr<BlockNode> bn;
    if (peekType() == e_Indent)
        block(bn);
    else
    {
        bn = make_shared<BlockNode>();
        bn->setLineNumber(tok->getLineNumber());
        bn->setFileName(fileName_);
        shared_ptr<LiteralNode> nd = make_shared<LiteralNode>();
        bn->push(nd);
    }
    inBlock_--;
    bn->setName(name);
    bn->setLineNumber(line());

    shared_ptr<BlockNode> prevBn;
    if (blocks_.find(name) != blocks_.end())
        prevBn = blocks_[name];
    else
        prevBn = make_shared<BlockNode>();

    if (prevBn->getMode() == Block::E_MODE::REPLACE)
    {
        blocks_[name] = prevBn;
        ret = prevBn;
        return;
    }

    vector<shared_ptr<Node>> allNodes;
    vector<shared_ptr<Node>> &prepended = prevBn->getPrepended();
    vector<shared_ptr<Node>> &nds = bn->getNodes();
    vector<shared_ptr<Node>> &appended = prevBn->getAppended();
    allNodes.reserve(prepended.size() + nds.size() + appended.size());
    allNodes.insert(allNodes.end(), prepended.begin(), prepended.end());
    allNodes.insert(allNodes.end(), nds.begin(), nds.end());
    allNodes.insert(allNodes.end(), appended.begin(), appended.end());

    if (mode == Block::E_MODE::APPEND)
    {
        vector<shared_ptr<Node>> appendedNodes;
        vector<shared_ptr<Node>> &apnd = prevBn->getAppended();
        appendedNodes.reserve(apnd.size() + nds.size());
        if (prevBn->getParser() == this)
        {
            appendedNodes.insert(appendedNodes.end(), apnd.begin(), apnd.end());
            appendedNodes.insert(appendedNodes.end(), nds.begin(), nds.end());
        }
        else
        {
            appendedNodes.insert(appendedNodes.end(), nds.begin(), nds.end());
            appendedNodes.insert(appendedNodes.end(), apnd.begin(), apnd.end());
        }
        prevBn->setAppended(appendedNodes);
    }
    else if (mode == Block::E_MODE::PREPEND)
    {
        vector<shared_ptr<Node>> prependedNodes;
        vector<shared_ptr<Node>> &prpnd = prevBn->getPrepended();
        prependedNodes.reserve(prpnd.size() + nds.size());
        if (prevBn->getParser() == this)
        {
            prependedNodes.insert(prependedNodes.end(), nds.begin(), nds.end());
            prependedNodes.insert(prependedNodes.end(), prpnd.begin(), prpnd.end());
        }
        else
        {
            prependedNodes.insert(prependedNodes.end(), prpnd.begin(), prpnd.end());
            prependedNodes.insert(prependedNodes.end(), nds.begin(), nds.end());
        }
        prevBn->setPrepended(prependedNodes);
    }

    bn->setNodes(allNodes);
    bn->setAppended(prevBn->getAppended());
    bn->setPrepended(prevBn->getPrepended());
    bn->setMode(mode);
    bn->setSubBlock((inBlock_ > 0));

    blocks_[name] = bn;
    ret = bn;
}

void Parser::parseMixinBlock(shared_ptr<Node> &ret)
{
    expect(e_MixinBlock);
    if (inMixin_ == 0)
        throw PugParserException(
            fileName_, line(), templateLoader_, "Anonymous blocks are not allowed unless they are part of a mixin.");
    ret = make_shared<MixinBlockNode>();
}

void Parser::parseInclude(shared_ptr<Node> &ret)
{
    shared_ptr<Include> tok;
    expect(tok, e_Include);
    string templateName = StringUtils::trim(tok->getValue());
    string path = PathHelper::resolvePath(fileName_, templateName, templateLoader_->getExtension());

    if (!tok->getFilter().empty())
    {
        try
        {
            unique_ptr<istream> reader = templateLoader_->getReader(path);
            shared_ptr<FilterNode> nd = make_shared<FilterNode>();
            nd->setValue(tok->getFilter());
            nd->setLineNumber(line());
            nd->setFileName(fileName_);
            shared_ptr<TextNode> text = make_shared<TextNode>();
            text->setValue(string(istreambuf_iterator<char>(*reader), {}));
            shared_ptr<BlockNode> bl = make_shared<BlockNode>();
            bl->getNodes().push_back(text);
            shared_ptr<Node> bln = static_pointer_cast<Node>(bl);
            nd->setTextBlock(bln);
            ret = nd;
            return;
        }
        catch (std::exception &e)
        {
            throw PugParserException(
                fileName_,
                line(),
                templateLoader_,
                "the included file [" + templateName + "] could not be opened\n" + string(e.what()));
        }
    }

    // non-pug
    string extension = FileSystem::getExtension(path);
    if (templateLoader_->getExtension() != extension)
    {
        try
        {
            unique_ptr<istream> reader = templateLoader_->getReader(path);
            shared_ptr<LiteralNode> nd = make_shared<LiteralNode>();
            nd->setLineNumber(line());
            nd->setFileName(fileName_);
            nd->setValue(string(istreambuf_iterator<char>(*reader), {}));
            ret = nd;
            return;
        }
        catch (std::exception &e)
        {
            throw PugParserException(
                fileName_,
                line(),
                templateLoader_,
                "the included file [" + templateName + "] could not be opened\n" + string(e.what()));
        }
    }

    shared_ptr<Parser> prs = createParser(templateName);
    prs->setBlocks(blocks_); // TODO: check if hardcopy of content is required
    prs->setMixins(mixins_);
    contexts_.push(prs);
    shared_ptr<Node> ast = prs->parse();
    contexts_.pop();
    if (ast)
    {
        ast->setFileName(path);
        if (peekType() == e_Indent)
        {
            shared_ptr<BlockNode> blnd;
            block(blnd);
            static_pointer_cast<BlockNode>(ast)->getIncludeBlock().push(blnd);
        }
        ret = ast;
    }
}

void Parser::parseExtends(shared_ptr<Node> &ret)
{
    shared_ptr<ExtendsToken> tok;
    expect(tok, e_ExtendsToken);
    string templateName = StringUtils::trim(tok->getValue());

    shared_ptr<Parser> prs = createParser(templateName);
    prs->setBlocks(blocks_);
    prs->setContexts(contexts_);
    extending_ = prs;

    ret = make_shared<LiteralNode>();
}

void Parser::parseInterpolation(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok;
    advance(tok);
    shared_ptr<TagNode> nd = make_shared<TagNode>();
    nd->setLineNumber(line());
    nd->setFileName(fileName_);
    nd->setName(tok->getValue());
    nd->setBuffer(true);
    shared_ptr<AttrsNode> atn = static_pointer_cast<AttrsNode>(nd);
    tag(atn);
    ret = nd;
}

void Parser::parseText(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok;
    expect(tok, e_Text);
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
    shared_ptr<Each> tok;
    expect(tok, e_Each);
    shared_ptr<EachNode> nd = make_shared<EachNode>();
    nd->setValue(tok->getValue());
    nd->setKey(tok->getKey());
    nd->setCode(tok->getCode());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
    shared_ptr<BlockNode> bn;
    block(bn);
    nd->setBlock(bn);
    if (peekType() == e_Else)
    {
        advance();
        block(bn);
        shared_ptr<Node> cbn = static_pointer_cast<Node>(bn);
        nd->setElseNode(cbn);
    }
    ret = nd;
}

void Parser::parseWhile(shared_ptr<Node> &ret)
{
    shared_ptr<While> tok;
    expect(tok, e_While);
    shared_ptr<WhileNode> nd = make_shared<WhileNode>();
    nd->setValue(tok->getValue());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
    shared_ptr<BlockNode> bn;
    block(bn);
    if (!bn)
    {
        bn = make_shared<BlockNode>();
    }
    nd->setBlock(bn);
    ret = nd;
}

void Parser::parseAssignment(shared_ptr<Node> &ret)
{
    shared_ptr<Assignment> tok;
    expect(tok, e_Assignment);
    shared_ptr<Node> nd = make_shared<AssigmentNode>();
    nd->setName(tok->getName());
    nd->setValue(tok->getValue());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
    ret = nd;
}

void Parser::parseTag(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok;
    advance(tok);
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
        switch (peekType())
        {
        case e_CssId:
        {
            shared_ptr<Token> tok;
            advance(tok);
            tagNode->setAttribute("id", tok->getValue(), false);
        }
        break;
        case e_CssClass:
        {

            shared_ptr<Token> tok;
            advance(tok);
            tagNode->setAttribute("class", tok->getValue(), false);
        }
        break;
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
            shared_ptr<AttributeList> tok;
            advance(tok);
            const vector<Attribute> &attrs = tok->getAttributes();
            tagNode->setSelfClosing(tok->isSelfClosing());

            for (Attribute attr : attrs)
            {
                tagNode->setAttribute(attr.getName(), attr.getValue(), attr.isEscaped());
            }
        }
        break;
        case e_AttributesBlock:
        {

            shared_ptr<Token> tok;
            advance(tok);
            tagNode->addAttributes(tok->getValue());
        }
        break;

        default: isTagToken = false; break;
        }
    }

    // check immediate '.'
    if (peekType() == e_Dot)
    {
        tagNode->setTextOnly(true);
        advance();
    }

    // (text | code | ':')?
    switch (peekType())
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
        shared_ptr<Token> tok;
        advance(tok);
        block->setLineNumber(tok->getLineNumber());
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
    while (peekType() == e_Newline)
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
    else if (peekType() == e_Indent)
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
    shared_ptr<If> tok;
    expect(tok, e_If);
    shared_ptr<ConditionalNode> nd = make_shared<ConditionalNode>();
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);

    vector<shared_ptr<IfConditionNode>> &conditions = nd->getConditions();
    shared_ptr<IfConditionNode> main = make_shared<IfConditionNode>(tok->getValue(), tok->getLineNumber());
    main->setInverse(tok->isInverseCondition());
    shared_ptr<BlockNode> bn;
    block(bn);
    main->setBlock(bn);
    conditions.push_back(main);

    while (peekType() == e_ElseIf)
    {
        shared_ptr<ElseIf> elifTok;
        expect(elifTok, e_ElseIf);
        shared_ptr<IfConditionNode> elifNd =
            make_shared<IfConditionNode>(elifTok->getValue(), elifTok->getLineNumber());
        block(bn);
        elifNd->setBlock(bn);
        conditions.push_back(elifNd);
    }

    if (peekType() == e_Else)
    {
        shared_ptr<ElseIf> elTok;
        expect(elTok, e_ElseIf);
        shared_ptr<IfConditionNode> elNd = make_shared<IfConditionNode>("", elTok->getLineNumber());
        elNd->setDefault(true);
        block(bn);
        elNd->setBlock(bn);
        conditions.push_back(elNd);
    }
    ret = nd;
}

void Parser::parseBlockExpansion(shared_ptr<Node> &ret)
{
    shared_ptr<BlockNode> bn;
    if (peekType() != e_Colon)
    {
        block(bn);
        ret = bn;
        return;
    }
    advance();
    bn = make_shared<BlockNode>();
    shared_ptr<Node> nd;
    parseExpr(nd);
    bn->push(nd);
    ret = bn;
}

void Parser::parseCase(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok;
    expect(tok, e_CaseToken);
    const string &val = tok->getValue();
    shared_ptr<Node> nd = make_shared<CaseNode>();
    nd->setValue(val);
    nd->setLineNumber(line());

    shared_ptr<BlockNode> bl = make_shared<BlockNode>();
    bl->setLineNumber(line());
    bl->setFileName(fileName_);
    expect(e_Indent);
    while (peekType() != e_Outdent)
    {
        switch (peekType())
        {
        case e_Comment:
        case e_Newline: advance(); break;
        case e_When:
        {
            shared_ptr<Node> when;
            parseWhen(when);
            bl->push(when);
        }
        break;
        case e_Default:
        {
            shared_ptr<Node> dflt;
            parseDefault(dflt);
            bl->push(dflt);
        }
        break;
        default:
            throw PugParserException(
                fileName_,
                line(),
                templateLoader_,
                "Unexpected token \"" + Token::getTypeNameFromTokenType(peekType()) +
                    "\", expected \"when\", \"default\" or \"newline\"");
        }
    }
    expect(e_Outdent);
    nd->setBlock(bl);
    ret = nd;
}

void Parser::parseWhen(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok;
    expect(tok, e_CaseToken);
    const string &val = tok->getValue();
    shared_ptr<CaseNode::When> nd = make_shared<CaseNode::When>();
    nd->setValue(val);
    if (peekType() != e_Newline)
    {
        shared_ptr<Node> ble;
        parseBlockExpansion(ble);
        nd->setBlock(ble);
    }
    ret = nd;
}

void Parser::parseDefault(shared_ptr<Node> &ret)
{
    expect(TokenType::e_Default);
    shared_ptr<CaseNode::When> nd = make_shared<CaseNode::When>();
    nd->setValue("default");
    shared_ptr<Node> ble;
    parseBlockExpansion(ble);
    nd->setBlock(ble);
    ret = nd;
}

void Parser::parseCode(shared_ptr<Node> &ret)
{
    shared_ptr<Expression> tok;
    expect(tok, e_Expression);
    shared_ptr<ExpressionNode> nd = make_shared<ExpressionNode>();
    nd->setValue(tok->getValue());
    nd->setBuffer(tok->isBuffer());
    nd->setEscape(tok->isEscape());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
    if (peekType() == e_Indent)
    {
        shared_ptr<BlockNode> bl;
        block(bl);
        nd->setBlock(bl);
    }
    ret = nd;
}

void Parser::parseDoctype(shared_ptr<Node> &ret)
{
    shared_ptr<Token> tok;
    expect(tok, TokenType::e_Doctype);
    shared_ptr<DoctypeNode> nd = make_shared<DoctypeNode>();
    nd->setValue(tok->getValue());
    nd->setLineNumber(tok->getLineNumber());
    nd->setFileName(fileName_);
    ret = nd;
}

void Parser::parseFilter(shared_ptr<Node> &ret)
{
    shared_ptr<Filter> tok;
    expect(tok, e_Filter);
    shared_ptr<AttributeList> attr;
    accept(attr, e_AttributeList);
    lexer_.setPipeless(true);
    shared_ptr<Node> tNd;
    parseTextBlock(tNd);
    lexer_.setPipeless(false);

    shared_ptr<FilterNode> nd;
    nd->setValue(tok->getValue());
    nd->setLineNumber(line());
    nd->setFileName(fileName_);
    if (tNd)
        nd->setTextBlock(tNd);
    else
    {
        shared_ptr<Node> bNd = static_pointer_cast<Node>(make_shared<BlockNode>());
        nd->setTextBlock(bNd);
    }
    if (attr)
        convertToNodeAttributes(nd->getAttributes(), *attr);

    ret = nd;
}

void Parser::parseASTFilter(shared_ptr<Node> &ret)
{
    shared_ptr<Filter> tok;
    expect(tok, e_Filter);
    shared_ptr<AttributeList> attr;
    accept(attr, e_AttributeList);
    expect(e_Colon);

    shared_ptr<FilterNode> nd = make_shared<FilterNode>();
    shared_ptr<BlockNode> bn;
    block(bn);
    nd->setBlock(bn);
    nd->setValue(tok->getValue());
    nd->setLineNumber(line());
    nd->setFileName(fileName_);
    convertToNodeAttributes(nd->getAttributes(), *attr);
}

void Parser::parseYield(shared_ptr<Node> &ret)
{
    advance();
    shared_ptr<BlockNode> nd = make_shared<BlockNode>();
    nd->setLineNumber(line());
    nd->setFileName(fileName_);
    nd->setYield(true);
    ret = nd;
}

// shared_ptr<Node> Parser::blockExpansion()
// {
// }

void Parser::block(shared_ptr<BlockNode> &ret)
{
    ret = make_shared<BlockNode>();
    ret->setLineNumber(line());
    ret->setFileName(fileName_);
    expect(e_Indent);
    while (peekType() != e_Outdent)
    {
        if (peekType() == e_Newline)
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

// shared_ptr<list<shared_ptr<CaseConditionNode>>> Parser::whenBlock()
// {
// }

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

// shared_ptr<CaseConditionNode> Parser::parseCaseCondition()
// {
// }

void Parser::convertToNodeAttributes(vector<Attr> &ret, AttributeList &attr)
{
    const vector<Attribute> &attributes = attr.getAttributes();
    ret.reserve(attributes.size());
    for (auto &attribute : attributes)
    {
        ret.push_back(Attr(attribute.getName(), attribute.getValue(), attribute.isEscaped()));
    }
}

shared_ptr<Token> &Parser::lookahead(int i)
{
    return lexer_.lookahead(i);
}

shared_ptr<Token> &Parser::peek()
{
    return lexer_.lookahead(1);
}

TokenType Parser::peekType()
{
    return lexer_.lookahead(1)->getType();
}

template <typename T>
void Parser::advance(shared_ptr<T> &ret)
{
    lexer_.advance((shared_ptr<Token> &)ret);
}

void Parser::advance()
{
    shared_ptr<Token> tok;
    lexer_.advance(tok);
}

int Parser::line()
{
    return lexer_.getLineno();
}

shared_ptr<Parser> Parser::createParser(const string &templateName)
{
    string tn = ensurePugExtension(templateName, templateLoader_->getExtension());
    try
    {
        string resolvedPath = PathHelper::resolvePath(fileName_, templateName, templateLoader_->getExtension());
        return make_shared<Parser>(resolvedPath, templateLoader_, expressionHandler_);
    }
    catch (const std::exception &e)
    {
        throw PugParserException(
            fileName_,
            line(),
            templateLoader_,
            "The template [" + templateName + "] could not be opened. Maybe it is located outside the base path?\n" +
                string(e.what()));
    }
}

string Parser::ensurePugExtension(const string &templateName, const string &extension)
{
    if (FileSystem::getExtension(templateName).empty())
    {
        return templateName + extension;
    }
    return templateName;
}

template <typename T>
void Parser::accept(shared_ptr<T> &ret, TokenType tokenType)
{
    if (peekType() == tokenType)
        lexer_.advance((shared_ptr<Token> &)ret);
}

template <typename T>
void Parser::expect(shared_ptr<T> &ret, TokenType tokenType)
{
    TokenType type = peekType();
    if (type != tokenType)
    {
        throw PugParserException(fileName_, line(), templateLoader_, tokenType, type);
    }
    advance(ret);
}

void Parser::expect(TokenType tokenType)
{
    TokenType type = peekType();
    if (type != tokenType)
    {
        throw PugParserException(fileName_, line(), templateLoader_, tokenType, type);
    }
    advance();
}
} // namespace parser
} // namespace pugcpp
