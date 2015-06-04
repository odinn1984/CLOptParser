#include "../../src/optparser.hpp"

#define BOOST_TEST_MODULE OptionsTest
#include <boost/test/included/unit_test.hpp>

using namespace cloptparser;

BOOST_AUTO_TEST_CASE(OptionUpdateDefaultValuesTest) {
    Option *intopt = Option::optionFactory(Option::NUM_TYPE);
    Option *stropt = Option::optionFactory(Option::STRING_TYPE);
    Option *flagopt = Option::optionFactory(Option::FLAG_TYPE);

    BOOST_CHECK_EQUAL(intopt->DefaultValue<num_option_t>(), 0);
    BOOST_CHECK_EQUAL(stropt->DefaultValue<str_option_t>(), "");
    BOOST_CHECK_EQUAL(flagopt->DefaultValue<flag_option_t>(), false);

    intopt->setDefaultValue("5");
    stropt->setDefaultValue("Test");
    flagopt->setDefaultValue("on");

    BOOST_CHECK_EQUAL(intopt->DefaultValue<num_option_t>(), 5);
    BOOST_CHECK_EQUAL(stropt->DefaultValue<str_option_t>(), "Test");
    BOOST_CHECK_EQUAL(flagopt->DefaultValue<flag_option_t>(), true);
}
