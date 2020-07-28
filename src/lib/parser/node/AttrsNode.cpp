#include "../../template/PugTemplate.hpp"

#include "AttrsNode.hpp"

namespace pugcpp
{
namespace parser
{
namespace node
{
const set<string> AttrsNode::selfClosingTags = {"area",
                                                "base",
                                                "br",
                                                "col",
                                                "embed",
                                                "hr",
                                                "img",
                                                "input",
                                                "keygen",
                                                "link",
                                                "menuitem",
                                                "meta",
                                                "param",
                                                "source",
                                                "track",
                                                "wbr"};
AttrsNode::AttrsNode() : AttrsNode(e_AttrsNode)
{
}

AttrsNode::AttrsNode(NodeType type) : Node(type)
{
}

bool AttrsNode::AttrCmp::operator()(const string &lhs, const string &rhs) const
{
    if (lhs == "id")
        return true;

    if (rhs == "id")
        return false;

    return lhs < rhs;
}

string AttrsNode::getAttribute(const string &key)
{
    Attr *attr = getAttributeByName(key);
    if (attr != nullptr)
        return attributeValueToString(attr->getValue());

    return "";
}

Attr *AttrsNode::getAttributeByName(const string &name)
{
    for (auto &item : attributes_)
    {
        if (item.getName() == name)
            return &item;
    }

    return nullptr;
}

void AttrsNode::setAttribute(const string &key, any value, bool escaped)
{
    if (getAttributeByName(key) != nullptr)
        throw Exception("Duplicate attribute '" + key + "' is not allowed.");

    attributes_.emplace(attributes_.end(), key, value, escaped);
}

void AttrsNode::addAttributes(const string &src)
{
    attiributeBlocks_.push_back(src);
}

bool AttrsNode::isSelfClosing()
{
    return selfClosing_;
}

bool AttrsNode::isSelfClosing(PugTemplate &tmplt)
{
    return (!tmplt.isXml() && selfClosingTags.find(name_) != selfClosingTags.end());
}

void AttrsNode::setSelfClosing(bool selfClosing)
{
    selfClosing_ = selfClosing;
}

bool AttrsNode::isTextOnly()
{
    return textOnly_;
}

void AttrsNode::setTextOnly(bool textOnly)
{
    textOnly_ = textOnly;
}

shared_ptr<Node> AttrsNode::getCodeNode()
{
    return codeNode_;
}

void AttrsNode::setCodeNode(shared_ptr<Node> codeNode)
{
    codeNode_ = codeNode;
}

bool AttrsNode::hasCodeNode()
{
    return bool(codeNode_);
}

bool AttrsNode::isTerese(PugTemplate &tmplt)
{
    return (isSelfClosing(tmplt) && tmplt.isTerese());
}

shared_ptr<AttrsNode> AttrsNode::clone()
{
}

string AttrsNode::visitAttributes(PugModel &model, PugTemplate &tmplt)
{
    vector<Attr> newAttributes;

    newAttributes = attributes_;
    if (attiributeBlocks_.size() > 0)
    {
        for (const auto &attributeBlock : attiributeBlocks_)
        {
            any a;
            try
            {
                a = tmplt.getExpressionHandler()->evaluateExpression(attributeBlock, model);
            }
            catch (ExpressionException &e)
            {
                e.printStackTrace();
                continue;
            }
            if (map<string, string> *m = any_cast<map<string, string>>(&a))
            {
                for (const auto &item : *m)
                {
                    newAttributes.emplace(newAttributes.end(), item.first, item.second, false);
                }
            }
            // TODO: instance of list
        }
    }
    map<string, unique_ptr<string>, AttrCmp> l_conAttrs;
    attrs(l_conAttrs, model, tmplt, newAttributes);

    return attrsToString(l_conAttrs);
}

string AttrsNode::attrsToString(const map<string, unique_ptr<string>, AttrCmp> &attrs)
{
    ostringstream os;
    for (const auto &entry : attrs)
    {
        os << " ";
        os << entry.first;
        if (entry.second)
        {
            os << '=' << '"';
            os << *(entry.second);
            os << '"';
        }
    }

    return os.str();
}

void AttrsNode::attrs(
    map<string, unique_ptr<string>, AttrCmp> &retAttrs,
    PugModel &model,
    PugTemplate &tmplt,
    vector<Attr> &attrs)
{
    vector<string> classes;
    vector<bool> classEscaping;

    for (auto &attribute : attrs)
    {
        try
        {
            addAttributesToMap(retAttrs, classes, classEscaping, attribute, model, tmplt);
        }
        catch (ExpressionException &e)
        {
            throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
        }
    }
    if (!classes.empty())
    {
        retAttrs["class"] = make_unique<string>(StringUtils::join(classes, " "));
    }
}

void AttrsNode::addAttributesToMap(
    map<string, unique_ptr<string>, AttrCmp> &newAttributes,
    vector<string> &classes,
    vector<bool> classEscaping,
    Attr &attribute,
    PugModel &md,
    PugTemplate &tmplt)
{
    const string &name = attribute.getName();
    bool escaped = attribute.isEscaped();
    unique_ptr<string> value;
    any av = attribute.getValue();
    if ("class" == name)
    {
        if (string *val = any_cast<string>(&av))
        {
            escaped = attribute.isEscaped();
            value = make_unique<string>(getInterpolatedAttributeValue(name, *val, escaped, md, tmplt));
        }
        else if (ExpressionString *val = any_cast<ExpressionString>(&av))
        {
            any expressionValue = evaluateExpression(*val, md, tmplt.getExpressionHandler());
            if (expressionValue.has_value())
            {
                // TODO
            }
        }
        if (StringUtils::isNotBlank(*value))
        {
            classes.push_back(*value);
            classEscaping.push_back(escaped);
        }
        return;
    }
    else if (ExpressionString *val = any_cast<ExpressionString>(&av))
    {
        // TODO
    }
    else if (string *val = any_cast<string>(&av))
    {
        escaped = attribute.isEscaped();
        value = make_unique<string>(getInterpolatedAttributeValue(name, *val, escaped, md, tmplt));
    }
    else if (bool *val = any_cast<bool>(&av))
    {
        if (!(*val))
            return;

        if (!tmplt.isTerese())
            value = make_unique<string>(name);
    }
    newAttributes[name] = move(value);
}

string AttrsNode::attributeValueToString(any value)
{
    if (string *ret = any_cast<string>(&value))
        return *ret;

    if (bool *ret = any_cast<bool>(&value))
        return (*ret) ? "true" : "false";

    if (ExpressionString *ret = any_cast<ExpressionString>(&value))
        return "#{" + ret->getValue() + "}";

    return "";
}

any AttrsNode::evaluateExpression(
    ExpressionString &attribute,
    PugModel &model,
    shared_ptr<IExpressionHandler> expressionHandler)
{
    const string &expression = attribute.getValue();
    any res = expressionHandler->evaluateExpression(expression, model);
    if (ExpressionString *es = any_cast<ExpressionString>(&res))
    {
        return evaluateExpression(*es, model, expressionHandler);
    }

    return res;
}

string AttrsNode::getInterpolatedAttributeValue(
    const string &name,
    const string &attributeValue,
    bool escaped,
    PugModel &model,
    PugTemplate &tmplt)
{
    vector<any> prepared;
    Utils::prepareInterpolate(prepared, attributeValue, escaped);
    try
    {
        return Utils::interpolate(prepared, model, tmplt.getExpressionHandler());
    }
    catch (ExpressionException &e)
    {
        throw PugCompilerException(*this, tmplt.getTemplateLoader(), &e);
    }
}

} // namespace node
} // namespace parser
} // namespace pugcpp