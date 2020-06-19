#include "ReaderTemplateLoader.hpp"

#include <stdexcept>

#include "../util/StringUtils.hpp"

namespace pugcpp
{
using namespace util;

namespace tmpl
{
ReaderTemplateLoader::ReaderTemplateLoader(istream &reader, const string &name) : m_pclReader(reader), m_sName(name)
{
}

ReaderTemplateLoader::ReaderTemplateLoader(istream &reader, const string &name, const string &extension)
: m_pclReader(reader), m_sName(name), m_sExtension(extension)
{
}

long ReaderTemplateLoader::getLastModified(const string &name)
{
    checkName(name);
    return -1;
}

istream &ReaderTemplateLoader::getReader(const string &name)
{
    checkName(name);
    return m_pclReader;
}

const string &ReaderTemplateLoader::getExtension() const
{
    return m_sExtension;
}

void ReaderTemplateLoader::checkName(const string &name)
{
    string nameOfParamWithoutExtension = getNameWithoutExtension(name);
    string nameOfObjectWithoutExtension = getNameWithoutExtension(m_sName);
    if (nameOfParamWithoutExtension != nameOfObjectWithoutExtension)
        throw runtime_error("This reader only responds to [" + m_sName + "] template. " +
                            "You should not reference other templates if using ReaderTemplateLoader, " +
                            "because multiple template loaders are currently not supported. " +
                            "Maybe you could use a FileTemplateLoader?");
}

string ReaderTemplateLoader::getNameWithoutExtension(const string &name)
{
    string dotExtension = "." + m_sExtension;
    return StringUtils::endsWith(name, dotExtension) ? name.substr(0, name.size() - dotExtension.size()) : name;
}
} // namespace tmpl
} // namespace pugcpp
