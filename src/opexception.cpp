#include "opexception.hpp"

cloptparser::OptionNotFoundException::OptionNotFoundException(std::string name) :
    std::runtime_error("OptionNotFoundException"), optName(name) {}

const char *cloptparser::OptionNotFoundException::what() const _NOEXCEPT {
    std::string ex = "Option (%optname%) not found";
    size_t start = ex.find("%optname%");
    unsigned long len = std::string("%optname%").length();

    return ex.replace(start, len, optName).c_str();
}