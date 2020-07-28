#include "./ReaderTemplateLoader.hpp"

namespace pugcpp
{
using namespace util;

namespace tmpl
{
ReaderTemplateLoader::ReaderTemplateLoader(istream &reader, const string &name) : reader_(reader), name_(name)
{
}

ReaderTemplateLoader::ReaderTemplateLoader(istream &reader, const string &name, const string &extension)
: reader_(reader), name_(name), extension_(extension)
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
    return reader_;
}

const string &ReaderTemplateLoader::getExtension() const
{
    return extension_;
}

void ReaderTemplateLoader::checkName(const string &name)
{
    string nameOfParamWithoutExtension = getNameWithoutExtension(name);
    string nameOfObjectWithoutExtension = getNameWithoutExtension(name_);
    if (nameOfParamWithoutExtension != nameOfObjectWithoutExtension)
        throw runtime_error(
            "This reader only responds to [" + name_ + "] template. " +
            "You should not reference other templates if using ReaderTemplateLoader, " +
            "because multiple template loaders are currently not supported. " +
            "Maybe you could use a FileTemplateLoader?");
}

string ReaderTemplateLoader::getNameWithoutExtension(const string &name)
{
    string dotExtension = "." + extension_;
    return StringUtils::endsWith(name, dotExtension) ? name.substr(0, name.size() - dotExtension.size()) : name;
}
} // namespace tmpl
} // namespace pugcpp
