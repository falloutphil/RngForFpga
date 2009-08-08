/*
 * Factorial.cpp
 *
 *  Created on: Jul 7, 2008
 *      Author: philipbeadling
 */

#include "Factorial.hpp"

namespace offboard { namespace maths { namespace basic {


unsigned int Factorial(unsigned int n)
{
	unsigned int result = 1;
	while (n > 1)
		result *= n--;
	return result;
}

unsigned int n_P_r( const unsigned int n, const unsigned int r)
{
	return Factorial(n) / ( Factorial(r) * Factorial (n-r) );
}


} } } //namespace
