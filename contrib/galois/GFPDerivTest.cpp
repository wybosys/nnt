/*
  *********************************************************************
  *                                                                   *
  *               Galois Field Arithmetic Library                     *
  * Prototype: Galois Field Polynomial Derivative Test                *
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


/*
   This is a test of the formal derivative capabilities of the GaloisFieldPolynomial
   class. The test is based upon a problem in the book: The Art of Error Correcting
   Coding.

   On page 70 (Non-binary BCH codes: Reed-Solomon) it is assumed the formal derivative
   of the polynomial phi is 1.

   Where phi(x) = 1x^0 + 1x^1 + alpha^5x^2 + 0x^3 + alpha^5x^4

   The code below demonstrates this fact.

*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "GaloisField.h"
#include "GaloisFieldElement.h"
#include "GaloisFieldPolynomial.h"



/*
   p(x) = 1x^4+1x^3+0x^2+0x^1+1x^0
          1    1    0    0    1
*/
unsigned int poly[5] = {1,0,0,1,1};

/*
  A Galois Field of type GF(2^8)
*/

galois::GaloisField galois_field(4,poly);


int main(int argc, char *argv[])
{

   std::cout << "Galois Field: " << std::endl << galois_field << std::endl;

   galois::GaloisFieldElement gfe[5] = {
                                         galois::GaloisFieldElement(&galois_field,galois_field.alpha(1)),
                                         galois::GaloisFieldElement(&galois_field,galois_field.alpha(1)),
                                         galois::GaloisFieldElement(&galois_field,galois_field.alpha(5)),
                                         galois::GaloisFieldElement(&galois_field,                    0),
                                         galois::GaloisFieldElement(&galois_field,galois_field.alpha(5)),
                                       };

   galois::GaloisFieldPolynomial polynomial(&galois_field,4,gfe);


   std::cout << "p(x)  = " << polynomial              << std::endl;
   std::cout << "p'(x) = " << polynomial.derivative() << std::endl;

   exit(EXIT_SUCCESS);
   return true;

}
