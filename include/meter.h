
#include "unit.h"

namespace si{
   const double KMILI=1.0/1000;
   const double KCENTI=1.0/100;
   const double KDECI=1.0/10;
   const double KDECA=10;
   const double KHECTA=100;
   const double KKILO=1000;
   const double KMEGA=1000*KKILO;

   namespace distance{
      using Meter=Unit<Distance>;
      
      //literals to use diferent scales of Meters
     constexpr Meter operator"" _mm(long double x) {return Meter(x)*KMILI;}
     constexpr Meter operator"" _cm(long double x) {return Meter(x)*KCENTI;}
     constexpr Meter operator"" _dm(long double x) {return Meter(x)*KDECI;}
     constexpr Meter operator"" _m(long double x) {return Meter(x);}
     constexpr Meter operator"" _dam(long double x) {return Meter(x)*KDECA;}
    constexpr Meter operator"" _hm(long double x) {return Meter(x)*KHECTA;}
     constexpr Meter operator"" _km(long double x) {return Meter(x)*KKILO;}

      //* scaleTO - returns the value of a Meter in the desired scale
      constexpr double scaleTo(const Meter x, double scale){return x.getVal()*scale;}
      
      //* converts any Unit that quantifies distance to a Meter Unit by the specified
      // conversion factor k_to_metre
      constexpr Meter convertToMeters(Unit<Distance> no_metre,double k_to_metre)
      {
         return Meter(no_metre.getVal()*k_to_metre);
      }

      //Literals to convert from Imperial System
      //
      const Meter INCH = 2.54_cm;
      const Meter FOOT = 0.3048_m;
      const Meter YARD = 0.9144_m;
      const Meter MILE = 1.6093_km;
      const Meter N_MILE = 1.853_km;

     constexpr Meter operator"" _in(long double x) {return Meter(x)*INCH.getVal();}
     constexpr Meter operator"" _ft(long double x) {return Meter(x)*FOOT.getVal();}
     constexpr Meter operator"" _yd(long double x) {return Meter(x)*YARD.getVal();}
     constexpr Meter operator"" _mile(long double x) {return Meter(x)*MILE.getVal();}
     constexpr Meter operator"" _nmile(long double x) {return Meter(x)*N_MILE.getVal();}

   };
};

