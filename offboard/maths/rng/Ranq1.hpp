#ifndef RANQ1_HPP
#define RANQ1_HPP

#include "definitions.h"

#include "Random.hpp"

namespace offboard { namespace maths { namespace rng {


// NRCs Ranq1 RNG as an example
class Ranq1 : public Random
{
	public:
		DLLEXPORT Ranq1( const unsigned long long j );
		DLLEXPORT double getDouble() const;

		//GSL Interface
		DLLEXPORT unsigned long int get() const { return int32(); }
		DLLEXPORT double get_double() const { return getDouble(); }
		//unsigned long int and unsigned int are the same
		// - at least the compiler doesn't warn, and this
		// is true on vc8 :-o
		DLLEXPORT unsigned int int32() const;
	private:
		// Implementation detail hidden from client
		// should not stop object constness.
		mutable unsigned long long v;
		unsigned long long int64() const;


};

} } } //namespace

#endif //RANQ1_HPP


