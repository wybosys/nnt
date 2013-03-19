/*
  *********************************************************************
  *                                                                   *
  *               Galois Field Arithmetic Library                     *
  * Prototype: Polynomial Shift Prototype                             *
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
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "GaloisFieldPolynomial.h"


/*
   p(x) = 1x^8+1x^7+0x^6+0x^5+0x^4+0x^3+1x^2+1x^1+1x^0
          1    1    0    0    0    0    1    1    1
*/
unsigned int poly[9] = {1,1,1,0,0,0,0,1,1};


int main(int argc, char *argv[])
{
   galois::GaloisField        galois_field(8,poly);
   galois::GaloisFieldElement galois_field_elements[] = {
                                                         galois::GaloisFieldElement(&galois_field, 1),
                                                         galois::GaloisFieldElement(&galois_field, 2),
                                                         galois::GaloisFieldElement(&galois_field, 3),
                                                         galois::GaloisFieldElement(&galois_field, 4),
                                                         galois::GaloisFieldElement(&galois_field, 5),
                                                         galois::GaloisFieldElement(&galois_field, 6),
                                                         galois::GaloisFieldElement(&galois_field, 7),
                                                         galois::GaloisFieldElement(&galois_field, 8),
                                                         galois::GaloisFieldElement(&galois_field, 9),
                                                         galois::GaloisFieldElement(&galois_field,10)
                                                        };

   galois::GaloisFieldPolynomial polynomial(&galois_field,9,galois_field_elements);

   galois::GaloisFieldElement    x_galois_field_elements[2] = {
                                                               galois::GaloisFieldElement(&galois_field, 0),
                                                               galois::GaloisFieldElement(&galois_field, 1)
                                                              };

   galois::GaloisFieldPolynomial X(&galois_field,1,x_galois_field_elements);


   galois::GaloisFieldElement    x2_galois_field_elements[3] = {
                                                                galois::GaloisFieldElement(&galois_field, 0),
                                                                galois::GaloisFieldElement(&galois_field, 0),
                                                                galois::GaloisFieldElement(&galois_field, 1)
                                                               };
   galois::GaloisFieldPolynomial X_2(&galois_field,2,x2_galois_field_elements);



   assert(((X * X)          / X)     ==          X);
   assert(((polynomial * X) / X)     == polynomial);

   assert(((X_2 * X_2)        / X_2) ==        X_2);
   assert(((polynomial * X_2) / X_2) == polynomial);

   assert((polynomial / X)          == (polynomial >> 1));
   assert((polynomial / (X  << 1))  == (polynomial >> 2));

   assert((polynomial / X_2)        == (polynomial >> 2));
   assert((polynomial / (X_2 << 1)) == (polynomial >> 3));

   exit(EXIT_SUCCESS);
   return true;

}













