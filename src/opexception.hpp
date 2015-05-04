#ifndef CLOPTPARSER_OPEXCEPTION_H
#define CLOPTPARSER_OPEXCEPTION_H

#include <iostream>
#include <exception>
#include <stdexcept>

namespace cloptparser {
    class OptionNotFoundException : public std::runtime_error {
    public:
        OptionNotFoundException(std::string name);

        virtual const char *what() const _NOEXCEPT;

    private:
        std::string optName;
    };

    class NullOptionProvided : public std::runtime_error {
    public:
        NullOptionProvided() : std::runtime_error("NullOptionProvided") {}
        virtual const char *what() const _NOEXCEPT {
            return "Attempted to add null option to parser";
        }
    };
}

#endif //CLOPTPARSER_OPEXCEPTION_H