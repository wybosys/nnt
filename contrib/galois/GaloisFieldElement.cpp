#include "GaloisFieldElement.h"

namespace galois
{

   GaloisFieldElement::GaloisFieldElement(GaloisField* _gf, GFSymbol v)
   {
      if (_gf != NULL)
      {
         gf         = _gf;
         poly_value = v & gf->size();
      }
      else
        poly_value = v;
   }


   GaloisFieldElement::GaloisFieldElement(const GaloisFieldElement& gfe)
   {
      gf          = gfe.gf;
      poly_value  = gfe.poly_value;
   }


   std::ostream& operator << (std::ostream& os, const GaloisFieldElement& gfe)
   {
      os << gfe.poly_value;
      return os;
   }


   GaloisFieldElement operator+(const GaloisFieldElement& a, const GaloisFieldElement& b)
   {
      GaloisFieldElement result  = a;
      result += b;
      return result;
   }


   GaloisFieldElement operator-(const GaloisFieldElement& a, const GaloisFieldElement& b)
   {
      GaloisFieldElement result  = a;
      result -= b;
      return result;
   }


   GaloisFieldElement operator*(const GaloisFieldElement& a, const GaloisFieldElement& b)
   {
      GaloisFieldElement result  = a;
      result *= b;
      return result;
   }


   GaloisFieldElement operator*(const GaloisFieldElement& a, const GFSymbol& b)
   {
      GaloisFieldElement result  = a;
      result *= b;
      return result;
   }


   GaloisFieldElement operator*(const GFSymbol& a, const GaloisFieldElement& b)
   {
      GaloisFieldElement result  = b;
      result *= a;
      return result;
   }


   GaloisFieldElement operator/(const GaloisFieldElement& a, const GaloisFieldElement& b)
   {
      GaloisFieldElement result  = a;
      result /= b;
      return result;
   }


   GaloisFieldElement operator^(const GaloisFieldElement& a, const int& b)
   {
      GaloisFieldElement result  = a;
      result ^= b;
      return result;
   }

}
