#include "./Lexer.hpp"

namespace pugcpp
{
namespace lexer
{
using namespace exceptions;

const regex Lexer::cleanRe = regex("^['\"]|['\"]$");
const regex Lexer::doubleQuotedRe = regex("^\"[^\"]*\"$");
const regex Lexer::quotedRe = regex("^'[^']*'$");
const map<char, char> Lexer::closingBrackets = {{'(', ')'}, {'{', '}'}, {'[', ']'}};

// public
Lexer::Lexer(
    const string &filename,
    shared_ptr<ITemplateLoader> templateLoader,
    shared_ptr<IExpressionHandler> expressionHandler)
: templateLoader_(templateLoader), expressionHandler_(expressionHandler)
{
    fileName_ = ensurePugExtension(filename, *templateLoader_);
    istream &reader = templateLoader->getReader(fileName_);
    scanner_ = make_unique<Scanner>(reader);
}

Lexer::Lexer(
    const string &input,
    const string &filename,
    shared_ptr<ITemplateLoader> templateLoader,
    shared_ptr<IExpressionHandler> expressionHandler)
: templateLoader_(templateLoader), expressionHandler_(expressionHandler)
{
    fileName_ = ensurePugExtension(filename, *templateLoader_);
    scanner_ = make_unique<Scanner>(input);
}

const int Lexer::getLineno() const
{
    return lneno_;
}

const bool Lexer::getPipeless() const
{
    return pipeless_;
}

void Lexer::setPipeless(bool pipeless)
{
    pipeless_ = pipeless;
}

const bool Lexer::isEndOfAttribute(
    const int i,
    const string &str,
    const string &key,
    const string &val,
    const Loc &loc,
    const CharacterParser::State &state) const
{
    if (StringUtils::trim(key).empty())
        return false;
    if (i == str.length())
        return true;
    if (Loc::KEY == loc)
    {
        if (str[i] == ' ' || str[i] == '\n')
        {
            for (int x = i; x < str.length(); ++x)
            {
                if (str[x] != ' ' && str[x] != '\n')
                {
                    switch (str[x])
                    {
                    case '=':
                    case '!':
                    case ',': return false; break;

                    default: return true; break;
                    }
                }
            }
        }
        return (str[i] == ',');
    }
    else if (Loc::VALUE == loc && !state.isNesting())
    {
        try
        {
            expressionHandler_->assertExpression(val);
        }
        catch (const std::exception &e)
        {
            return false;
        }
        if (str[i] == ' ' || str[i] == '\n')
        {
            for (int x = i; x < str.length(); ++x)
            {
                if (str[x] != ' ' && str[x] != '\n')
                {
                    if (CharacterParser::isPunctuator(str[x] && str[x] != '"' && str[x] != '\''))
                        return false;
                    return true;
                }
            }
        }
        return (str[i] == ',');
    }
    return false;
}

void Lexer::consume(int len)
{
    scanner_->consume(len);
}

void Lexer::defer(shared_ptr<Token> tok)
{
    deferredTokens_.push(tok);
}

shared_ptr<Token> Lexer::lookahead(int n)
{
    int fetch = n - stash_.size();
    while (fetch > 0)
    {
        stash_.push_back(next());
        fetch = fetch - 1;
    }
    n = n - 1;

    return stash_.at(n);
}

shared_ptr<Token> Lexer::next()
{
    shared_ptr<Token> token;

    deferred(token);
    if (token)
        return token;

    blank(token);
    if (token)
        return token;

    eos(token);
    if (token)
        return token;

    pipelessText(token);
    if (token)
        return token;

    yield(token);
    if (token)
        return token;

    doctype(token);
    if (token)
        return token;

    interpolation(token);
    if (token)
        return token;

    caseToken(token);
    if (token)
        return token;

    when(token);
    if (token)
        return token;

    defaultToken(token);
    if (token)
        return token;

    extendsToken(token);
    if (token)
        return token;

    append(token);
    if (token)
        return token;

    prepend(token);
    if (token)
        return token;

    block(token);
    if (token)
        return token;

    mixinBlock(token);
    if (token)
        return token;

    include(token);
    if (token)
        return token;

    includeFiltered(token);
    if (token)
        return token;

    mixin(token);
    if (token)
        return token;

    call(token);
    if (token)
        return token;

    conditional(token);
    if (token)
        return token;

    each(token);
    if (token)
        return token;

    whileToken(token);
    if (token)
        return token;

    tag(token);
    if (token)
        return token;

    filter(token);
    if (token)
        return token;

    blockCode(token);
    if (token)
        return token;

    code(token);
    if (token)
        return token;

    id(token);
    if (token)
        return token;

    className(token);
    if (token)
        return token;

    attrs(token);
    if (token)
        return token;

    attributesBlock(token);
    if (token)
        return token;

    indent(token);
    if (token)
        return token;

    text(token);
    if (token)
        return token;

    comment(token);
    if (token)
        return token;

    colon(token);
    if (token)
        return token;

    dot(token);
    if (token)
        return token;

    assignment(token);
    if (token)
        return token;

    textFail(token);
    if (token)
        return token;

    throw PugLexerException(
        "unexpected text: " + scanner_->getInput().substr(0, 5), fileName_, lneno_, templateLoader_);

    return token;
}

shared_ptr<Token> Lexer::advance()
{
    shared_ptr<Token> t;
    stashed(t);

    return t ? t : next();
}

shared_ptr<list<shared_ptr<Token>>> Lexer::getTokens()
{
    shared_ptr<Token> t;
    shared_ptr<list<shared_ptr<Token>>> ret;

    while ((t = advance()))
    {
        ret->push_back(t);
        if (t->getType() == TokenType::e_Eos)
            break;
    }
    return ret;
}

// private
shared_ptr<CharacterParser::Match> Lexer::bracketExpression()
{
    return bracketExpression(0);
}

shared_ptr<CharacterParser::Match> Lexer::bracketExpression(int skip)
{
    char start = scanner_->getInput().at(skip);
    if (start != '(' && start != '{' && start != '[')
    {
        throw PugLexerException("unrecognized start character", fileName_, getLineno(), templateLoader_);
    }

    const char end = closingBrackets.at(start);
    Options opt;
    opt.setStart(skip + 1);
    shared_ptr<CharacterParser::Match> range;
    try
    {
        range = characterParser_.parseMax(scanner_->getInput(), &opt);
    }
    catch (const CharacterParser::SyntaxError &e)
    {
        throw PugLexerException(
            string(e.what()) + " See" + scanner_->getInput().substr(0, 5),
            fileName_,
            getLineno(),
            templateLoader_);
    }
    char foundEnd = scanner_->getInput().at(range->getEnd());
    if (foundEnd != end)
        throw PugLexerException(
            "start character `" + string(1, start) + "` does not match end character `" + string(1, foundEnd) + "`.",
            fileName_,
            getLineno(),
            templateLoader_);

    return range;
}

string Lexer::scan(const string &regexp, int group)
{
    smatch matcher;
    string str = "";

    scanner_->getMatcherForPattern(matcher, regexp);
    if (!matcher.empty() && matcher.size() > group)
    {
        str = matcher.str(group);
        consume(matcher.position(0) + matcher.length(0));
    }

    return str;
}

string Lexer::interpolate(const string &attr, const char quote)
{
    regex rgx("(\\\\)?#\\{(.+)");

    return StringReplacer::replace(attr, rgx, [this, quote](smatch &m) {
        string match = m.str(0);
        string escape = m.str(1);
        string expr = m.str(2);
        if (escape.empty())
            return match;
        try
        {
            try
            {
                shared_ptr<CharacterParser::Match> range = characterParser_.parseMax(expr);
                if (expr[range->getEnd()] != '}')
                    return match.substr(0, 2) + interpolate(match.substr(2), quote);
                expressionHandler_->assertExpression(range->getSrc());
                return quote + " (" + range->getSrc() + ") " + quote +
                       interpolate(expr.substr(range->getEnd() + 1), quote);
            }
            catch (ExpressionException &ex)
            {
                return match.substr(0, 2) + interpolate(match.substr(2), quote);
            }
        }
        catch (CharacterParser::SyntaxError &e)
        {
            throw PugLexerException(e.getMessage() + " See " + match, fileName_, lneno_, templateLoader_);
        }
    });
}

string Lexer::ensurePugExtension(const string &templateName, const ITemplateLoader &templateLoader)
{
    if (FileSystem::getExtension(templateName).empty())
    {
        return templateName + "." + templateLoader.getExtension();
    }
    return templateName;
}

bool Lexer::assertNestingCorrect(const string &exp)
{
    // this verifies that code is properly nested, but allows
    // invalid JavaScript such as the contents of `attributes`
    try
    {
        shared_ptr<CharacterParser::State> res = characterParser_.parse(exp);
        if (res->isNesting())
        {
            throw PugLexerException(
                "Nesting must match on expression `" + exp + "`", fileName_, lneno_, templateLoader_);
        }
    }
    catch (const CharacterParser::SyntaxError &e)
    {
        throw PugLexerException(
            "Nesting must match on expression `" + exp + "`", fileName_, lneno_, templateLoader_);
    }

    return true;
}

void Lexer::stashed(shared_ptr<Token> &ret)
{
    if (stash_.size() == 0)
        return;

    ret = stash_.front();
    stash_.pop_front();
}

void Lexer::deferred(shared_ptr<Token> &ret)
{
    if (deferredTokens_.size() == 0)
        return;

    ret = deferredTokens_.front();
    deferredTokens_.pop();
}

void Lexer::blank(shared_ptr<Token> &ret)
{
    smatch matcher;

    scanner_->getMatcherForPattern(matcher, "^\\n *\\n");
    if (!matcher.empty())
    {
        consume(matcher.position(0) + matcher.length(0) - 1);
        lneno_++;

        if (pipeless_)
            ret = make_shared<Text>("", lneno_);
        else
            ret = next();
    }
}

void Lexer::eos(shared_ptr<Token> &ret)
{
    if (scanner_->getInput().length() > 0)
        return;

    if (indentStack_.size() > 0)
    {
        indentStack_.pop();
        ret = make_shared<Outdent>(lneno_);
    }
    else
    {
        ret = make_shared<Eos>("eos", lneno_);
    }
}

void Lexer::comment(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^\\/\\/(-)?([^\\n]*)");

    if (matcher.empty() || matcher.size() < 3)
        return;

    bool buffer = ("-" != matcher.str(1));
    ret = make_shared<Comment>(matcher.str(2), lneno_, buffer);
    pipeless_ = true;
    consume(matcher.position(0) + matcher.length(0));
}

void Lexer::code(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^(!?=|-)[ \\t]*([^\\n]+)");

    if (matcher.empty() || matcher.size() < 3)
        return;

    string flags = matcher.str(1);
    shared_ptr<Expression> tok = make_shared<Expression>(matcher.str(2), lneno_);
    tok->setEscape(flags[0] == '=');
    tok->setBuffer(flags[0] == '=' || (flags.length() > 1 && flags[1] == '='));
    if (tok->isBuffer())
    {
        try
        {
            expressionHandler_->assertExpression(matcher.str(2));
        }
        catch (ExpressionException &e)
        {
            throw PugLexerException(e.getMessage(), fileName_, lneno_, templateLoader_);
        }
    }
    consume(matcher.position(0) + matcher.length(0));
    ret = tok;
}

void Lexer::interpolation(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^#\\{");

    if (matcher.empty())
        return;

    try
    {
        shared_ptr<CharacterParser::Match> match = bracketExpression(1);
        consume(match->getEnd() + 1);
        ret = make_shared<Interpolation>(match->getSrc(), lneno_);
    }
    catch (exception &e)
    {
        return;
    }
}

void Lexer::tag(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^(\\w[-:\\w]*)(\\/?)");

    if (matcher.empty() || matcher.size() < 3)
        return;

    string name = matcher.str(1);
    consume(matcher.length(0));
    if (':' == name.back())
    {
        name.pop_back();
        defer(make_shared<Colon>(lneno_));
        while (' ' == scanner_->getInput().front())
            consume(1);
    }
    shared_ptr<Tag> tok = make_shared<Tag>(name, lneno_);
    if (matcher.length(2) > 0)
        tok->setSelfClosing(true);

    ret = tok;
}

void Lexer::yield(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^yield *");

    if (matcher.empty())
        return;

    consume(matcher.position(0) + matcher.length(0));
    ret = make_shared<Yield>(lneno_);
}

void Lexer::filter(shared_ptr<Token> &ret)
{
    string val = scan("^:([\\w\\-]+)");
    if (StringUtils::isNotBlank(val))
    {
        ret = make_shared<Filter>(val, lneno_);
        pipeless_ = true;
    }
}

void Lexer::each(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(
        matcher, "^(?:- *)?(?:each|for) +([a-zA-Z_$][\\w$]*)(?: *, *([a-zA-Z_$][\\w$]*))? * in *([^\\n]+)");

    if (matcher.empty() || matcher.size() < 4)
        return;

    ret = make_shared<Each>(matcher.str(1), lneno_, matcher.str(2), matcher.str(3));
    consume(matcher.position(0) + matcher.length(0));
}

void Lexer::whileToken(shared_ptr<Token> &ret)
{
    string val = scan("^while +([^\\n]+)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<While>(val, lneno_);
}

void Lexer::conditional(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^(if|unless|else if|else)\\b([^\\n]*)");

    if (matcher.empty() || matcher.size() < 3)
        return;

    string type = matcher.str(1);
    string condition = matcher.str(2);
    consume(matcher.position(0) + matcher.length(0));
    if (type == "else")
        ret = make_shared<Else>("", lneno_);
    else if (type == "else if")
        ret = make_shared<ElseIf>(condition, lneno_);
    else
        ret = make_shared<If>(condition, lneno_, (type == "unless"));
}

void Lexer::doctype(shared_ptr<Token> &ret)
{
    string val = scan("^!!! *([^\\n]+)?");
    if (StringUtils::isNotBlank(val))
        throw PugLexerException(
            "`!!!` is deprecated, you must now use `doctype`", fileName_, lneno_, templateLoader_);

    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^(?:doctype) *([^\\n]+)?");
    if (matcher.empty() || matcher.size() < 2)
        return;

    string name = matcher.str(1);
    consume(matcher.length(0));
    if (!name.empty() && "5" == StringUtils::trim(name))
        throw PugLexerException(
            "`doctype 5` is deprecated, you must now use `doctype html`", fileName_, lneno_, templateLoader_);
    ret = make_shared<Doctype>(name, lneno_);
}

void Lexer::id(shared_ptr<Token> &ret)
{
    string val = scan("^#([\\w-]+)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<CssId>(val, lneno_);
}

void Lexer::className(shared_ptr<Token> &ret)
{
    string val = scan("^\\.([\\w-]+)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<CssClass>(val, lneno_);
}

void Lexer::text(shared_ptr<Token> &ret)
{
    string val = scan("^\\.([\\w-]+)");
    if (val.empty())
    {
        val = scan("^\\|?( )");
        if (val.empty())
            val = scan("^(<[^\\n]*)");
    }
    if (StringUtils::isNotBlank(val))
        ret = make_shared<Text>(val, lneno_);
}

void Lexer::textFail(shared_ptr<Token> &ret)
{
    string val = scan("^([^\\.\\n][^\\n]+)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<Text>(val, lneno_);
}

void Lexer::extendsToken(shared_ptr<Token> &ret)
{
    string val = scan("^extends? +([^\\n]+)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<ExtendsToken>(val, lneno_);
}

void Lexer::prepend(shared_ptr<Token> &ret)
{
    string name = scan("^prepend +([^\\n]+)");
    if (StringUtils::isNotBlank(name))
    {
        ret = make_shared<Block>(name, lneno_);
        ret->setMode("prepend");
    }
}

void Lexer::append(shared_ptr<Token> &ret)
{
    string name = scan("^append +([^\\n]+)");
    if (StringUtils::isNotBlank(name))
    {
        ret = make_shared<Block>(name, lneno_);
        ret->setMode("append");
    }
}

void Lexer::block(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^block\\b *(?:(prepend|append) +)?([^\\n]+)");

    if (matcher.empty() || matcher.size() < 3)
        return;

    string val = matcher.str(1);
    string mode = StringUtils::isNotBlank(val) ? val : "replace";
    ret = make_shared<Block>(matcher.str(2), lneno_);
    ret->setMode(mode);
    consume(matcher.position(0) + matcher.length(0));
}

void Lexer::mixinBlock(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^block[ \\t]*(\\n|$)");

    if (matcher.empty() || matcher.size() < 2)
        return;

    consume(matcher.position(0) + matcher.length(0) - matcher.length(1));
    ret = make_shared<MixinBlock>(lneno_);
}

void Lexer::blockCode(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^-\\n");

    if (matcher.empty())
        return;

    consume(matcher.position(0) + matcher.length(0) - 1);
    pipeless_ = true;
    ret = make_shared<BlockCode>(lneno_);
}

void Lexer::include(shared_ptr<Token> &ret)
{
    string val = scan("^include +([^\\n]+)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<Include>(val, lneno_);
}

void Lexer::includeFiltered(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^include:([\\w\\-]+)([\\( ])");

    if (matcher.empty() || matcher.size() < 3)
        return;

    string filter = matcher.str(1);
    string g2 = matcher.str(2);
    consume(matcher.position(0) + matcher.length(0) - 1);
    shared_ptr<Token> att;
    if (g2 == "(")
        attrs(att);
    if (g2 != " " && scanner_->getInput()[0] != ' ')
        throw PugLexerException(
            "expected space after include:filter but got " + string(1, scanner_->getInput()[0]),
            fileName_,
            lneno_,
            templateLoader_);
    scanner_->getMatcherForPattern(matcher, "^ *([^\\n]+)");
    if (matcher.empty() || matcher.size() < 2 || StringUtils::trim(matcher.str(1)).empty())
        throw PugLexerException("missing path for include:filter", fileName_, lneno_, templateLoader_);
    shared_ptr<Include> tok = make_shared<Include>(matcher.str(1), lneno_);
    tok->setFilter(filter);
    if (att)
        tok->setAttrs(att);

    ret = tok;
}

void Lexer::caseToken(shared_ptr<Token> &ret)
{
    string val = scan("^case +([^\\n]+)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<CaseToken>(val, lneno_);
}

void Lexer::when(shared_ptr<Token> &ret)
{
    string val = scan("^when +([^:\\n]+)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<When>(val, lneno_);
}

void Lexer::defaultToken(shared_ptr<Token> &ret)
{
    string val = scan("^(default *)");
    if (StringUtils::isNotBlank(val))
        ret = make_shared<Default>(val, lneno_);
}

void Lexer::assignment(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^(\\w+) += *([^;\\n]+)( *;? *)");

    if (matcher.empty() || matcher.size() < 3)
        return;

    shared_ptr<Assignment> tok = make_shared<Assignment>(matcher.str(2), lneno_);
    tok->setName(matcher.str(1));
    consume(matcher.position(0) + matcher.length(0));
    ret = tok;
}

void Lexer::dot(shared_ptr<Token> &ret)
{
    pipeless_ = true;
    smatch matcher;

    scanner_->getMatcherForPattern(matcher, "^\\.");
    if (matcher.empty())
        return;

    ret = make_shared<Dot>(lneno_);
    consume(matcher.position(0) + matcher.length(0));
}

void Lexer::mixin(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^mixin +([-\\w]+)(?: *\\((.*)\\))? *");

    if (matcher.empty() || matcher.size() < 3)
        return;

    shared_ptr<Mixin> tok = make_shared<Mixin>(matcher.str(1), lneno_);
    tok->setArguments(matcher.str(2));
    consume(matcher.position(0) + matcher.length(0));
    ret = tok;
}

void Lexer::call(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^\\+(\\s*)(([-\\w]+)|(#\\{))");

    if (matcher.empty() || matcher.size() < 5)
        return;

    shared_ptr<Call> tok;
    // try to consume simple or interpolated call
    if (matcher[3].matched)
    {
        // simple call
        tok = make_shared<Call>(matcher.str(3), lneno_);
        consume(matcher.position(0) + matcher.length(0));
    }
    else
    {
        // interpolated call
        shared_ptr<CharacterParser::Match> match = bracketExpression(2 + matcher.length(1));
        consume(match->getEnd() + 1);
        try
        {
            expressionHandler_->assertExpression(match->getSrc());
        }
        catch (std::exception &e)
        {
            throw Exception("Assert expresson failed.", &e);
        }
        tok = make_shared<Call>("#{" + match->getSrc() + "}", lneno_);
    }
    scanner_->getMatcherForPattern(matcher, "^ *\\(");
    if (!matcher.empty())
    {
        shared_ptr<CharacterParser::Match> range = bracketExpression(matcher.length(0) - 1);
        regex_search(range->getSrc(), matcher, regex("^\\s*[-\\w]+ *="));
        if (matcher.empty())
        {
            consume(range->getEnd() + 1);
            tok->setArguments(range->getSrc());
        }
        if (!tok->getArguments().empty())
        {
            try
            {
                expressionHandler_->assertExpression("[" + tok->getArguments() + "]");
            }
            catch (std::exception &e)
            {
                throw Exception("Assert expresson failed.", &e);
            }
        }
    }
    ret = tok;
}

void Lexer::attrs(shared_ptr<Token> &ret)
{
    if (scanner_->getInput()[0] != '(')
        return;

    int index = bracketExpression()->getEnd();
    string str = scanner_->getInput().substr(1, index - 1);
    shared_ptr<AttributeList> tok = make_shared<AttributeList>(lneno_);

    assertNestingCorrect(str);
    consume(index + 1);

    char quote;
    string key;
    string val;
    string interpolatable;
    bool escapedAttr = true;
    shared_ptr<CharacterParser::State> state = characterParser_.defaultState();
    Loc loc = Loc::KEY;

    lneno_ += StringUtils::occurences(str, "\n");

    for (int i = 0; i <= str.length(); ++i)
    {
        if (isEndOfAttribute(i, str, key, val, loc, *state))
        {
            StringUtils::argTrim(val);
            StringUtils::replaceAll(val, "\\n", "");
            if (!val.empty())
            {
                try
                {
                    expressionHandler_->assertExpression(val);
                }
                catch (ExpressionException &e)
                {
                    throw PugLexerException(e.getMessage(), fileName_, lneno_, templateLoader_);
                }
            }
            // val = unescapeJson(val); //TODO
            StringUtils::argTrim(key);
            StringUtils::replaceAll(key, "^['\"]|['\"]$", "");
            if (val.empty())
                tok->addBoolAttribute(key, true);
            else if (regex_search(val, doubleQuotedRe) || regex_search(val, quotedRe))
                tok->addAttribute(key, regex_replace(val, cleanRe, ""), escapedAttr);
            else
                tok->addExpressionAttribute(key, val, escapedAttr);
            key.clear();
            val.clear();
            loc = Loc::KEY;
            escapedAttr = false;
        }
        else
        {
            switch (loc)
            {
            case Loc::KEY_CHAR:
            {
                if (str[i] == quote)
                {
                    loc = Loc::KEY;
                    const vector<char> expectedCharacters = {' ', ',', '!', '=', '\n'};
                    if ((i + 1) < str.length() &&
                        find(expectedCharacters.begin(), expectedCharacters.end(), str[i + 1]) !=
                            expectedCharacters.end())
                        throw PugLexerException(
                            "Unexpected character" + string(1, str[i + 1]) + " expected ` `, `\\n`, `,`, `!` or `=`",
                            fileName_,
                            lneno_,
                            templateLoader_);
                }
                else
                {
                    key += str[i];
                }
            }
            break;
            case Loc::KEY:
            {
                if (str.empty())
                    break;

                if (key.empty() && (str[i] == '"' || str[i] == '\''))
                {
                    loc = Loc::KEY_CHAR;
                    quote = str[i];
                }
                else if ((str[i] == '!' || str[i] == '='))
                {
                    escapedAttr = (str[i] != '!');
                    if (str[i] == '!')
                        i++;
                    if (str[i] != '=')
                        throw PugLexerException(
                            "Unexpected character" + string(1, str[i]) + " expected `=`",
                            fileName_,
                            lneno_,
                            templateLoader_);
                    loc = Loc::VALUE;
                    state = characterParser_.defaultState();
                }
                else
                {
                    key += str[i];
                }
            }
            break;
            case Loc::VALUE:
            {
                characterParser_.parseChar(str[i], state);
                if (state->isString())
                {
                    loc = Loc::STRING;
                    quote = str[i];
                    interpolatable = str[i];
                }
                else
                {
                    val += str[i];
                }
            }
            break;
            case Loc::STRING:
            {
                characterParser_.parseChar(str[i], state);
                interpolatable += str[i];
                if (!state->isString())
                {
                    loc = Loc::VALUE;
                    val += interpolate(interpolatable, quote);
                }
            }
            break;

            default: break;
            }
        }
    }

    if (!scanner_->getInput().empty() && scanner_->getInput()[0] == '/')
    {
        consume(1);
        tok->setSelfClosing(true);
    }

    ret = tok;
}

void Lexer::attributesBlock(shared_ptr<Token> &ret)
{
    smatch matcher;
    scanner_->getMatcherForPattern(matcher, "^&attributes\\b");

    if (matcher.empty() || matcher.length(0) == 0)
        return;

    consume(11);
    shared_ptr<CharacterParser::Match> match = bracketExpression();
    consume(match->getEnd() + 1);
    ret = make_shared<AttributesBlock>(match->getSrc(), lneno_);
}

void Lexer::indent(shared_ptr<Token> &ret)
{
    smatch matcher;

    if (!indentRe_.empty())
        scanner_->getMatcherForPattern(matcher, indentRe_);
    else
    {
        string re;

        // tabs
        re = "^\\n(\\t*) *";
        scanner_->getMatcherForPattern(matcher, re);

        // spaces
        if (!matcher.empty() && matcher.length(1) == 0)
        {
            re = "^\\n( *)";
            scanner_->getMatcherForPattern(matcher, re);
        }

        // established
        if (!matcher.empty() && matcher.length(1) > 0)
            indentRe_ = re;
    }

    if (matcher.empty() || matcher.size() < 2)
        return;

    int indents = matcher.length(1);
    lneno_++;
    consume(indents + 1);

    const string &input = scanner_->getInput();
    if (input.length() > 0 && (input[0] == ' ' || input[0] == '\t'))
    {
        throw PugLexerException(
            "Invalid indentation, you can use tabs or spaces but not both",
            fileName_,
            lneno_,
            templateLoader_);
    }

    // blank line
    if (scanner_->isBlankLine())
    {
        pipeless_ = false;

        ret = make_shared<Newline>(lneno_);
        return;
    }

    // outdent
    if (!indentStack_.empty() && indents < indentStack_.top())
    {
        while (!indentStack_.empty() && indents < indentStack_.top())
        {
            stash_.push_back(make_shared<Outdent>(lneno_));
            indentStack_.pop();
        }
        ret = stash_.back();
        stash_.pop_back();
    }
    // indent
    else if (indents > 0 && (indentStack_.empty() || indents != indentStack_.top()))
    {
        indentStack_.push(indents);
        ret = make_shared<Indent>(to_string(indents), lneno_);
        ret->setIndents(indents);
    }
    // newline
    else
    {
        ret = make_shared<Newline>(lneno_);
    }
    pipeless_ = false;
}

void Lexer::pipelessText(shared_ptr<Token> &ret)
{
    if (!pipeless_)
        return;

    smatch matcher;
    if (!indentRe_.empty())
    {
        scanner_->getMatcherForPattern(matcher, indentRe_);
    }
    else
    {
        string re;
        // tabs
        re = "^\\n(\\t*) *";
        scanner_->getMatcherForPattern(matcher, re);

        // spaces
        if (!matcher.empty() && matcher.length(1) == 0)
        {
            re = "^\\n( *)";
            scanner_->getMatcherForPattern(matcher, re);
        }
        // established
        if (!matcher.empty() && matcher.length(1) > 0)
            indentRe_ = re;
    }
    if (matcher.empty() || !matcher.length(1) > 0)
        return;

    int indents = matcher.length(1);
    if (indents == 0 || (indentStack_.size() > 0 && indents <= indentStack_.top()))
        return;

    string indent = matcher.str(1);
    vector<string> tokens;
    bool isMatch = false;

    do
    {
        int i = scanner_->getInput().find('\n', 1);
        if (i == string::npos)
            i = scanner_->getInput().length() - 1;
        else
            --i;
        string str = scanner_->getInput().substr(1, i);
        int indentLength = indent.length();
        if (str.length() <= indentLength)
            indentLength = str.length();
        isMatch = (str.substr(0, indentLength) == indent || StringUtils::trim(str).length() == 0);
        if (isMatch)
        {
            tokens.push_back(str.substr(indentLength));
            ++lneno_;
            consume(str.length() + 1);
        }
    } while (scanner_->getInput().length() > 0 && isMatch);
    while (scanner_->getInput().length() == 0 && tokens.back() == "")
    {
        tokens.pop_back();
    }
    ret = make_shared<PipelessText>(lneno_);
    ret->setValues(tokens);
}

void Lexer::colon(shared_ptr<Token> &ret)
{
    string val = scan("^: *", 0);
    if (!val.empty())
        ret = make_shared<Colon>(lneno_);
}

} // namespace lexer
} // namespace pugcpp
