#ifndef CLOPTPARSER_OPTGROUP_H
#define CLOPTPARSER_OPTGROUP_H

#include <iostream>
#include <map>
#include <vector>
#include <boost/any.hpp>
#include <boost/log/trivial.hpp>

#include "option.hpp"

namespace cloptparser {
    class OptGroup {
    public:
        OptGroup(std::string groupName);
        virtual ~OptGroup();

        void addFromList(const std::vector<cloptparser::Option *> &options);
        void add(cloptparser::Option *option);
        void remove(std::string optName);
        void printHelp();
        cloptparser::Option *find(std::string name);

    private:
        std::string groupName;
        std::vector<cloptparser::Option *> optList;
    };
}


#endif //CLOPTPARSER_OPTGROUP_H
