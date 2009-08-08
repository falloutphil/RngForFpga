#include <cmath>
#include <vector>
#include <memory>

#include "SieveOfEratosthenes.hpp"

// Helper function to remove common code from Prime methods
std::vector<unsigned int>* EratosSieveToSqrt( const unsigned int maxValue, bool* const sieveMap )
{
	// We'll use a dirty ol' C-style array for this - vectors buy
	// us nothing here and may result in a (very slight) performace drop.
	
	// Note indexes 0 and 1 are uninitalized,
	// we could initialize them to true for
	// clarity, but this comment suffices.

	// Initalize the rest to be potentially prime
	// Note we are ignoring multiples of 2 - in fact we don't
	// even initalize them - urgh! - all in the name of performance
	// again, we *KNOW* we'll never touch these values because
	// all even values (bar 2) can never be prime, so out processing
	// loop NEVER inspects these by design.
	// NOTE: In terms of memory usuage it might be better to 
	// half our array size here.... but it will mean some trickery
	// to get from index->prime.  For current use with small primes
	// the double memory hit is not a concern.
	for ( unsigned int i = 3; i <= maxValue; i+=2 )
		sieveMap[i] = true;

	// Use a vector - to return the values -
	// nice because we can just push back without
	// worrying about how many primes we'll end up with.
	// From a hardcore point of view we could argue that
	// the push back is expensive and could initalize
	// the size at the end and then datafill without
	// pushing back, but testing shows this buys us
	// nothing in performance, so stick with the more
	// maintainable method:
	std::vector<unsigned int>* primes = new std::vector<unsigned int>;
	// Must add 2 as a prime as we factor out multiples of 2 below
	primes->push_back(2);
	
	// Loop over the *initalized* odd values, ignoring
	// the even ones which can never be prime.
	for ( unsigned int i = 3; i <= static_cast<unsigned int>(sqrt(static_cast<double>(maxValue))); i+=2 )
	{
		
		// Number has already been struck off as multiple
		if ( !sieveMap[i] )
			continue;
		
		// Otherwise it is prime - remove
		// its multiples
		for ( unsigned int j = 2*i; j <= maxValue; j+=i )
			sieveMap[j] = false;
		
		// Store the prime
		primes->push_back(i);
	}

	// Return primes so far
	// Client must sieve > sqrt as this is application specific
	return primes;
}



std::vector<unsigned int>* FirstNEratosPrimes( const unsigned int numberRequired )
{
	// Using Prime counting function upper bound
	// nth prime < n * [ ln(n) + ln( ln(n) ) ]  ; n >= 6.

	// http://en.wikipedia.org/wiki/Prime-counting_function#Inequalities 
	// http://en.wikipedia.org/wiki/Prime_number_theorem
	// #  Michele Cipolla (1902). "La determinazione assintotica dell'nimo numero primo". Matematiche Napoli 3: 132-166. 
	// Eric Bach, Jeffrey Shallit (1996). Algorithmic Number Theory 1. MIT Press, 233. ISBN 0-262-02405-5. 

	// However on inspection and by use of the ceil function
	// to round up, we can see that the 4th and 5th primes
	// have an error of < 1 on their calculated boundaries.
	// This allows us to use n >= 4.
	// The reamaining 1st-3rd primes are just given an upper bound
	// of 5, that is the value of the 3rd prime.  Differentiating
	// the upper bound lower than this (1st=2,2nd=3) is not worthwhile.
	const double ln_n = log( static_cast<double>(numberRequired) );
	const unsigned int upperBound = (numberRequired < 4) ? 
		5 : static_cast<unsigned int> ( ceil( numberRequired * ( ln_n + log( ln_n ) ) ) );

 	// The array size, yes, it's 1 too large, but again in the
	// interests of performance we want the loop counter to equal
	// the prime we are interested in, rather than having to
	// do further arithmetic on the index to return the prime it
	// represents (at the cost of memory).  C++ loops start at 0, so we ignore the zero element
	// and make our loop one larger to compensate.
	bool* sieve = new bool[ upperBound + 1 ];
	std::vector<unsigned int>* primes = EratosSieveToSqrt( upperBound, sieve );

	// Now we need to push back the primes remaining
	// in our sieve > sqrt(upperbound)
	unsigned int sqrtBoundary = 1 + static_cast<unsigned int>(sqrt(static_cast<double>(upperBound)));
	// Move to our next odd (thus possibly prime) value
	if ( sqrtBoundary % 2 == 0 )
		++sqrtBoundary;

	for ( unsigned int i = sqrtBoundary; i <= upperBound ; i+=2 )
	{
		if (sieve[i])
		{
			primes->push_back(i);
			// As our upper bound will always produce
			// more primes then we asked for, a break
			// clause will stop the loop when we reach
			// the amount of primes we need
			if (primes->size() == numberRequired)
				break;
		}
	}

	// Free our heaped memory
	delete[] sieve;

	return primes;


}

std::vector<unsigned int>* EratosPrimesUpTo( const unsigned int maxValue )
{	
	// See FirstNEratosPrimes() for relevent comments
	bool* sieve = new bool[ maxValue + 1 ];
	std::vector<unsigned int>* primes = EratosSieveToSqrt( maxValue, sieve );
	
	unsigned int sqrtMaxValue = 1 + static_cast<unsigned int>(sqrt(static_cast<double>(maxValue)));

	if ( sqrtMaxValue % 2 == 0 )
		++sqrtMaxValue;
	for ( unsigned int i = sqrtMaxValue; i <= maxValue ; i+=2 )
		if (sieve[i])
			primes->push_back(i);

	delete[] sieve;

	return primes;
}

// Used by Faure sequence
unsigned int NextPrimeGreaterOrEqualTo( const unsigned int number )
{
	// This is crude for now - but it does the job
	// Use auto_ptrs for both - could just delete the first
	// one here, but as the second one is referenced in return
	// there is no way to kill the memory other than to return
	// the pointer - messy - so let auto_ptr do the work for us
	// Find all the primes upto number
	const std::auto_ptr< const std::vector<unsigned int> > allPrimesUpToNumber( EratosPrimesUpTo( number ) );
	if ( allPrimesUpToNumber->back() == number )
		// If number itself prime, it will be the last entry,
		// just return it
		return number;
	
	// Count number of primes returned, add 1 to this and ask for all these primes back (yuk!)
	const std::auto_ptr< const std::vector<unsigned int> > 
		allPrimesIncludingRequired( FirstNEratosPrimes( allPrimesUpToNumber->size() + 1 ) );
	// Last entry in vector is the one we want!
	return allPrimesIncludingRequired->back();	
}


