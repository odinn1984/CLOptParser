#include "option.hpp"

cloptparser::Option *cloptparser::Option::optionFactory(int type) {
    switch(type) {
        case cloptparser::Option::NUM_TYPE:
            return new OptionNumber();
        case cloptparser::Option::STRING_TYPE:
            break;
        case cloptparser::Option::FLAG_TYPE:
            break;
        default:
            throw cloptparser::InvalidOptionTypeProvided();
    }

    return nullptr;
}

/**
 * Abstract Option Class Method Implementations
 */
void cloptparser::Option::setLongOptionName(std::string name) { longName = name; }
void cloptparser::Option::setShortOptionName(std::string name) { shortName = name; }
void cloptparser::Option::setHelpMessage(std::string message) { helpMessage = message; }

std::string cloptparser::Option::LongName() { return longName; }
std::string cloptparser::Option::ShortName() { return shortName; }
std::string cloptparser::Option::HelpMessage() { return helpMessage; }

/**
 * Decimal Number Option Class Method Implementations
 */
cloptparser::OptionNumber::OptionNumber() {
    defaultValue = 0;
    value = defaultValue;
}

cloptparser::OptionNumber::~OptionNumber() {}

void cloptparser::OptionNumber::setValue(std::string val) { value = boost::lexical_cast<num_option_t>(val); }
void cloptparser::OptionNumber::setDefaultValue(std::string val) { defaultValue = boost::lexical_cast<num_option_t>(val); }

boost::any cloptparser::OptionNumber::_value() { return value; }
boost::any cloptparser::OptionNumber::_defaultValue() { return defaultValue; }

void cloptparser::OptionNumber::printHelpMessage() {
    std::string seperator = "";

    if(ShortName() != "" && LongName() != "")
        seperator = ", ";

    std::cout << "-" << ShortName() << " NUM"
              << seperator
              << "--" << LongName() << "=NUM"
              << "\t\t"
              << HelpMessage()
              << " [DEFAULT: " << DefaultValue<num_option_t>() << "]"
              << std::endl;
}