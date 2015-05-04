#ifndef _CLOPTPARSER_OPTION_H_
#define _CLOPTPARSER_OPTION_H_

#include <iostream>
#include <iomanip>
#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include "opexception.hpp"

typedef int num_option_t;
typedef std::string str_option_t;
typedef bool flag_option_t;

namespace cloptparser {
    class Option {
    public:
        static const int NUM_TYPE = 0;
        static const int STRING_TYPE = 1;
        static const int FLAG_TYPE = 2;

        static Option *optionFactory(int type);

        virtual void setLongOptionName(std::string name);
        virtual void setShortOptionName(std::string name);
        virtual void setHelpMessage(std::string message);
        virtual void setValue(std::string val) = 0;
        virtual void setDefaultValue(std::string val) = 0;

        virtual std::string LongName();
        virtual std::string ShortName();
        virtual std::string HelpMessage();

        template <typename T> T Value() { return boost::any_cast<T>(_value()); }
        template <typename T> T DefaultValue() { return boost::any_cast<T>(_defaultValue()); }

        virtual void printHelpMessage() = 0;

    protected:
        virtual boost::any _value() = 0;
        virtual boost::any _defaultValue() = 0;

    private:
        std::string shortName;
        std::string longName;
        std::string helpMessage;
    };

    class OptionNumber : public Option {
    public:
        OptionNumber();
        virtual ~OptionNumber();

        virtual void setValue(std::string val);
        virtual void setDefaultValue(std::string val);
        virtual void printHelpMessage();

    protected:
        virtual boost::any _value();
        virtual boost::any _defaultValue();

    private:
        num_option_t value;
        num_option_t defaultValue;
    };
};

#endif //_CLOPTPARSER_OPTION_H_