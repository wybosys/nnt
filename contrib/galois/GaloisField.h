/*
  *********************************************************************
  *                                                                   *
  *        Galois Field Arithmetic Library (version 0.0.1)            *
  *                                                                   *
  * Class: Galois Field                                               *
  * Author: Arash Partow - 2000                                       *
  * URL: http://www.partow.net/projects/galois/index.html             *
  *                                                                   *
  * Copyright Notice:                                                 *
  * Free use of this library is permitted under the guidelines and    *
  * in accordance with the most current version of the Common Public  *
  * License.                                                          *
  * http://www.opensource.org/licenses/cpl.php                        *
  *                                                                   *
  *********************************************************************
*/


#ifndef INCLUDE_GALOISFIELD_H
#define INCLUDE_GALOISFIELD_H

#include <iostream>
#include <vector>
#include <string.h>

namespace galois
{


   typedef int      GFSymbol;
   const   GFSymbol GFERROR = -1;

   class GaloisField
   {

      public:

       GaloisField();
       GaloisField(const int  pwr, const unsigned int* primitive_poly);
       GaloisField(const GaloisField& gf);
      ~GaloisField();

       GaloisField& operator=(const GaloisField& gf);
       bool operator==(const GaloisField& gf);


       inline GFSymbol index(const GFSymbol value) const
       {
          return index_of[value];
       }


       inline GFSymbol alpha(const GFSymbol value) const
       {
          return alpha_to[value];
       }


       inline unsigned int size() const
       {
          return field_size;
       }


       inline unsigned int pwr() const
       {
          return power;
       }


       inline GFSymbol add(const GFSymbol& a, const GFSymbol& b)
       {
          return (a ^ b);
       }


       inline GFSymbol sub(const GFSymbol& a, const GFSymbol& b)
       {
          return (a ^ b);
       }


       inline GFSymbol mul(const GFSymbol& a, const GFSymbol& b)
       {
          #if !defined(NO_GFLUT)
            return mul_table[a][b];
          #else
            if ((a == 0) || (b == 0))
              return 0;
            else
              return alpha_to[fast_modulus(index_of[a] + index_of[b])];
          #endif
       }


       inline GFSymbol div(const GFSymbol& a, const GFSymbol& b)
       {
          #if !defined(NO_GFLUT)
            return div_table[a][b];
          #else
            if ((a == 0) || (b == 0))
              return 0;
            else
              return alpha_to[fast_modulus(index_of[a] - index_of[b] + field_size)];
          #endif
       }


       inline GFSymbol exp(const GFSymbol& a, const int& n)
       {
          #if !defined(NO_GFLUT)
            if (n < 0)
            {
               int b = n;
                while(b < 0) b += field_size;// b could be negative

               if (b == 0)
                 return 1;
               return exp_table[a][b];
            }
            else
              return exp_table[a][n & field_size];
          #else
            if (a != 0)
            {
               if (n < 0)
               {
                  int b = n;
                  while(b < 0) b += field_size;// b could be negative
                  if (b == 0)
                    return 1;
                  return alpha_to[fast_modulus(index_of[a] * b)];
               }
               else if (n == 0)
                 return 1;
               else
                 return alpha_to[fast_modulus(index_of[a] * n)];
            }
            else
              return 0;
          #endif
       }


       inline GFSymbol inverse(const GFSymbol& val)
       {
          #if !defined(NO_GFLUT)
            return mul_inverse[val];
          #else
            return alpha_to[fast_modulus(field_size - index_of[val])];
          #endif
       }


       friend std::ostream& operator << (std::ostream& os, const GaloisField& gf);


      private:

       void     generate_field(const unsigned int* prim_poly);
       GFSymbol fast_modulus  (GFSymbol                    x);
       GFSymbol gen_mul       (const GFSymbol& a, const GFSymbol&     b);
       GFSymbol gen_div       (const GFSymbol& a, const GFSymbol&     b);
       GFSymbol gen_exp       (const GFSymbol& a, const unsigned int& n);
       GFSymbol gen_inverse   (const GFSymbol& val);

      private:

       unsigned int              power;
       unsigned int              field_size;
       unsigned int              prim_poly_hash;
       GFSymbol*                 alpha_to;    // aka exponential or anti-log
       GFSymbol*                 index_of;    // aka log
       GFSymbol*                 mul_inverse; // multiplicative inverse
       GFSymbol**                mul_table;
       GFSymbol**                div_table;
       GFSymbol**                exp_table;

   };


}

#endif
