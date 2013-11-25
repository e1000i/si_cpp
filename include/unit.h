/** Quantity.h
 * This header contains the Quantity definition to use with the robots and
 * ensure consistenci among all the modules.
 *
 * So, all functions that uses real Unit will use instead of double or int
 * or any other general type the Quantitys defined here.
 * The are basecally Speed, Acceleration and Distance.
 *
 * Distance is in Meters and defined literals are 'm', 'cm' and 'mm' all them convert
 * automatically the precedent integer or dobule to meters.
 *
 * To acces the actual value of the Unit use the getVal() function.
 *
 * Implemented all basic math operators so now we can apply * o + to generated classes
 * from template Unit. I will prevent at compilation time from assiganent or comparation errors
 * betwen different Units, even aditions and other operations that causes most of the 
 * programming errors or confusions.
 */

#ifndef QuantityS_H
#define QuantityS_H

#include <iostream>

namespace si{


   template<int L, int M ,int T>struct Quantity{
      //enum{m=M,kg=K,s=S};
   };

   template<typename Quantity>
      class Unit
      {
         public:
            //* constructors 
            explicit constexpr Unit(double d=0.0):val(d){}
           constexpr Unit(const Unit& x):val(x.val){} //copy constructor
           Unit(Unit&& other)
            {
               swap(other); 
            }
            //Assignament operator overload
            Unit& operator=(const Unit& rhs)
            {
               val=rhs.val;
               return *this;
            }

            Unit& operator=(Unit&& rhs)
            {
               swap(rhs);
               return *this;
            }
            //* Basic operators with same types
            Unit& operator+=(const Unit& rhs)
            {
               val+=rhs.val;
               return *this;
            }

            Unit& operator-=(const Unit& rhs)
            {
               val-=rhs.val;
               return *this;
            }

            Unit& operator++()
            {
               ++val;
               return *this;
            }

            Unit operator++(int)
            {
               Unit tmp(*this);
               operator++();
               return tmp;
            }

            Unit& operator--()
            {
               val--;
               return *this;
            }


            Unit operator--(int)
            {
               Unit tmp(*this);
               operator--();
               return tmp;
            }

            //*maniputaltion
            //
            constexpr double getVal() const
            {
               return val;
            }

            void swap(Unit & other)
            {
               using std::swap;
               swap(val, other.val);
            }

            friend std::ostream& operator<<(std::ostream& out, const Unit& m)
            {
               out << m.getVal();
               return out;
            }
            /*operator double()
              {
              return val;
              }*/

         private:
            double val;
      };
   //* Math Operators 
   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
   constexpr   Unit<Quantity<L,M,T>> operator+(const Unit<Quantity<L,M,T>>& lhs, const Unit<Quantity<L,M,T>>& rhs)
      {
         return Unit<Quantity<L,M,T>>(lhs)+=rhs;
      }
   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr Unit<Quantity<M,L,T>> operator-(const Unit<Quantity<M,L,T>>& lhs, const Unit<Quantity<M,L,T>>& rhs)
      {
         return Unit<Quantity<M,L,T>>(lhs)-=rhs;
      }

   template <int M1, int L1, int T1, int M2, int L2, int T2>
    constexpr Unit<Quantity<M1+M2,L1+L2,T1+T2>> operator*(const Unit<Quantity<M1,L1,T1>>& lhs, const Unit<Quantity<M2,L2,T2>>& rhs)
      {
         return Unit<Quantity<M1+M2,L1+L2,T1+T2>>(lhs.getVal()*rhs.getVal());
      }
   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr Unit<Quantity<L,M,T>> operator*(const double& lhs, const Unit<Quantity<L,M,T>>& rhs)
      {
         return Unit<Quantity<L,M,T>>(lhs*rhs.getVal());
      }
   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr Unit<Quantity<L,M,T>> operator*(const Unit<Quantity<L,M,T>>& lhs, const double&rhs)
      {
         return Unit<Quantity<L,M,T>>(lhs.getVal()*rhs);
      }

   template <int M1, int L1, int T1, int M2, int L2, int T2>
     constexpr Unit<Quantity<M1-M2,L1-L2,T1-T2>> operator/(const Unit<Quantity<M1,L1,T1>>& lhs, 
            const Unit<Quantity<M2,L2,T2>>& rhs)
      {
         return Unit<Quantity<M1-M2,L1-L2,T1-T2>>(lhs.getVal()/rhs.getVal());
      }

   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
      constexpr Unit<Quantity<-L, -M, -T>> operator/(double x, const Unit<Quantity<L,M,T>>& rhs)
      {
         return Unit<Quantity<-L,-M,-T>>(x/rhs.getVal());
      }

   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
      Unit<Quantity<L,M,T>> operator/(const Unit<Quantity<L,M,T>>& rhs, double x)
      {
         return Unit<Quantity<L,M,T>>(rhs.getVal()/x);
      }
   //* Logical Operators

   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr  bool operator==(const Unit<Quantity<L,M,T>>& lhs, const Unit<Quantity<L,M,T>>& rhs)
      {
         return (lhs.getVal()==rhs.getVal());
      }

   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr  bool operator!=(const Unit<Quantity<L,M,T>>& lhs, const Unit<Quantity<L,M,T>>& rhs)
      {
         return (lhs.getVal()!=rhs.getVal());
      }

   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr  bool operator<=(const Unit<Quantity<L,M,T>>& lhs, const Unit<Quantity<L,M,T>>& rhs)
      {
         return lhs.getVal()<=rhs.getVal();
      }
   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr  bool operator>=(const Unit<Quantity<L,M,T>>& lhs, const Unit<Quantity<L,M,T>>& rhs)
      {
         return lhs.getVal()>=rhs.getVal();
      }
   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr bool operator< (const Unit<Quantity<L,M,T>>& lhs, const Unit<Quantity<L,M,T>>& rhs)
      {
         return lhs.getVal()<rhs.getVal();
      }
   template <int L, int M, int T, template<int L,int  M,int T> class Quantity>
    constexpr bool operator> (const Unit<Quantity<L,M,T>>& lhs, const Unit<Quantity<L,M,T>>& rhs)
      {
         return lhs.getVal()>rhs.getVal();
      }

   //Defining MKS quantityes: Distance, Mass and Time
   using Distance = Quantity<1,0,0>;
   using Mass = Quantity<0,1,0>;
   using Time = Quantity<0,0,1>;

   using Speed = Quantity<1,0,-1>;
   using Acceleration = Quantity<1,0,-2>;
};
#endif //QuantityS_H
