#include "GaloisField.h"

namespace galois
{


   GaloisField::GaloisField() : power(0), field_size(0)
   {
      alpha_to       = new GFSymbol  [1];
      index_of       = new GFSymbol  [1];
      mul_inverse    = new GFSymbol  [1];
      mul_table      = new GFSymbol *[1];
      div_table      = new GFSymbol *[1];
      exp_table      = new GFSymbol *[1];
      prim_poly_hash = 0;
   }


   GaloisField::GaloisField(const int  pwr, const unsigned int* primitive_poly) : power(pwr), field_size((1 << power)-1)
   {
      alpha_to    = new GFSymbol [field_size + 1];
      index_of    = new GFSymbol [field_size + 1];

      #if !defined(NO_GFLUT)

        mul_table   = new GFSymbol* [(field_size + 1)];
        div_table   = new GFSymbol* [(field_size + 1)];
        exp_table   = new GFSymbol* [(field_size + 1)];
        mul_inverse = new GFSymbol  [(field_size + 1) * 2];

        for (unsigned int i = 0; i < (field_size + 1); i++)
        {
           mul_table[i] = new GFSymbol [(field_size + 1)];
           div_table[i] = new GFSymbol [(field_size + 1)];
           exp_table[i] = new GFSymbol [(field_size + 1)];
        }

      #else

        mul_table   = new GFSymbol *[1];
        div_table   = new GFSymbol *[1];
        exp_table   = new GFSymbol *[1];
        mul_inverse = new GFSymbol  [1];

      #endif

      prim_poly_hash = 0xAAAAAAAA;

      for (unsigned int i = 0; i < power; i++)
      {
         prim_poly_hash += ((i & 1) == 0) ? (  (prim_poly_hash <<  7) ^ primitive_poly[i] ^ (prim_poly_hash >> 3)) :
                                            (~((prim_poly_hash << 11) ^ primitive_poly[i] ^ (prim_poly_hash >> 5)));
      }

      generate_field(primitive_poly);
   }


   GaloisField::GaloisField(const GaloisField& gf)
   {
      power          = gf.power;
      field_size     = gf.field_size;
      prim_poly_hash = gf.prim_poly_hash;
      alpha_to       = new GFSymbol [field_size + 1];
      index_of       = new GFSymbol [field_size + 1];

      memcpy(alpha_to, gf.alpha_to, (field_size + 1) * sizeof(GFSymbol));
      memcpy(index_of, gf.index_of, (field_size + 1) * sizeof(GFSymbol));

      #if !defined(NO_GFLUT)

        mul_table   = new GFSymbol* [(field_size + 1)];
        div_table   = new GFSymbol* [(field_size + 1)];
        exp_table   = new GFSymbol* [(field_size + 1)];
        mul_inverse = new GFSymbol  [(field_size + 1) * 2];

        for (unsigned int i = 0; i < (field_size + 1); i++)
        {
           mul_table[i] = new GFSymbol [(field_size + 1)];
           div_table[i] = new GFSymbol [(field_size + 1)];
           exp_table[i] = new GFSymbol [(field_size + 1)];
        }

        memcpy(mul_inverse, gf.mul_inverse, (field_size + 1) * sizeof(GFSymbol) * 2);

        memcpy(mul_table, gf.mul_table, (field_size + 1) * sizeof(GFSymbol*));
        memcpy(div_table, gf.div_table, (field_size + 1) * sizeof(GFSymbol*));
        memcpy(exp_table, gf.exp_table, (field_size + 1) * sizeof(GFSymbol*));

        for (unsigned int i = 0; i < (field_size + 1); i++)
        {
           memcpy(mul_table[i], gf.mul_table[i], (field_size + 1) * sizeof(GFSymbol));
           memcpy(div_table[i], gf.div_table[i], (field_size + 1) * sizeof(GFSymbol));
           memcpy(exp_table[i], gf.exp_table[i], (field_size + 1) * sizeof(GFSymbol));
        }

      #endif
   }


   GaloisField::~GaloisField()
   {
      if (alpha_to != NULL) delete [] alpha_to;
      if (index_of != NULL) delete [] index_of;

      #if !defined(NO_GFLUT)

        for (unsigned int i = 0; i < (field_size + 1); i++)
        {
           if (mul_table[i] != NULL) delete [] mul_table[i];
           if (div_table[i] != NULL) delete [] div_table[i];
           if (exp_table[i] != NULL) delete [] exp_table[i];
        }

        if (mul_table   != NULL) delete [] mul_table;
        if (div_table   != NULL) delete [] div_table;
        if (exp_table   != NULL) delete [] exp_table;
        if (mul_inverse != NULL) delete [] mul_inverse;

      #endif
   }


   bool GaloisField::operator==(const GaloisField& gf)
   {
      return (
              (this->power          ==          gf.power) &&
              (this->prim_poly_hash == gf.prim_poly_hash)
             ) ;
   }


   GaloisField& GaloisField::operator=(const GaloisField& gf)
   {
      if (this == &gf)
         return *this;

      if (alpha_to != NULL) delete [] alpha_to;
      if (index_of != NULL) delete [] index_of;

      power          = gf.power;
      field_size     = gf.field_size;
      prim_poly_hash = gf.prim_poly_hash;

      memcpy(alpha_to, gf.alpha_to, (field_size + 1) * sizeof(GFSymbol));
      memcpy(index_of, gf.index_of, (field_size + 1) * sizeof(GFSymbol));

      #if !defined(NO_GFLUT)

        if (mul_table   != NULL) delete [] mul_table;
        if (div_table   != NULL) delete [] div_table;
        if (exp_table   != NULL) delete [] exp_table;
        if (mul_inverse != NULL) delete [] mul_inverse;

        mul_table   = new GFSymbol* [(field_size + 1)];
        div_table   = new GFSymbol* [(field_size + 1)];
        exp_table   = new GFSymbol* [(field_size + 1)];
        mul_inverse = new GFSymbol  [(field_size + 1) * 2];

        for (unsigned int i = 0; i < (field_size + 1); i++)
        {
           mul_table[i] = new GFSymbol [(field_size + 1)];
           div_table[i] = new GFSymbol [(field_size + 1)];
           exp_table[i] = new GFSymbol [(field_size + 1)];
        }

        memcpy(mul_inverse, gf.mul_inverse, (field_size + 1) * sizeof(GFSymbol) * 2);

        memcpy(mul_table, gf.mul_table, (field_size + 1) * sizeof(GFSymbol*));
        memcpy(div_table, gf.div_table, (field_size + 1) * sizeof(GFSymbol*));
        memcpy(exp_table, gf.exp_table, (field_size + 1) * sizeof(GFSymbol*));


        for (unsigned int i = 0; i < (field_size + 1); i++)
        {
           memcpy(mul_table[i], gf.mul_table[i], (field_size + 1) * sizeof(GFSymbol));
           memcpy(div_table[i], gf.div_table[i], (field_size + 1) * sizeof(GFSymbol));
           memcpy(exp_table[i], gf.exp_table[i], (field_size + 1) * sizeof(GFSymbol));
        }

      #endif

      return *this;
   }


   void GaloisField::generate_field(const unsigned int* prim_poly)
   {
      /*
         Note: It is assumed that the degree of the primitive
               polynomial will be equivelent to the m value as
               in GF(2^m)
      */

      /*
         need to update using stanford method for prim-poly generation.
      */
      int mask = 1;

      alpha_to[power] = 0;

      for (unsigned int i = 0; i < power; i++)
      {
         alpha_to[i]           = mask;
         index_of[alpha_to[i]] = i;

         if (prim_poly[i] != 0)
         {
            alpha_to[power] ^= mask;
         }

         mask <<= 1;
      }

      index_of[alpha_to[power]] = power;

      mask >>= 1;

      for (unsigned int i = power + 1; i < field_size; i++)
      {
         if (alpha_to[i - 1] >= mask)
           alpha_to[i] = alpha_to[power] ^ ((alpha_to[i - 1] ^ mask) << 1);
         else
           alpha_to[i] = alpha_to[i - 1] << 1;

         index_of[alpha_to[i]] = i;
      }

      index_of[0] = GFERROR;
      alpha_to[field_size] = 1;

      #if !defined(NO_GFLUT)

        for (unsigned int i = 0; i < field_size + 1; i++)
        {
           for (unsigned int j = 0; j < field_size + 1; j++)
           {
              mul_table[i][j] = gen_mul(i,j);
              div_table[i][j] = gen_div(i,j);
              exp_table[i][j] = gen_exp(i,j);
           }
        }

        for (unsigned int i = 0; i < (field_size + 1); i++)
        {
           mul_inverse[i] = gen_inverse(i);
           mul_inverse[i + (field_size + 1)] = mul_inverse[i];
        }

      #endif
   }


   GFSymbol GaloisField::fast_modulus(GFSymbol x)
   {
      while (x >= (int)field_size)
      {
         x -= (int)field_size;
         x  = (x >> power) + (x & (int)field_size);
      }

      return x;
   }


   GFSymbol GaloisField::gen_mul(const GFSymbol& a, const GFSymbol& b)
   {
      if ((a == 0) || (b == 0))
        return 0;
      else
        return alpha_to[fast_modulus(index_of[a] + index_of[b])];
   }


   GFSymbol GaloisField::gen_div(const GFSymbol& a, const GFSymbol& b)
   {
      if ((a == 0) || (b == 0))
        return 0;
      else
        return alpha_to[fast_modulus(index_of[a] - index_of[b] + field_size)];
   }


   GFSymbol GaloisField::gen_exp(const GFSymbol& a, const unsigned int& n)
   {
      if (a != 0)
      {
         if (n == 0)
           return 1;
         else
           return alpha_to[fast_modulus(index_of[a] * n)];
      }
      else
        return 0;
   }


   GFSymbol GaloisField::gen_inverse(const GFSymbol& val)
   {
      return alpha_to[fast_modulus(field_size - index_of[val])];
   }


   std::ostream& operator << (std::ostream& os, const GaloisField& gf)
   {
      for(unsigned int i = 0; i < gf.field_size + 1; i++)
      {
         os << i << "\t" << gf.alpha_to[i] << "\t" << gf.index_of[i] << std::endl;
      }

      return os;
   }

}
