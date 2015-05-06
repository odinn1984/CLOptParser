#include "optparser.hpp"

cloptparser::CLOptParser::CLOptParser(int argc, char **argv) : argc(argc), argv(argv) {
    #ifndef DEBUG
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
    #endif
}

cloptparser::CLOptParser::~CLOptParser() {
    delete[] argv;
}

void cloptparser::CLOptParser::addGroup(cloptparser::OptGroup &grp) { this->optGroups.push_back(grp); }

void cloptparser::CLOptParser::addMendatoryOption(cloptparser::Option *opt) {
    if(nullptr == opt)
        throw cloptparser::NullOptionProvided();

    mandatoryOptions.push_back(opt);
}

void cloptparser::CLOptParser::addOption(cloptparser::Option *opt) {
    if(nullptr == opt)
        throw cloptparser::NullOptionProvided();

    this->options.insert(this->options.begin(), opt);
}

void cloptparser::CLOptParser::parse() {
    // Nothing to parse, return without doing anything
    if(0 >= argc)
        return;

    int mandatoryOptionsCount = 0;
    int shortNameOptionsCount = 0;
    int longNameOptionsCount = 0;
    bool parsingError = false;
    std::string errorMsg;

    for(int i=1; i<argc && !parsingError; i++) {
        if(boost::starts_with(argv[i], "--")) {
            // Full name options
            std::string opt = std::string(argv[i]);
            std::string optName = std::string(argv[i]).substr(2, opt.find("=") - 2);
            std::string optValue = std::string(argv[i]).substr(opt.find("=") + 1);

            // TODO: Add special case for flags which don't have values...

            BOOST_LOG_TRIVIAL(debug) << "Long Name Attribute: " <<
                                     optName <<
                                     " Got Value: " << optValue;

            try {
                setValueByName(optName, optValue);
                longNameOptionsCount++;
            } catch(cloptparser::OptionNotFoundException ex) {
                errorMsg = ex.what();
                BOOST_LOG_TRIVIAL(error) << errorMsg;
                parsingError = true;
            }
        } else if(boost::starts_with(argv[i], "-")) {
            // Short name options
            std::string opt = std::string(argv[i]);
            std::string optName = std::string(argv[i]).substr(1, opt.find(" ") - 1);
            std::string optValue = std::string(argv[++i]);

            // TODO: Add special case for flags which don't have values...

            BOOST_LOG_TRIVIAL(debug) << "Short Name Attribute: " <<
                                        optName <<
                                        " Got Value: " << optValue;

            try {
                setValueByName(optName, optValue);
                shortNameOptionsCount++;
            } catch(cloptparser::OptionNotFoundException ex) {
                errorMsg = ex.what();
                BOOST_LOG_TRIVIAL(error) << errorMsg;
                parsingError = true;
            }
        } else {
            if(mandatoryOptionsCount <= mandatoryOptions.size() - 1) {
                mandatoryOptions[mandatoryOptionsCount]->setValue(argv[i]);
                BOOST_LOG_TRIVIAL(debug) << "Mandatory Attribute: " <<
                                            mandatoryOptions[mandatoryOptionsCount]->LongName() <<
                                            " Got Value: " << argv[i];
            }

            mandatoryOptionsCount++;
        }
    }

    if(mandatoryOptionsCount != mandatoryOptions.size() && !parsingError) {
        parsingError = true;
        errorMsg = "Invalid number of mandatory values supplied";
    }

    if(parsingError) {
        std::cerr << "Error: " << errorMsg << std::endl;
        printHelpMessage();
        return;
    }
}

cloptparser::Option *cloptparser::CLOptParser::option(std::string name) {
    for (int i = 0; i < options.size(); i++)
        if(options[i]->LongName() == name || options[i]->ShortName() == name)
            return options[i];

    for (int i = 0; i < optGroups.size(); i++) {
        cloptparser::Option *opt = optGroups[i].find(name);

        if(nullptr != opt)
            return opt;
    }

    return nullptr;
}

void cloptparser::CLOptParser::printHelpMessage() {
    std::cout << "Usage: " << argv[0] << " [OPTIONS]";

    for(int i=0; i<mandatoryOptions.size(); i++)
        std::cout << " " << mandatoryOptions[i]->LongName();

    std::cout << std::endl << std::endl;

    if(0 < options.size()) {
        std::cout << "Options: " << std::endl;

        for(std::vector<cloptparser::Option *>::iterator it = options.begin(); it != options.end(); ++it) {
            std::cout << "\t";
            (*it)->printHelpMessage();
        }

        std::cout << std::endl;
    }

    if(0 < optGroups.size()) {
        for (int i = 0; i < optGroups.size(); i++)
            optGroups[i].printHelp();

        std::cout << std::endl;
    }
}

void cloptparser::CLOptParser::setValueByName(std::string name, std::string value) {
    cloptparser::Option *tempOpt = option(name);

    if(nullptr == tempOpt)
        throw cloptparser::OptionNotFoundException(name);

    tempOpt->setValue(value);
}
