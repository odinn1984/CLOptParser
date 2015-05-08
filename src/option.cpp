#include "option.hpp"

cloptparser::Option *cloptparser::Option::optionFactory(int type) {
    switch(type) {
        case cloptparser::Option::NUM_TYPE:
            return new OptionNumber();
        case cloptparser::Option::STRING_TYPE:
            return new OptionString();
        case cloptparser::Option::FLAG_TYPE:
            return new OptionFlag();
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
bool cloptparser::Option::rValueNeeded() { return true; }

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

/**
 * String Option Class Method Implementations
 */
cloptparser::OptionString::OptionString() {
    defaultValue = "";
    value = defaultValue;
}
cloptparser::OptionString::~OptionString() {}

void cloptparser::OptionString::setValue(std::string val) { value = val; }
void cloptparser::OptionString::setDefaultValue(std::string val) { defaultValue = val; }

boost::any cloptparser::OptionString::_value() { return value; }
boost::any cloptparser::OptionString::_defaultValue() { return defaultValue; }

void cloptparser::OptionString::printHelpMessage() {
    std::string seperator = "";

    if(ShortName() != "" && LongName() != "")
        seperator = ", ";

    std::cout << "-" << ShortName() << " STR"
    << seperator
    << "--" << LongName() << "=STR"
    << "\t\t"
    << HelpMessage()
    << " [DEFAULT: " << DefaultValue<str_option_t>() << "]"
    << std::endl;
}

/**
 * Flag Option Class Method Implementations
 */
cloptparser::OptionFlag::OptionFlag() {
    defaultValue = false;
    value = defaultValue;
}
cloptparser::OptionFlag::~OptionFlag() {}

void cloptparser::OptionFlag::setValue(std::string val) { value = boost::lexical_cast<flag_option_t>(val); }
void cloptparser::OptionFlag::setDefaultValue(std::string val) { defaultValue = boost::lexical_cast<flag_option_t>(val); }
bool cloptparser::OptionFlag::rValueNeeded() { return false; }

boost::any cloptparser::OptionFlag::_value() { return value; }
boost::any cloptparser::OptionFlag::_defaultValue() { return defaultValue; }

void cloptparser::OptionFlag::printHelpMessage() {
    std::string seperator = "";

    if(ShortName() != "" && LongName() != "")
        seperator = ", ";

    std::cout << "-" << ShortName()
    << seperator
    << "--" << LongName()
    << "\t\t"
    << HelpMessage()
    << std::endl;
}

