#ifndef RAN_HPP
#define RAN_HPP

#include "definitions.h"

#include "Random.hpp"

// NRCs Ranq1 RNG as an example
class Ran : public Random
{
	public:
		DLLEXPORT Ran( const unsigned long long j );
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
		mutable unsigned long long u,v,w;
		unsigned long long int64() const;


};

#endif //RAN_HPP

