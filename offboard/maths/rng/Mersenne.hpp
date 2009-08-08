#ifndef MERSENNE_HPP
#define MERSENNE_HPP

#include "Random.hpp"

namespace offboard { namespace maths { namespace rng {

// NRCs Ranq1 RNG as an example
class Mersenne : public Random
{


	public:
		Mersenne( unsigned long s );
		// Logically const
		double getDouble() const;
		unsigned int int32() const;

		//GSL Interface
		unsigned long int get() const { return int32(); }
		double get_double() const { return getDouble(); }

};

} } } // namespace

#endif //MERSENNE_HPP

