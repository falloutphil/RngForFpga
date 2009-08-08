#include <ctime>
#include <cmath>

#include <iostream>

#include "../basic/IntegerPowers.hpp"
#include "../rng/mt19937ar.h"

#include "RabinMiller.hpp"


// To Do:  Do that mod 60 test thingy.
// n is the candidate number
bool isPseudoPrime( const unsigned int n, const unsigned int numberOfTests )
{
	// Ignore -ve primes for now.
	// Below algorithm doesn't handle 0 or 1 either so
	// answer here.  Also, no evens are prime, bar 2:
	if ( (n < 2) || (n > 2 && ( (n % 2) == 0 )) )
		return false;

	unsigned int s = n - 1;
	unsigned int r = 0;
	// MT RNG init
	init_genrand( static_cast<unsigned long>(time(NULL)) );

	while (!(s & 1))
	{
		// Divide s by 2
		s >>= 1;
		++r;
	}

	//std::cout << "\nn-1 = " << n-1 << " = 2^r * s = 2^" << r << " * " << s << " = " << ullPow(2,r) * s;
	//
	for ( unsigned int i = 0; i < numberOfTests; ++i )
	{
		// Calculate a^s mod n
		// Generate rand between 1 and n-1 (scaled here from U[0,max(int)]);
		const unsigned int a = ( genrand_int32() % (n-1) ) + 1;
		//std::cout << "\nRandom a=" << a;
		//std::cout <<"\ny = a^s mod n   " << a << "^" << s << " mod " << n;
		unsigned int y = powAndMod( a, s, n ); //ullPow( a, s ) % n;
		//std::cout <<"\ny = " << y;
		if ( y == 1 )
			continue;


		unsigned int j=0;
		do
		{
			// First time can use above y calculation
			// for a^(2^0 * s) = a^s
			if ( y == (n - 1) )
				break;

			++j;
			//y = ullPow( a, ullPow( 2, j ) * s ) % n;
			// Note: y = y^2 mod n is identical (and quicker than) y=a^((2^j)*2) mod n
			y = powAndMod( y, 2, n ); //ullPow( y, 2 ) % n;
			//std::cout <<"\ny = a^(2^j * s) mod n   " << a << "^(2^" << j << " * "<< s << ")"  << " mod " << n;
			//std::cout <<"\ny = " << y;
		}
		while( j < r );

		//std::cout << "\ny=" << y << " j=" << j << " r=" << r << " ";
		if ( j == r )
			// if y never = n - 1, it is composite
			return false;
	}

	return true;

}

