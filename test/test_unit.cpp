/* TEST for Unit class 
 * this is a set of test to prove that we can do
 * what we want to do with our units definition
 */
#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE units test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "quantity.h"

using namespace SI;
//using namespace Quantitys::Literals;
//
Unit<Quantity<1,0,0>> getUnit(double val)
{
   Unit<Quantity<1,0,0>> temp(val);
   return temp;
}

   BOOST_AUTO_TEST_CASE( magnitude_creation ) {
      Unit<Quantity<1,0,0>> test; //empty constructorv
      BOOST_CHECK_EQUAL(test.getVal(),0.0);    
      
      Unit<Quantity<1,0,0>> test1(10);//normal constructor
      BOOST_CHECK_EQUAL(test1.getVal(),10.0);
      
      Unit<Quantity<1,0,0>> test2(test1);//copy constructor
      BOOST_CHECK_EQUAL(test1.getVal(),10.0);
      BOOST_CHECK_EQUAL(test2.getVal(),10.0);

      test = test2;                       //copy assignament
      BOOST_CHECK_EQUAL(test.getVal(),10.0);
      BOOST_CHECK_EQUAL(test2.getVal(),10.0);
      BOOST_CHECK_EQUAL(test.getVal(),test2.getVal());

      Unit<Quantity<1,0,0>> test3(getUnit(2.0)); //move constructor
      BOOST_CHECK_EQUAL(test3.getVal(),2.0);

      BOOST_CHECK_EQUAL(test.getVal(),10.0);
      test = std::move(test3);                     //move assignament
      BOOST_CHECK(test.getVal()!=test3.getVal());
      BOOST_CHECK_EQUAL(test.getVal(),2.0);
      BOOST_CHECK_EQUAL(test3.getVal(),10.0);
   }
   
   BOOST_AUTO_TEST_CASE( basic_operators) {
      Unit<Quantity<1,0,0>> test;
      Unit<Quantity<1,0,0>> i(++test);
      Unit<Quantity<1,0,0>> res(test++);
      BOOST_CHECK_EQUAL(i.getVal(),1.0);
      BOOST_CHECK_EQUAL(res.getVal(),1.0);
      BOOST_CHECK_EQUAL(test.getVal(),2.0);

      i=--test;
      res=test--;
      BOOST_CHECK_EQUAL(i.getVal(),1.0);
      BOOST_CHECK_EQUAL(res.getVal(),1.0);
      BOOST_CHECK_EQUAL(test.getVal(),0.0);

      i=test++;
      res=test++;
      i+=res;
      BOOST_CHECK_EQUAL(i.getVal(),1.0);
      i+=res;
      BOOST_CHECK_EQUAL(i.getVal(),2.0);
      i-=test;
      BOOST_CHECK_EQUAL(i.getVal(),0.0);
   }
   
   BOOST_AUTO_TEST_CASE( operators )
   {
      //using Distance=Quantity<1,0,0>;
      //using Quantity<0,1,0> Weight;
      //using Time=Quantity<0,0,1>;
      using Speed=Quantity<1,0,-1> ;

      Unit<Quantity<1,0,0>> meters(10);
      Unit<Quantity<0,0,1>> seconds(5);
      Unit<Quantity<0,1,0>> kg(100);
      Unit<Quantity<1,0,-1>> velocitiy(0);
      Unit<Quantity<-1,0,0>> imeters(10);
     
      Unit<Distance> res = 2*meters;
     // Unit<Distance> error = meters*meters; //compilation error! OK!
      Unit<Quantity<2,0,0>> surface = meters*meters;
      Unit<Speed> s = meters/seconds;
     // Unit<Quantity<1,0,-2> a = s/seconds;
     // TODO: add compilation flag to check that all the cases that neeed to not compile don't compyle
     // Unit<Distance> error1 = meters+seconds //compilation error! OK!
     Unit<Distance> meters2 = meters;

     // BOOST_CHECK_EQUAL(res.getVal(),20);
     BOOST_CHECK_EQUAL(surface.getVal(),100); //product of magnitudes   
     BOOST_CHECK_EQUAL(s.getVal(),2);
     Unit<Distance> res2 = meters+meters; 
     BOOST_CHECK_EQUAL(res2.getVal(), 20.0); //suma
     BOOST_CHECK_EQUAL(res.getVal(),20.0); //mult by scalar
     res = meters*2;
     BOOST_CHECK_EQUAL(res.getVal(),20.0); //mult by scalar
     res = meters/2;
     BOOST_CHECK_EQUAL(res.getVal(),5.0); //div by scalar
     //res = 2/meters; //compilation error! OK!
     Unit<Quantity<-1,0,0>> ires = 2/meters; //divide a scalar
     BOOST_CHECK_EQUAL(ires == imeters,false);
     BOOST_CHECK_EQUAL(ires.getVal(),0.2);
     res2 = meters-meters;
     BOOST_CHECK_EQUAL(res2.getVal(),0.0); 
     BOOST_CHECK_EQUAL(meters == meters2,true);
     BOOST_CHECK_EQUAL(meters == res2,false);
     BOOST_CHECK_EQUAL(meters != res2,true);
     BOOST_CHECK_EQUAL(meters != meters2, false);
     BOOST_CHECK_EQUAL(meters > res2, true);
     BOOST_CHECK_EQUAL(meters <= meters2,true);
     BOOST_CHECK_EQUAL(res2 < meters,true);
     BOOST_CHECK_EQUAL(meters >= meters2,true);
     //BOOST_CHECK_EQUAL(meters < kg,false); //compilation error!
      std::stringstream ss;
      ss << meters;
      BOOST_CHECK_EQUAL(ss.str(),"10");     
   }      

