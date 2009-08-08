#ifndef FAURE_HPP_
#define FAURE_HPP_

#include <vector>

#include "definitions.h"

#include "Random.hpp"

namespace offboard { namespace maths { namespace rng {

// Faure Quasi-Random sequence
class Faure : public Random
{
	public:
		DLLEXPORT Faure( const unsigned long start_n, const unsigned int _dimensions );
		// Note: not bitwise-const, but logically const
		DLLEXPORT std::vector<double> getUniformVector() const;

	private:
		// Client should be able to have a const Faure
		// without worrying about the fact that under
		// the covers internal states are changing.
		// Even with these values changing the object
		// will appear const to the client (that is
		// the client cannot directly modify any data
		// which affects the nature of the sequence).
		// This is a philosophical point - as some users
		// who understand the likely implementation
		// of the interface might expect the object state
		// to change by requesting a uniform vector -
		// perhaps those users are thinking too hard!
		// The clincher for me is that if we pass const
		// referances to this class around, we need to be
		// able to call 'get' functions on them to make
		// them useful - and this overrules client quibble.
		// Of course if we had a set_n() function this would
		// not be const, as the client is explicitly requesting
		// a change to the object state, rather than implying
		// one due to the nature of the algorithm.  Feel
		// free to argue this with me if you disagree!
		const unsigned int base;
		mutable unsigned int n;
		const unsigned int dimensions;
		// Again these are internal variables
		// NOTE: They are stateless, declaring them
		// here just means there is only one alloc/dealloc
		// per object.
		mutable unsigned int k, m, myC_k;
		mutable double myRandom, primePower;
};

} } } // namespace

#endif /*FAURE_HPP_*/
