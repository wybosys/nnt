#include "GaloisFieldPolynomial.h"

namespace galois
{

   GaloisFieldPolynomial::GaloisFieldPolynomial(GaloisField* _gf)
   {
      gf = _gf;
      poly.clear();
   }


   GaloisFieldPolynomial::GaloisFieldPolynomial(GaloisField* _gf, const unsigned int size, GaloisFieldElement* gfe)
   {
      gf = _gf;
      poly.resize(size + 1);

      if (gfe != NULL)
      {
         for(unsigned int i = 0; i <= size; i++)
         {
            poly[i] = gfe[i];
         }
      }
      else
      {
         for(unsigned int i = 0; i < poly.size(); i++)
         {
            poly[i] = GaloisFieldElement(gf,0);
         }
      }
   }


   GaloisFieldPolynomial::GaloisFieldPolynomial(const GaloisFieldPolynomial& polynomial)
   {
      gf   = polynomial.gf;
      poly = polynomial.poly;
   }


   GaloisFieldPolynomial::GaloisFieldPolynomial(const GaloisFieldElement& gfe)
   {
      gf = gfe.field();
      poly.clear();
      poly.push_back(gfe);
   }


   bool GaloisFieldPolynomial::valid() const
   {
      return (poly.size() > 0);
   }


   unsigned int GaloisFieldPolynomial::deg() const
   {
      return static_cast<unsigned int>(poly.size() - 1);
   }


   GaloisField* GaloisFieldPolynomial::field() const
   {
      return gf;
   }


   void GaloisFieldPolynomial::set_degree(const unsigned int& x)
   {
      poly.resize(x - 1,GaloisFieldElement(gf,0));
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator=(const GaloisFieldPolynomial& polynomial)
   {
      if (this == &polynomial)
        return *this;

      gf   = polynomial.gf;
      poly = polynomial.poly;

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator=(const GaloisFieldElement& gfe)
   {
      poly.clear();
      gf = gfe.field();
      poly.push_back(gfe);
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator+=(const GaloisFieldPolynomial& polynomial)
   {
      if (gf == polynomial.gf)
      {
         if (poly.size() < polynomial.poly.size())
         {
            unsigned int j = 0;
            for (unsigned int i = 0; i < poly.size(); i++)
            {
               poly[i] += polynomial.poly[j++];
            }

            for ( ; j < polynomial.poly.size(); j++)
            {
               poly.push_back(polynomial.poly[j]);
            }
         }
         else
         {
            unsigned int i = 0;
            for (unsigned int j = 0; j < polynomial.poly.size(); j++)
            {
               poly[i++] += polynomial.poly[j];
            }
         }

         simplify(*this);
      }

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator+=(const GaloisFieldElement& gfe)
   {
      poly[0] += gfe;
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator-=(const GaloisFieldPolynomial& gfe)
   {
      return (*this += gfe);
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator-=(const GaloisFieldElement& gfe)
   {
      poly[0] -= gfe;
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator*=(const GaloisFieldPolynomial& polynomial)
   {
      if (gf == polynomial.gf)
      {
         GaloisFieldPolynomial product(gf,deg() + polynomial.deg() + 1);

         for (unsigned int  i= 0; i < poly.size(); i++)
         {
            for (unsigned int j = 0; j < polynomial.poly.size(); j++)
            {
               product.poly[i + j] += poly[i] * polynomial.poly[j];
            }
         }

         simplify(product);
         poly = product.poly;
      }
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator*=(const GaloisFieldElement& gfe)
   {
      if (gf == gfe.field())
      {
         for(unsigned int i = 0; i < poly.size(); i++)
         {
            poly[i] *= gfe;
         }
      }
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator/=(const GaloisFieldPolynomial& divisor)
   {
      if (
          (gf            ==    divisor.gf) &&
          (deg()         >= divisor.deg()) &&
          ((int)divisor.deg() >=             0)
         )
      {
         GaloisFieldPolynomial  quotient(gf, deg() - divisor.deg() + 1);
         GaloisFieldPolynomial remainder(gf, divisor.deg() - 1);

         for(int i = deg(); i >= 0; i--)
         {
            if (i <= (int)quotient.deg())
            {
               quotient[i] = remainder[remainder.deg()] / divisor[divisor.deg()];

               for(int j = remainder.deg(); j > 0; j--)
               {
                  remainder[j] = remainder[j - 1] + (quotient[i] * divisor[j]);
               }

               remainder[0] = poly[i] + (quotient[i] * divisor[0]);
            }
            else
            {
               for(int j = remainder.deg(); j > 0; j--)
               {
                  remainder[j] = remainder[j - 1];
               }
               remainder[0] = poly[i];
            }
         }

         simplify(quotient);

         poly = quotient.poly;
      }

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator/=(const GaloisFieldElement& gfe)
   {
      if (gf == gfe.field())
      {
         for (unsigned int i = 0;  i < poly.size(); i++)
         {
            poly[i] /= gfe;
         }
      }
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator%=(const GaloisFieldPolynomial& divisor)
   {
      if (
          (gf            ==    divisor.gf) &&
          (deg()         >= divisor.deg()) &&
          ((int)divisor.deg() >=             0)
         )
      {
         GaloisFieldPolynomial  quotient(gf, deg() - divisor.deg() + 1);
         GaloisFieldPolynomial remainder(gf, divisor.deg() - 1);

         for(int i = deg(); i >= 0; i--)
         {
            if (i <= (int)quotient.deg())
            {
               quotient[i] = remainder[remainder.deg()] / divisor[divisor.deg()];

               for(int j = remainder.deg(); j > 0; j--)
               {
                  remainder[j] = remainder[j - 1] + (quotient[i] * divisor[j]);
               }

               remainder[0] = poly[i] + (quotient[i] * divisor[0]);
            }
            else
            {
               for(int j = remainder.deg(); j > 0; j--)
               {
                  remainder[j] = remainder[j - 1];
               }
               remainder[0] = poly[i];
            }
         }

         simplify(remainder);
         poly = remainder.poly;
      }

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator%=(const unsigned int& power)
   {
      if (poly.size() >= power)
        poly.resize(power);
      simplify(*this);
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator^=(const int& n)
   {
      GaloisFieldPolynomial result = *this;

      for (int i = 0; i < n; i++)
      {
         result *= *this;
      }

      *this = result;

      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator<<=(const unsigned int& n)
   {
      if (poly.size() > 0)
      {
         std::size_t initial_size = poly.size();
         poly.resize(poly.size() + n, GaloisFieldElement(gf,0));

         for(std::size_t i = initial_size - 1; static_cast<int>(i) >= 0; i--)
         {
            poly[i + n] = poly[i];
         }

         for(unsigned int i = 0; i < n; i++)
         {
            poly[i] = 0;
         }
      }
      return *this;
   }


   GaloisFieldPolynomial& GaloisFieldPolynomial::operator>>=(const unsigned int& n)
   {
      if (n <= poly.size())
      {
         for(unsigned int i = 0;  i <= deg() - n; i++)
         {
            poly[i] = poly[i + n];
         }

         poly.resize(poly.size() - n,GaloisFieldElement(gf,0));
      }
      else if (n >= deg() + 1)
      {
         poly.resize(0,GaloisFieldElement(gf,0));
      }
      return *this;
   }


   const GaloisFieldElement& GaloisFieldPolynomial::operator[](const unsigned int& term) const
   {
      assert(term < poly.size());
      return poly[term];
   }


   GaloisFieldElement& GaloisFieldPolynomial::operator[](const unsigned int& term)
   {
      assert(term < poly.size());
      return poly[term];
   }


   GaloisFieldElement GaloisFieldPolynomial::operator()(const GaloisFieldElement& value)
   {
      GaloisFieldElement result(gf,0);

      if (poly.size() > 0)
      {
         result = poly[poly.size() - 1];
         for(std::size_t i = poly.size() - 2; ((int)i) >= 0; i--)
         {
            result = poly[i] + (result * value);
         }
      }
      return result;
   }


   const GaloisFieldElement GaloisFieldPolynomial::operator()(const GaloisFieldElement& value) const
   {
      GaloisFieldElement result(gf,0);

      if (poly.size() > 0)
      {
         result = poly[poly.size() - 1];
         for(std::size_t i = poly.size() - 2; static_cast<int>(i) >= 0; i--)
         {
            result = poly[i] + (result * value);
         }
      }
      return result;
   }


   GaloisFieldElement GaloisFieldPolynomial::operator()(GFSymbol value)
   {
      return (*this)(GaloisFieldElement(gf,value));
   }


   const GaloisFieldElement GaloisFieldPolynomial::operator()(GFSymbol value) const
   {
      return (*this)(GaloisFieldElement(gf,value));
   }


   bool GaloisFieldPolynomial::operator==(const GaloisFieldPolynomial& polynomial) const
   {
      if (gf == polynomial.gf)
      {
         if (poly.size() != polynomial.poly.size())
           return false;
         else
         {
            for (unsigned int i = 0; i < poly.size(); i++)
            {
               if (poly[i] != polynomial.poly[i])
                 return false;
            }
            return true;
         }
      }
      else
        return false;
   }


   bool GaloisFieldPolynomial::operator!=(const GaloisFieldPolynomial& polynomial) const
   {
      return !(*this == polynomial);
   }


   GaloisFieldPolynomial GaloisFieldPolynomial::derivative()
   {
      if ((*this).poly.size() > 1)
      {
         GaloisFieldPolynomial deriv(gf,deg());
         for (unsigned int i = 0; i < poly.size() - 1; i++)
         {
            if (((i + 1) & 1) == 1)
              deriv.poly[i] = poly[i + 1];
            else
              deriv.poly[i] = 0;
         }
         simplify(deriv);
         return deriv;
      }
      return GaloisFieldPolynomial(gf,0);
   }


   void GaloisFieldPolynomial::simplify()
   {
      simplify(*this);
   }


   void GaloisFieldPolynomial::simplify(GaloisFieldPolynomial& polynomial)
   {
      if (poly.size() > 0)
      {
         std::size_t last = polynomial.poly.size() - 1;

         while(((int)last >= 0) && (polynomial.poly.size() > 0))
         {
            if (polynomial.poly[last] == 0)
              polynomial.poly.pop_back();
            else
              break;

            last = polynomial.poly.size() - 1;
         }
      }
   }


   GaloisFieldPolynomial operator+(const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result += b;
      return result;
   }


   GaloisFieldPolynomial operator + (const GaloisFieldPolynomial& a, const GaloisFieldElement& b)
   {
      GaloisFieldPolynomial result = a;
      result += b;
      return result;
   }


   GaloisFieldPolynomial operator + (const GaloisFieldElement& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = b;
      result += a;
      return result;
   }


   GaloisFieldPolynomial operator + (const GaloisFieldPolynomial& a, const GFSymbol& b)
   {
      return a + GaloisFieldElement(a.field(),b);
   }


   GaloisFieldPolynomial operator + (const GFSymbol& a, const GaloisFieldPolynomial& b)
   {
      return b + GaloisFieldElement(b.field(),a);
   }


   GaloisFieldPolynomial operator - (const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result -= b;
      return result;
   }

   GaloisFieldPolynomial operator - (const GaloisFieldPolynomial& a, const GaloisFieldElement& b)
   {
      GaloisFieldPolynomial result = a;
      result -= b;
      return result;
   }


   GaloisFieldPolynomial operator - (const GaloisFieldElement& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = b;
      result -= a;
      return result;
   }


   GaloisFieldPolynomial operator - (const GaloisFieldPolynomial& a, const GFSymbol& b)
   {
      return a - GaloisFieldElement(a.field(),b);
   }


   GaloisFieldPolynomial operator - (const GFSymbol& a, const GaloisFieldPolynomial& b)
   {
      return b - GaloisFieldElement(b.field(),a);
   }


   GaloisFieldPolynomial operator * (const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result *= b;
      return result;
   }


   GaloisFieldPolynomial operator * (const GaloisFieldElement& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = b;
      result *= a;
      return result;
   }


   GaloisFieldPolynomial operator * (const GaloisFieldPolynomial& a, const GaloisFieldElement& b)
   {
      GaloisFieldPolynomial result = a;
      result *= b;
      return result;
   }

   GaloisFieldPolynomial operator / (const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result /= b;
      return result;
   }


   GaloisFieldPolynomial operator / (const GaloisFieldPolynomial& a, const GaloisFieldElement& b)
   {
      GaloisFieldPolynomial result = a;
      result /= b;
      return result;
   }


   GaloisFieldPolynomial operator % (const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      GaloisFieldPolynomial result = a;
      result %= b;
      return result;
   }

   GaloisFieldPolynomial operator % (const GaloisFieldPolynomial& a, const unsigned int& power)
   {
      GaloisFieldPolynomial result = a;
      result %= power;
      return result;
   }

   GaloisFieldPolynomial operator ^ (const GaloisFieldPolynomial& a, const int& n)
   {
      GaloisFieldPolynomial result = a;
      result ^= n;
      return result;
   }


   GaloisFieldPolynomial operator<<(const GaloisFieldPolynomial& a, const unsigned int& n)
   {
      GaloisFieldPolynomial result = a;
      result <<= n;
      return result;
   }


   GaloisFieldPolynomial operator>>(const GaloisFieldPolynomial& a, const unsigned int& n)
   {
      GaloisFieldPolynomial result = a;
      result >>= n;
      return result;
   }


   GaloisFieldPolynomial gcd(const GaloisFieldPolynomial& a, const GaloisFieldPolynomial& b)
   {
      if ((*a.field()) == (*b.field()))
      {
         if ((!a.valid()) && (!b.valid())) return GaloisFieldPolynomial();
         if (!a.valid()) return b;
         if (!b.valid()) return a;

         GaloisFieldPolynomial x = a % b;
         GaloisFieldPolynomial y = b;
         GaloisFieldPolynomial z = x;

         while ((z = y % x).valid())
         {
            y = x;
            x = z;
         }
         return x;
      }
      else
        return GaloisFieldPolynomial();
   }


   std::ostream& operator << (std::ostream& os, const GaloisFieldPolynomial& polynomial)
   {

      if ((int)polynomial.deg() >= 0)
      {
/*
         for (unsigned int i = 0; i < polynomial.poly.size(); i++)
         {
            os << polynomial.poly[i].index()
               << ((i != (polynomial.deg())) ? " " : "");
         }

         std::cout << " poly form: ";
*/
         for (unsigned int i = 0; i < polynomial.poly.size(); i++)
         {
            os << polynomial.poly[i].poly()
               << " "
               << "x^"
               << i
               << ((i != (polynomial.deg())) ? " + " : "");
         }
      }
      return os;
   }

}
