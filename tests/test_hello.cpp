#include "lib.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_hello)

	BOOST_AUTO_TEST_CASE(test_valid_hello)
{
	    BOOST_CHECK(hello() == "Hello, World!");
}
BOOST_AUTO_TEST_SUITE_END()


