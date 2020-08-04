#ifndef FileTemplateLoader_hpp
#define FileTemplateLoader_hpp

#include <fstream>
#include <memory>
#include <stdexcept>

#include "../util/FileSystem.hpp"

#include "ITemplateLoader.hpp"

namespace pugcpp
{
namespace tmpl
{
class FileTemplateLoader : public ITemplateLoader
{
  private:
    string encoding_ = "UTF-8";
    string folderPath_ = "";
    string extension_ = ".pug";

    void validateFolderPath(const string &folderPath);

  public:
    FileTemplateLoader(const string &folderPath, const string &encoding);
    FileTemplateLoader(const string &folderPath, const string &encoding, const string &extension);

    long getLastModified(const string &name);
    unique_ptr<istream> getReader(const string &name);
    const string &getExtension() const;
};
} // namespace tmpl
} // namespace pugcpp
#endif
