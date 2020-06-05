#pragma once

namespace pugcpp
{
class PugCpp
{
private:
    /* data */
public:
    enum Mode {
        HTML,
        XML,
        XHTML
    };
    PugCpp(/* args */);
    ~PugCpp(){}
};
}