#include "./Lexer.hpp"

namespace pugcpp
{
namespace lexer
{
using namespace exceptions;

const regex Lexer::m_rgCleanRe = regex("^['\"]|['\"]$");
const regex Lexer::m_rgDoubleQuotedRe = regex("^\"[^\"]*\"$");
const regex Lexer::m_rgQuotedRe = regex("^'[^']*'$");
const map<char, char> Lexer::m_conClosingBrackets = {{'(', ')'}, {'{', '}'}, {'[', ']'}};

// public
Lexer::Lexer(
    const string &filename,
    shared_ptr<ITemplateLoader> templateLoader,
    shared_ptr<IExpressionHandler> expressionHandler)
: m_pclTemplateLoader(templateLoader), m_pclExpressionHandler(expressionHandler)
{
    m_sFilename = ensurePugExtension(filename, *m_pclTemplateLoader);
    istream &reader = templateLoader->getReader(m_sFilename);
    m_pclScanner = make_unique<Scanner>(reader);
    m_pclCharacterParser = make_shared<CharacterParser>();
}

Lexer::Lexer(
    const string &input,
    const string &filename,
    shared_ptr<ITemplateLoader> templateLoader,
    shared_ptr<IExpressionHandler> expressionHandler)
: m_pclTemplateLoader(templateLoader), m_pclExpressionHandler(expressionHandler)
{
    m_sFilename = ensurePugExtension(filename, *m_pclTemplateLoader);
    m_pclScanner = make_unique<Scanner>(input);
    m_pclCharacterParser = make_shared<CharacterParser>();
}

const int Lexer::getLineno() const
{
    return m_nLineno;
}

const bool Lexer::getPipeless() const
{
    return m_bPipeless;
}

void Lexer::setPipeless(bool pipeless)
{
    m_bPipeless = pipeless;
}

const bool Lexer::isEndOfAttribute(
    int i,
    const string &str,
    const string &key,
    const string &val,
    Loc loc,
    CharacterParser::State state) const
{
}

void Lexer::consume(int len)
{
    m_pclScanner->consume(len);
}

void Lexer::defer(shared_ptr<Token> tok)
{
    m_conDeferredTokens.push_back(tok);
}

shared_ptr<Token> Lexer::lookahead(int n)
{
    int fetch = n - m_conStash.size();
    while (fetch > 0)
    {
        m_conStash.push_back(next());
        fetch = fetch - 1;
    }
    n = n - 1;
    return m_conStash.at(n);
}

shared_ptr<Token> Lexer::next()
{
    shared_ptr<Token> token;

    if ((token = deferred()))
    {
        return token;
    }

    if ((token = blank()))
    {
        return token;
    }

    if ((token = eos()))
    {
        return token;
    }

    if ((token = pipelessText()))
    {
        return token;
    }

    if ((token = yield()))
    {
        return token;
    }

    if ((token = doctype()))
    {
        return token;
    }

    if ((token = interpolation()))
    {
        return token;
    }

    if ((token = caseToken()))
    {
        return token;
    }

    if ((token = when()))
    {
        return token;
    }

    if ((token = defaultToken()))
    {
        return token;
    }

    if ((token = extendsToken()))
    {
        return token;
    }

    if ((token = append()))
    {
        return token;
    }

    if ((token = prepend()))
    {
        return token;
    }

    if ((token = block()))
    {
        return token;
    }

    if ((token = mixinBlock()))
    {
        return token;
    }

    if ((token = include()))
    {
        return token;
    }

    if ((token = includeFiltered()))
    {
        return token;
    }

    if ((token = mixin()))
    {
        return token;
    }

    if ((token = call()))
    {
        return token;
    }

    if ((token = conditional()))
    {
        return token;
    }

    if ((token = each()))
    {
        return token;
    }

    if ((token = whileToken()))
    {
        return token;
    }

    if ((token = tag()))
    {
        return token;
    }

    if ((token = filter()))
    {
        return token;
    }
    if ((token = blockCode()))
    {
        return token;
    }

    if ((token = code()))
    {
        return token;
    }

    if ((token = id()))
    {
        return token;
    }

    if ((token = className()))
    {
        return token;
    }

    if ((token = attrs()))
    {
        return token;
    }

    if ((token = attributesBlock()))
    {
        return token;
    }

    if ((token = indent()))
    {
        return token;
    }

    if ((token = text()))
    {
        return token;
    }

    if ((token = comment()))
    {
        return token;
    }

    if ((token = colon()))
    {
        return token;
    }

    if ((token = dot()))
    {
        return token;
    }

    if ((token = assignment()))
    {
        return token;
    }

    if ((token = textFail()))
    {
        return token;
    }

    if ((token = fail()))
    {
        return token;
    }

    return token;
}

shared_ptr<Token> Lexer::advance()
{
    shared_ptr<Token> t = stashed();

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
    char start = m_pclScanner->getInput().at(skip);
    if (start != '(' && start != '{' && start != '[')
    {
        throw PugLexerException("unrecognized start character", m_sFilename, getLineno(), m_pclTemplateLoader);
    }

    const char end = m_conClosingBrackets.at(start);
    shared_ptr<Options> options = make_shared<Options>();
    shared_ptr<CharacterParser::Match> range;
    try
    {
        range = m_pclCharacterParser->parseMax(m_pclScanner->getInput(), options);
    }
    catch (const CharacterParser::SyntaxError &e)
    {
        throw PugLexerException(
            string(e.what()) + " See" + m_pclScanner->getInput().substr(0, 5),
            m_sFilename,
            getLineno(),
            m_pclTemplateLoader);
    }
    char foundEnd = m_pclScanner->getInput().at(range->getEnd());
    if (foundEnd != end)
    {
        string st(1, start);
        string fen(1, foundEnd);
        throw PugLexerException(
            "start character " + st + " does not match end character " + fen,
            m_sFilename,
            getLineno(),
            m_pclTemplateLoader);
    }

    return range;
}

string Lexer::scan(const string &regexp, int group)
{
    shared_ptr<smatch> matcher = m_pclScanner->getMatcharForPattern(regexp);
    if (!matcher->empty() && matcher->size() > group)
    {
        int end = matcher->position(0) + matcher->length(0);
        consume(end);

        return (*matcher)[group].str();
    }

    return "";
}

string Lexer::interpolate(const string &attr, const string &quote)
{
    regex rgx("(\\\\)?#\\{(.+)");
    // TODO
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
        shared_ptr<CharacterParser::State> res = m_pclCharacterParser->parse(exp);
        if (res->isNesting())
        {
            throw PugLexerException(
                "Nesting must match on expression `" + exp + "`", m_sFilename, m_nLineno, m_pclTemplateLoader);
        }
    }
    catch (const CharacterParser::SyntaxError &e)
    {
        throw PugLexerException(
            "Nesting must match on expression `" + exp + "`", m_sFilename, m_nLineno, m_pclTemplateLoader);
    }

    return true;
}

shared_ptr<Token> Lexer::stashed()
{
    shared_ptr<Token> ret;

    if (m_conStash.size() > 0)
    {
        ret = m_conStash.front();
        m_conStash.pop_front();
    }

    return ret;
}

shared_ptr<Token> Lexer::deferred()
{
    shared_ptr<Token> ret;

    if (m_conDeferredTokens.size() > 0)
    {
        ret = m_conDeferredTokens.front();
        m_conDeferredTokens.pop_front();
    }

    return ret;
}

shared_ptr<Token> Lexer::blank()
{
    shared_ptr<Token> ret;
    shared_ptr<smatch> matcher = m_pclScanner->getMatcharForPattern("^\\n *\\n");

    if (!matcher->empty())
    {
        int end = matcher->position(0) + matcher->length(0);
        consume(end - 1);
        m_nLineno++;

        if (m_bPipeless)
            ret = static_pointer_cast<Token>(make_shared<Text>("", m_nLineno));
        else
            ret = next();
    }

    return ret;
}

shared_ptr<Token> Lexer::eos()
{
    shared_ptr<Token> ret;

    if (m_pclScanner->getInput().length() > 0)
        return ret;

    if (m_conIndentStack.size() > 0)
    {
        m_conIndentStack.pop();
        ret = static_pointer_cast<Token>(make_shared<Outdent>(m_nLineno));
    }
    else
    {
        ret = static_pointer_cast<Token>(make_shared<Eos>("eos", m_nLineno));
    }

    return ret;
}

shared_ptr<Token> Lexer::comment()
{
    shared_ptr<Token> ret;
    shared_ptr<smatch> matcher = m_pclScanner->getMatcharForPattern("^\\/\\/(-)?([^\\n]*)");

    if (!matcher->empty() && matcher->size() > 1) {
        int end = matcher->position(0) + matcher->length(0);
        consume(end);
        bool buffer = !("-" == matcher->str(1));
        ret = static_pointer_cast<Token>(make_shared<Comment>(matcher->str(2), m_nLineno, buffer));
        m_bPipeless = true;
    }

    return ret;
}

shared_ptr<Token> Lexer::code()
{
}

shared_ptr<Token> Lexer::interpolation()
{
}

shared_ptr<Token> Lexer::tag()
{
}

shared_ptr<Token> Lexer::yield()
{
}

shared_ptr<Token> Lexer::filter()
{
}

shared_ptr<Token> Lexer::each()
{
}

shared_ptr<Token> Lexer::whileToken()
{
}

shared_ptr<Token> Lexer::conditional()
{
}

shared_ptr<Token> Lexer::doctype()
{
}

shared_ptr<Token> Lexer::id()
{
}

shared_ptr<Token> Lexer::className()
{
}

shared_ptr<Token> Lexer::text()
{
}

shared_ptr<Token> Lexer::textFail()
{
}

shared_ptr<Token> Lexer::fail()
{
}

shared_ptr<Token> Lexer::extendsToken()
{
}

shared_ptr<Token> Lexer::prepend()
{
}

shared_ptr<Token> Lexer::append()
{
}

shared_ptr<Token> Lexer::block()
{
}

shared_ptr<Token> Lexer::mixinBlock()
{
}

shared_ptr<Token> Lexer::blockCode()
{
}

shared_ptr<Token> Lexer::include()
{
}

shared_ptr<Token> Lexer::includeFiltered()
{
}

shared_ptr<Token> Lexer::caseToken()
{
}

shared_ptr<Token> Lexer::when()
{
}

shared_ptr<Token> Lexer::defaultToken()
{
}

shared_ptr<Token> Lexer::assignment()
{
}

shared_ptr<Token> Lexer::dot()
{
}

shared_ptr<Token> Lexer::mixin()
{
}

shared_ptr<Token> Lexer::call()
{
}

shared_ptr<Token> Lexer::attrs()
{
}

shared_ptr<Token> Lexer::attributesBlock()
{
}

shared_ptr<Token> Lexer::indent()
{
}

shared_ptr<Token> Lexer::pipelessText()
{
}

shared_ptr<Token> Lexer::colon()
{
    shared_ptr<Token> ret;
    string val = scan("^: *", 0);
    if (!val.empty())
        ret = static_pointer_cast<Token>(make_shared<Colon>(m_nLineno));

    return ret;
}

} // namespace lexer
} // namespace pugcpp
