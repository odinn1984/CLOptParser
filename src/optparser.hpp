#ifndef CLOPTPARSER_OPTPARSER_H
#define CLOPTPARSER_OPTPARSER_H

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>

#include <boost/any.hpp>
#include <boost/log/trivial.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "option.hpp"
#include "optgroup.hpp"
#include "opexception.hpp"

namespace cloptparser {
    class CLOptParser {
    public:
        CLOptParser(int argc, char **argv);
        virtual ~CLOptParser();

        void addMendatoryOption(Option *opt);
        void addOption(Option *opt);
        void addGroup(OptGroup &grp);
        void parse();

        Option *option(std::string name);

    protected:
        void printHelpMessage();

    private:
        void setValueByName(std::string name, std::string value);

        int argc;
        char **argv;
        std::vector <Option *> mandatoryOptions;
        std::vector<Option *> options;
        std::vector<OptGroup> optGroups;
    };
}

#endif //CLOPTPARSER_OPTPARSER_H
