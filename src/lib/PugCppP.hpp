#pragma once

#include <any>
#include <istream>
#include <memory>
#include <ostream>
#include <string>

#include "expression/IExpressionHandler.hpp"
#include "template/ITemplateLoader.hpp"
#include "template/PugTemplate.hpp"

using namespace std;

namespace pugcpp
{
using namespace parser::node;
using namespace tmpl;
using namespace expression;

class PugCppP
{
  public:
    static shared_ptr<PugTemplate> getTemplate(const string &filename);
    static shared_ptr<PugTemplate> getTemplate(const string &filename, const string &extension);
    static shared_ptr<PugTemplate> getTemplate(istream &reader, const string &name);
    static shared_ptr<PugTemplate> getTemplate(istream &reader, const string &name, const string &extension);
    static string templateToString(PugTemplate &tmpl, map<string, any> *model);

  private:
    static const string encodingUTF8;
    static shared_ptr<PugTemplate> createTemplate(const string &filename,
                                                  shared_ptr<ITemplateLoader> loader,
                                                  shared_ptr<IExpressionHandler> expressionHandler);
};
} // namespace pugcpp