/*
  *********************************************************************
  *                                                                   *
  *               Galois Field Arithmetic Library                     *
  * Prototype: Galois Field Prototype                                 *
  * Version: 0.0.1                                                    *
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


#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "GaloisFieldPolynomial.h"


/*
   p(x) = 1x^8+1x^7+0x^6+0x^5+0x^4+0x^3+1x^2+1x^1+1x^0
          1    1    0    0    0    0    1    1    1
*/
unsigned int poly[9] = {1,1,1,0,0,0,0,1,1};

/*
  A Galois Field of type GF(2^8)
*/

galois::GaloisField gf(8,poly);

galois::GaloisFieldElement gfe[10] = {
                                      galois::GaloisFieldElement(&gf, 1),
                                      galois::GaloisFieldElement(&gf, 2),
                                      galois::GaloisFieldElement(&gf, 3),
                                      galois::GaloisFieldElement(&gf, 4),
                                      galois::GaloisFieldElement(&gf, 5),
                                      galois::GaloisFieldElement(&gf, 6),
                                      galois::GaloisFieldElement(&gf, 7),
                                      galois::GaloisFieldElement(&gf, 8),
                                      galois::GaloisFieldElement(&gf, 9),
                                      galois::GaloisFieldElement(&gf,10)
                                     };

galois::GaloisFieldElement gfe2[6] = {
                                      galois::GaloisFieldElement(&gf, 6),
                                      galois::GaloisFieldElement(&gf, 5),
                                      galois::GaloisFieldElement(&gf, 4),
                                      galois::GaloisFieldElement(&gf, 3),
                                      galois::GaloisFieldElement(&gf, 2),
                                      galois::GaloisFieldElement(&gf, 1)
                                     };

galois::GaloisFieldElement gfe3[5] = {
                                      galois::GaloisFieldElement(&gf, 13),
                                      galois::GaloisFieldElement(&gf, 11),
                                      galois::GaloisFieldElement(&gf,  7),
                                      galois::GaloisFieldElement(&gf,  3),
                                      galois::GaloisFieldElement(&gf,  2)
                                     };


galois::GaloisFieldElement gfez[3] = {
                                      galois::GaloisFieldElement(&gf, 0),
                                      galois::GaloisFieldElement(&gf, 0),
                                      galois::GaloisFieldElement(&gf, 1)
                                     };


bool addsub_test()
{

   galois::GaloisFieldPolynomial gfp1(&gf,9,gfe);
   galois::GaloisFieldPolynomial gfp2(&gf,5,gfe2);
   galois::GaloisFieldPolynomial gfp3(&gf,0);

   gfp3 = gfp1 + gfp2;
   gfp3 = gfp3 - gfp2;

   if (gfp1 != gfp3)
   {
      std::cout << "Add-Sub ERROR!"   << std::endl;
      std::cout << "gfp1(x) " << gfp1 << std::endl;
      std::cout << "gfp2(x) " << gfp2 << std::endl;
      std::cout << "gfp3(x) " << gfp3 << std::endl;
      return false;
   }

   return true;
}

bool muldiv_test()
{
   galois::GaloisFieldPolynomial gfp1(&gf,9,gfe);
   galois::GaloisFieldPolynomial gfp2(&gf,5,gfe2);
   galois::GaloisFieldPolynomial gfp3(&gf,0);

   gfp3 = gfp1 * gfp2;
   gfp3 = gfp3 / gfp2;

   if (gfp1 != gfp3)
   {
      std::cout << "Mul-Div ERROR!"   << std::endl;
      std::cout << "gfp1(x) " << gfp1 << std::endl;
      std::cout << "gfp2(x) " << gfp2 << std::endl;
      std::cout << "gfp3(x) " << gfp3 << std::endl;
      return false;
   }

   return true;

}


bool divmod_test()
{
   galois::GaloisFieldPolynomial gfp1(&gf,9,gfe);
   galois::GaloisFieldPolynomial gfp2(&gf,5,gfe2);
   galois::GaloisFieldPolynomial gfp3(&gf,4,gfe3);
   galois::GaloisFieldPolynomial gfp4(&gf,0);

   gfp4 = (gfp1 * gfp2) + gfp3;

   if(
      (gfp4 % gfp1 != gfp3) ||
      (gfp4 % gfp2 != gfp3)
     )
   {
      std::cout << "Div-Mod ERROR!"   << std::endl;
      std::cout << "gfp1(x) " << gfp1 << std::endl;
      std::cout << "gfp2(x) " << gfp2 << std::endl;
      std::cout << "gfp3(x) " << gfp3 << std::endl;
      std::cout << "gfp4(x) " << gfp3 << std::endl;
      return false;
   }

   return true;

}


bool mod_zmodetest()
{
   galois::GaloisFieldPolynomial gfp1(&gf,9,gfe);
   galois::GaloisFieldPolynomial gfp2(&gf,2,gfez); // p(x) = x^2

   if((gfp1 % gfp2) != (gfp1 % 2))
   {
      std::cout << "Mod-ZMod ERROR!" << std::endl;
      std::cout << "gfp1(x) " << gfp1 << std::endl;
      std::cout << "gfp2(x) " << gfp2 << std::endl;
      return false;
   }

   return true;

}


bool exp_test()
{
   galois::GaloisFieldPolynomial gfp1(&gf,9,gfe);
   galois::GaloisFieldPolynomial gfp2(&gf,0);

   gfp2 = gfp1 ^ 10;

   for (unsigned int i = 0; i < 10; i++)
   {
      gfp2 = gfp2 / gfp1;
   }

   if(gfp2 != gfp1)
   {
      std::cout << "Exponentiation ERROR!" << std::endl;
      std::cout << "gfp1(x) " << gfp1 << std::endl;
      std::cout << "gfp2(x) " << gfp2 << std::endl;
      return false;
   }

   return true;

}


bool shiftleft_test()
{

   galois::GaloisFieldPolynomial gfp1(&gf,9,gfe);
   galois::GaloisFieldPolynomial gfp2(&gf,0);

   gfp2 = gfp1 << 10;
   gfp2 = gfp2 >> 10;

   if(gfp2 != gfp1)
   {
      std::cout << "Shift Left ERROR!" << std::endl;
      std::cout << "gfp1(x) " << gfp1 << std::endl;
      std::cout << "gfp2(x) " << gfp2 << std::endl;
      return false;
   }

   return true;

}


int main(int argc, char *argv[])
{

   unsigned int MAX = 25500;

   for(unsigned int  i = 0; i < MAX; i++)
   {

      if (!addsub_test())
        break;

      if (!muldiv_test())
        break;

      if (!divmod_test())
        break;

      if (!mod_zmodetest())
        break;

      if (!exp_test())
        break;

      if (!shiftleft_test())
        break;

      if (i % 100 == 0)
       std::cout << i << " times" << std::endl;


   }

   exit(EXIT_SUCCESS);
   return true;

}

