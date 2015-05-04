#include "optgroup.hpp"

cloptparser::OptGroup::OptGroup(std::string name) : groupName(name) {}
cloptparser::OptGroup::~OptGroup() {}

void cloptparser::OptGroup::addFromList(const std::vector<cloptparser::Option *> &options) {
    for(int i=0; i<options.size(); i++)
        optList.push_back(options[i]);
}

void cloptparser::OptGroup::add(cloptparser::Option *option) {
    optList.push_back(option);
}

void cloptparser::OptGroup::remove(std::string optName) {
    for(std::vector<Option *>::iterator it = optList.begin(); it != optList.end(); ++it)
        if((*it)->LongName() == optName || (*it)->ShortName() == optName)
            optList.erase(it);
}

void cloptparser::OptGroup::printHelp() {
    std::cout << groupName << ":" << std::endl;

    for(int i=0; i<optList.size(); i++) {
        std::cout << "\t";
        optList[i]->printHelpMessage();
    }

    std::cout << std::endl;
}

cloptparser::Option *cloptparser::OptGroup::find(std::string name) {
    for(std::vector<Option *>::iterator it = optList.begin(); it != optList.end(); ++it)
        if((*it)->LongName() == name || (*it)->ShortName() == name)
            return *it;

    return nullptr;
}
