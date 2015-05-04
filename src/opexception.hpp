#ifndef CLOPTPARSER_OPEXCEPTION_H
#define CLOPTPARSER_OPEXCEPTION_H

#include <iostream>
#include <exception>
#include <stdexcept>

namespace cloptparser {
    class OptionNotFoundException : public std::runtime_error {
    public:
        OptionNotFoundException(std::string name) : std::runtime_error("OptionNotFoundException"), optName(name) {}

        virtual const char *what() const _NOEXCEPT {
            std::string ex = "Option (%optname%) not found";
            size_t start = ex.find("%optname%");
            unsigned long len = std::string("%optname%").length();

            return ex.replace(start, len, optName).c_str();
        }

    private:
        std::string optName;
    };

    class NullOptionProvided : public std::runtime_error {
    public:
        NullOptionProvided() : std::runtime_error("NullOptionProvided") {}
        virtual const char *what() const _NOEXCEPT { return "Attempted to add null option to parser"; }
    };

    class InvalidOptionTypeProvided : public std::runtime_error {
    public:
        InvalidOptionTypeProvided() : std::runtime_error("InvalidOptionTypeProvided") {}
        virtual const char *what() const _NOEXCEPT { return "Unrecognised option type was provided to Option factory"; }
    };
}

#endif //CLOPTPARSER_OPEXCEPTION_H