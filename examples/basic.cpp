#include <iostream>
#include <vector>
#include "../src/optparser.hpp"

using namespace std;
using namespace cloptparser;

int main(int argc, char **argv) {
    Option *a = Option::optionFactory(Option::NUM_TYPE);
    Option *b = Option::optionFactory(Option::NUM_TYPE);
    Option *c = Option::optionFactory(Option::NUM_TYPE);
    OptGroup *g = new OptGroup("General Options");

    a->setValue("5");
    a->setDefaultValue("2");
    a->setLongOptionName("num_threads");
    a->setShortOptionName("nt");
    a->setHelpMessage("Set the number of threads");

    b->setValue("2");
    b->setDefaultValue("1");
    b->setLongOptionName("num_procs");
    b->setShortOptionName("np");
    b->setHelpMessage("Set the number of processes");

    c->setDefaultValue("1");
    c->setLongOptionName("DEST");
    c->setShortOptionName("m");
    c->setHelpMessage("Destionation of the pokemon");

    vector<Option *> ol;

    ol.push_back(a);
    ol.push_back(b);

    g->addFromList(ol);

    CLOptParser *p = new CLOptParser(argc, argv);
    p->addGroup(*g);
    p->addMendatoryOption(c);
    p->addOption(b);
    p->parse();

    cout << "Current number of threads: " << a->Value<num_option_t>() << endl;
    cout << "Current number of procs: " << b->Value<num_option_t>() << endl;
    cout << "Current mandatory: " << c->Value<num_option_t>() << endl;

    return 0;
}