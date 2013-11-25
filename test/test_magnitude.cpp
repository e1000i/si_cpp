/* TEST for magnitude 
 * this is a set of test to prove that we can do
 * what we want to do with our units definition
 */
#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE units test
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "magnitude.h"

using namespace Units;
//using namespace Units::Literals;
//
Magnitude<Unit<1,0,0>> getMagnitude(double val)
{
   Magnitude<Unit<1,0,0>> temp(val);
   return temp;
}

   BOOST_AUTO_TEST_CASE( magnitude_creation ) {
      Magnitude<Unit<1,0,0>> test; //empty constructorv
      BOOST_CHECK_EQUAL(test.getVal(),0.0);    
      
      Magnitude<Unit<1,0,0>> test1(10);//normal constructor
      BOOST_CHECK_EQUAL(test1.getVal(),10.0);
      
      Magnitude<Unit<1,0,0>> test2(test1);//copy constructor
      BOOST_CHECK_EQUAL(test1.getVal(),10.0);
      BOOST_CHECK_EQUAL(test2.getVal(),10.0);

      test = test2;                       //copy assignament
      BOOST_CHECK_EQUAL(test.getVal(),10.0);
      BOOST_CHECK_EQUAL(test2.getVal(),10.0);
      BOOST_CHECK_EQUAL(test.getVal(),test2.getVal());

      Magnitude<Unit<1,0,0>> test3(getMagnitude(2.0)); //move constructor
      BOOST_CHECK_EQUAL(test3.getVal(),2.0);

      BOOST_CHECK_EQUAL(test.getVal(),10.0);
      test = std::move(test3);                     //move assignament
      BOOST_CHECK(test.getVal()!=test3.getVal());
      BOOST_CHECK_EQUAL(test.getVal(),2.0);
      BOOST_CHECK_EQUAL(test3.getVal(),10.0);
   }
   
   BOOST_AUTO_TEST_CASE( basic_operators) {
      Magnitude<Unit<1,0,0>> test;
      Magnitude<Unit<1,0,0>> i(++test);
      Magnitude<Unit<1,0,0>> res(test++);
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
      using Distance=Unit<1,0,0>;
      //using Unit<0,1,0> Weight;
      using Time=Unit<0,0,1>;
      using Speed=Unit<1,0,-1> ;

      Magnitude<Unit<1,0,0>> meters(10);
      Magnitude<Unit<0,0,1>> seconds(5);
      Magnitude<Unit<0,1,0>> kg(100);
      Magnitude<Unit<1,0,-1>> velocitiy(0);
      Magnitude<Unit<-1,0,0>> imeters(10);
     
      Magnitude<Distance> res = 2*meters;
     // Magnitude<Distance> error = meters*meters; //compilation error! OK!
      Magnitude<Unit<2,0,0>> surface = meters*meters;
      Magnitude<Speed> s = meters/seconds;
     // Magnitude<Unit<1,0,-2> a = s/seconds;
     // TODO: add compilation flag to check that all the cases that neeed to not compile don't compyle
     // Magnitude<Distance> error1 = meters+seconds //compilation error! OK!
     Magnitude<Distance> meters2 = meters;

     // BOOST_CHECK_EQUAL(res.getVal(),20);
     BOOST_CHECK_EQUAL(surface.getVal(),100); //product of magnitudes   
     BOOST_CHECK_EQUAL(s.getVal(),2);
     Magnitude<Distance> res2 = meters+meters; 
     BOOST_CHECK_EQUAL(res2.getVal(), 20.0); //suma
     BOOST_CHECK_EQUAL(res.getVal(),20.0); //mult by scalar
     res = meters*2;
     BOOST_CHECK_EQUAL(res.getVal(),20.0); //mult by scalar
     res = meters/2;
     BOOST_CHECK_EQUAL(res.getVal(),5.0); //div by scalar
     //res = 2/meters; //compilation error! OK!
     Magnitude<Unit<-1,0,0>> ires = 2/meters; //divide a scalar
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


   //   BOOST_CHECK_EQUAL(Speed(2),2.0_m / 1.0_s);
   //   BOOST_CHECK_EQUAL(Acceleration(2),2.0_m / 1.0_s2);
   
   //BOOST_AUTO_TEST_CASE(arithmetics) {
   //   BOOST_CHECK_EQUAL(1.5_m+1.5_m, Meter(3.0));
   //}
 
/*
   using Speed=Magnitude<Unit<1,0,-1>>;
   using Acceleration=Magnitude<Unit<1,0,-2>>;
   using Distance=Magnitude<Unit<1,0,0>>;
   using Distance= Unit<1,0,0>;
   using Second = Unit<0,0,1>;
   using Second2 = Unit<0,0,2>;
   namespace Literals {
      constexpr Value<Second> operator"" _s(long double d)
      {
         return Value<Second>(d);
      }

      constexpr Value<Second2> operator"" _s2(long double d)
      {
         return Value<Second2>(d);
      }

      constexpr Value<Distance> operator"" _m(long double d)
      {
         return Value<Distance>(d);
      }

      constexpr Value<Distance> operator"" _cm(long double d)
      {
         return Value<Distance>(d/100);
      }

      constexpr Value<Distance> operator"" _mm(long double d)
      {
         return Value<Distance>(d/1000);
      }
   };
   */
