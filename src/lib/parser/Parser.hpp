#pragma once

#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "../expression/IExpressionHandler.hpp"
#include "../lexer/Lexer.hpp"
#include "../lexer/token/AttributeList.hpp"
#include "../lexer/token/Token.hpp"
#include "../template/ITemplateLoader.hpp"
#include "../util/CharacterParser.hpp"
#include "PathHelper.hpp"
#include "node/Attr.hpp"
#include "node/AttrsNode.hpp"
#include "node/BlockNode.hpp"
#include "node/CaseConditionNode.hpp"
#include "node/Node.hpp"

using namespace std;

namespace pugcpp
{
namespace parser
{
using namespace node;
using namespace lexer;
using namespace tmpl;
using namespace expression;
using namespace util;
using namespace token;

class Parser
{
  private:
    unique_ptr<Lexer> m_pLexer;
    shared_ptr<map<string, BlockNode>> m_pmBlocks;
    shared_ptr<ITemplateLoader> m_pTemplateLoader;
    shared_ptr<IExpressionHandler> m_pExpressionHandler;
    unique_ptr<Parser> m_pclExtending;
    string m_sFilename;
    shared_ptr<list<Parser>> m_plContexts;
    CharacterParser m_clCharacterParser;
    int m_nInMixin = 0;
    shared_ptr<map<string, MixinNode>> m_pmMixins;
    int m_nInBlock = 0;
    PathHelper m_clPathHelper;

  public:
    static const regex FILE_EXTENSION_PATTERN;

    Parser(const string &filename,
           shared_ptr<ITemplateLoader> templateLoader,
           shared_ptr<IExpressionHandler> expressionHandler);
    Parser(const string &src,
           const string &filename,
           shared_ptr<ITemplateLoader> templateLoader,
           shared_ptr<IExpressionHandler> expressionHandler);

    shared_ptr<Node> parse();
    void setBlocks(shared_ptr<map<string, BlockNode>> blocks);
    map<string, BlockNode> &getBlocks();
    void setContexts(shared_ptr<list<Parser>> contexts);
    shared_ptr<list<Parser>> getContexts();
    void setMixins(shared_ptr<map<string, MixinNode>> mixins);

  private:
    shared_ptr<Node> parseExpr();
    shared_ptr<Node> parseBlockCode();
    shared_ptr<Node> parseComment();
    shared_ptr<Node> parseMixin();
    shared_ptr<Node> parseCall();
    shared_ptr<Node> parseCssClassOrId();
    shared_ptr<Node> parseBlock();
    shared_ptr<Node> parseMixinBlock();
    shared_ptr<Node> parseInclude();
    shared_ptr<Node> parseExtends();
    shared_ptr<Node> parseInterpolation();
    shared_ptr<Node> parseText();
    shared_ptr<Node> parseEach();
    shared_ptr<Node> parseWhile();
    shared_ptr<Node> parseAssignment();
    shared_ptr<Node> parseTag();
    shared_ptr<Node> parseTextBlock();
    shared_ptr<Node> parseConditional();
    shared_ptr<Node> parseBlockExpansion();
    shared_ptr<Node> parseCase();
    shared_ptr<Node> parseWhen();
    shared_ptr<Node> parseDefault();
    shared_ptr<Node> parseCode();
    shared_ptr<Node> parseDoctype();
    shared_ptr<Node> parseFilter();
    shared_ptr<Node> parseASTFilter();

    shared_ptr<BlockNode> parseYield();
    shared_ptr<Node> blockExpansion();
    shared_ptr<BlockNode> block();
    shared_ptr<list<CaseConditionNode>> whenBlock();
    shared_ptr<Node> tag(shared_ptr<AttrsNode> tagNode);
    shared_ptr<vector<Node>> parseInlineTagsInText(const string &str);
    shared_ptr<CaseConditionNode> parseCaseCondition();
    shared_ptr<list<Attr>> convertToNodeAttributes(AttributeList &attr);
    shared_ptr<Token> lookahead(int i);
    shared_ptr<Token> peek();
    shared_ptr<Token> advance();
    shared_ptr<Token> accept(/*clazz*/);
    shared_ptr<Token> expect(/*exptectTokenClass*/);
    shared_ptr<Parser> createParser(const string &templateName);
    string ensurePugExtension(const string &templateName);
    void skip(int n);
    int line();
};
} // namespace parser
} // namespace pugcpp