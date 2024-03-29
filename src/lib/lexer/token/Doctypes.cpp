#include "Doctypes.hpp"

namespace pugcpp
{
namespace lexer
{
namespace token
{
const map<string, string> Doctypes::s_conTypeMap = {
    {"default", "<!DOCTYPE html>"},
    {"xml", "<?xml version=\"1.0\" encoding=\"utf-8\" ?>"},
    {"transitional",
     "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" "
     "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">"},
    {"strict",
     "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" "
     "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">"},
    {"frameset",
     "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Frameset//EN\" "
     "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd\">"},
    {"1.1", "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\" \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">"},
    {"basic",
     "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML Basic 1.1//EN\" "
     "\"http://www.w3.org/TR/xhtml-basic/xhtml-basic11.dtd\">"},
    {"mobile",
     "<!DOCTYPE html PUBLIC \"-//WAPFORUM//DTD XHTML Mobile 1.2//EN\" "
     "\"http://www.openmobilealliance.org/tech/DTD/xhtml-mobile12.dtd\">"}};

const string Doctypes::s_sEmpty = "";

const string &Doctypes::get(const string &pugDocType)
{
    auto elemIt = s_conTypeMap.find(pugDocType);

    if (elemIt == s_conTypeMap.end())
        return s_sEmpty;

    return elemIt->second;
}
} // namespace token
} // namespace lexer
} // namespace pugcpp
