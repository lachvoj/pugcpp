#pragma once

#include "ITemplateLoader.hpp"

namespace pugcpp
{
namespace tmpl
{
class ReaderTemplateLoader
{
  private:
    istream &m_pclReader;
    string m_sName;
    string m_sExtension = "pug";

  public:
    ReaderTemplateLoader(istream &reader, const string &name);
    ReaderTemplateLoader(istream &reader, const string &name, const string &extension);

    long getLastModified(const string &name);
    istream &getReader(const string &name);
    const string &getExtension() const;

  private:
    void checkName(const string &name);
    string getNameWithoutExtension(const string &name);
};

} // namespace tmpl
} // namespace pugcpp