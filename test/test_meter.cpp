
/* TEST for Unit class 
 * this is a set of test to prove that we can do
 * what we want to do with our units definition
 */
#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE units test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "meter.h"

using namespace si;
using namespace distance;


BOOST_AUTO_TEST_CASE( meter_operations  ) {

   std::cout << " Testing user defined literals for metre" << std::endl;
   BOOST_CHECK_EQUAL(Meter(10),Unit<Distance>(10));
   BOOST_CHECK_EQUAL(Meter(1),1.0_m);
   BOOST_CHECK_EQUAL(Meter(1),1000.0_mm);
   BOOST_CHECK_EQUAL(Meter(1),100.0_cm);
   BOOST_CHECK_EQUAL(Meter(1),10.0_dm);
   BOOST_CHECK_EQUAL(Meter(1),0.1_dam);
   BOOST_CHECK_EQUAL(Meter(1),0.01_hm);
   BOOST_CHECK_EQUAL(Meter(1),0.001_km);
   BOOST_CHECK_EQUAL(INCH,1.0_in);

}
