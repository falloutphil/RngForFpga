#ifndef RANVEC_HPP
#define RANVEC_HPP

#include <boost/circular_buffer.hpp>

#include "definitions.h"

#include "Random.hpp"

#define VECLENGTH 64

namespace offboard { namespace maths { namespace rng {

// NRCs Ranq1 RNG as an example
class RanVec : public Random
{
	public:
		DLLEXPORT RanVec( const unsigned long long j );
		DLLEXPORT ~RanVec( );
		DLLEXPORT double getDouble() const;

		//GSL Interface
		DLLEXPORT unsigned long int get() const { return int32(); }
		DLLEXPORT double get_double() const { return getDouble(); }

		//unsigned long int and unsigned int are the same
		// - at least the compiler doesn't warn, and this
		// is true on vc8 :-o
		DLLEXPORT unsigned int int32() const;
	private:
		// u,v and w are implementation details
		// implicit evolving of an object's **private**
		// state should not appear non-const to client

		// u and w are vectorised. No need to vectorise v as this is computation
		// can be combinatorial.
		mutable boost::circular_buffer<unsigned long long> u_pipe,w_pipe;
		mutable unsigned long long u,v,w;
		unsigned long long int64() const;

		unsigned count;


};

} } } //namespace

#endif //RANVEC_HPP

