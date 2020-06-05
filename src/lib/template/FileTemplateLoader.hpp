#pragma once

#include "ITemplateLoader.hpp"

namespace tmpl
{
class FileTemplateLoader : public ITemplateLoader
{
  private:
    string encoding_ = "UTF-8";
    string folderPath_ = "";
    string extension_ = "pug";

    void validateFolderPath(const string &folderPath);

  public:
    FileTemplateLoader(const string &folderPath, const string &encoding);
    FileTemplateLoader(const string &folderPath, const string &encoding, const string &extension);
    ~FileTemplateLoader();

    long getLastModified(const string &name);
    ifstream getReader(const string &name);
    const string &getExtension() const;
};
} // namespace tmpl
