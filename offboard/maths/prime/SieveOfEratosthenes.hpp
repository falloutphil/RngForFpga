// Efficient for calculation the first 10 billion primes.
// Beyond this the 'Sieve of Atkins' or similar should
// be used.
// http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

// May optimize with 'Wheel Factorization'
// http://en.wikipedia.org/wiki/Wheel_factorization

#ifndef SIEVEOFERATOSTHENES_HPP
#define SIEVEOFERATOSTHENES_HPP

#include "definitions.h"

#include <vector>

namespace offboard { namespace maths { namespace prime {

// Note on return types:
// There is a case for returning by value here since we are
// returning a newly created object.  The potential size
// of the returned vector means that heap creation and
// return by pointer was chosen.
// Return by reference may produce nicer semantics, but
// references are aliases to objects and in this case
// they are not aliasing another object - they are
// the sole reference to it!
// Plus returning a pointer strongly suggests to the client
// that they now have ownership and responsible for deleting
// the resource.  Typically client use of a reference does
// not infer ownership and the responsibility of deleting the underlying
// memory is likely to be overlooked.

// Find first N primes
DLLEXPORT std::vector<unsigned int>* FirstNEratosPrimes( const unsigned int numberRequired );
// Find all the primes between 2 and some max value
DLLEXPORT std::vector<unsigned int>* EratosPrimesUpTo( const unsigned int maxValue );
// Next Prime - helper function used in Faure sequence
DLLEXPORT unsigned int NextPrimeGreaterOrEqualTo( const unsigned int number );

} } } //namespace

#endif //SIEVEOFERATOSTHENES_HPP

