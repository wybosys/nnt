/*
  *********************************************************************
  *                                                                   *
  *               Galois Field Arithmetic Library                     *
  * Prototype: Galois Field LUT Test                                  *
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
#include <stdlib.h>
#include <stdio.h>
#include "GaloisField.h"


/*
   p(x) = 1x^8+1x^7+0x^6+0x^5+0x^4+0x^3+1x^2+1x^1+1x^0
          1    1    0    0    0    0    1    1    1
*/
unsigned int poly[9] = {1,1,1,0,0,0,0,1,1};

/*
  A Galois Field of type GF(2^8)
*/

galois::GaloisField gf(8,poly);


int main(int argc, char *argv[])
{


   for (unsigned int k = 0; k < 10000; k++)
   {
      for (unsigned int i = 0; i < 256; i++)
      {
         for (unsigned int j = 0; j < 256; j++)
         {
            galois::GFSymbol symb;
            symb = gf.mul(i,j);
            symb = gf.div(i,j);
            symb = gf.exp(i,j);
         }
      }
   }

   exit(EXIT_SUCCESS);
   return true;

}

