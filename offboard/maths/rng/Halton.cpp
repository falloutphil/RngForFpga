
#include "../prime/SieveOfEratosthenes.hpp"

#include "Halton.hpp"

Halton::Halton( const unsigned long start_n, const unsigned int _dimensions ) :
	                                      n( start_n ),
                                          dimensions( _dimensions ),
                                          primes( FirstNEratosPrimes(_dimensions) )
{

}



std::vector<double> Halton::getUniformVector() const
{
	unsigned long k;
	// b is picked from an array of primes to represent dimensionality
	// i is just out dimension loop counter.
	unsigned int b, i;
	double f, h;

	// Did have this as a mutable class member,
	// however this isn't thread safe - say
	// two threads are passed the same Halton
	// object - they may both update the resultVector
	// at the same time!
	// Cost of copy is always encountered anyway because
	// users could not store the result in a reference
	// because the resultVector could then change
	// even in a single thread scenario, silently
	// modifying the original stored result with
	// the value of the next requested result.
	// I reckon heap allocation is total overkill
	// here given the limitations of Halton when
	// used in more than, say, 15 dimensions, so
	// passing a local back by value is no bad
	// thing here!
	std::vector<double> resultVector( dimensions );

	// We need a U[0,1] for each dimension
	for ( ++n, i=0; i < dimensions; ++i )
	{
		// Divide the sequence by prime b each
		// loop using integer division (DIV)
		// Stop iteration when k=0
		for ( k = n, b=(*primes)[i], f=1., h=0.; (k); k/=b )
		{
			// Raise the factor of our Prime (b) by ^-1
			f /= b;
			// Convert our decimal sequence number to
			// base-b using Divide method.  Luckily
			// this will pop the base-b number out
			// in reverse order to the MSB is raised
			// to the smallest value of k in 1/(b^k)
			// h is a summation of all our MODs multipled
			// by b^-k.
			h += ( k % b ) * f;
		}

		resultVector[i] = h;
	}

	return resultVector;
}



