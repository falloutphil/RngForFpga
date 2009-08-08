
#include "Mersenne.hpp"
// Interface to original MT code
#include "mt19937ar.h"

namespace offboard { namespace maths { namespace rng {


Mersenne::Mersenne( unsigned long s )
{
	init_genrand(s);
}

double Mersenne::getDouble() const
{
	return genrand_real1();
}

unsigned int Mersenne::int32() const
{
	return genrand_int32();
}

} } } //namespace


