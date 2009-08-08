#ifndef HALTON_HPP
#define HALTON_HPP

#include <vector>

#include "definitions.h"

#include "Random.hpp"

namespace offboard { namespace maths { namespace rng {


// Halton Quasi-Random sequence
class Halton : public Random
{
	public:
		// Standard Halton - start_n gives the interger to start counting from
		DLLEXPORT Halton( const unsigned long start_n, const unsigned int _dimensions );

		// Return by value here - if we return a class member
		// by reference (and it is stored as such) it's value will change with subsequent calls!
		DLLEXPORT std::vector<double> getUniformVector() const;

		// Debug only function to test Sieve
	    const std::vector<unsigned int>& getPrimes() const { return *primes; }
	private:
		// See Faure.hpp for discussions on use of mutable!
		mutable unsigned int n;
		const unsigned int dimensions;
		// Sieve gives us back a pointer that this class
		// takes ownership of. We don't want the hassle
		// of memory managing its contents so just have it die with the object.
		const std::auto_ptr< const std::vector<unsigned int> > primes;


};

} } } //namespace

#endif //HALTON_HPP

