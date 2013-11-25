
#include "unit.h"

namespace si{
   const double KM = 60;
   const double KH = KM*60.0;
   const double KD = KH*24.0;
   const double KY = KD*365.4;

   namespace time{
      using Second=Unit<Time>;

      constexpr Second operator"" _s(long double s) {return Second(s);}
      constexpr Second operator"" _min(long double min) {return Seconds(s)*KM;}
      constexpr Second operator"" _h(long double hour){return Seconds(s)*KH;}
      constexpr Second operator"" _days(long double days){return Seconds(s)*KD;}
      constexpr Second operator"" _years(long double years){return Seconds(s)*KY;}
   };
};
