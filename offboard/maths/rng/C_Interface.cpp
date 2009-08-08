// Pure C Interface to expose the below functions
#include "C_Interface.h"

// Base hpp for all our RNGs for gsl_rng_type factory
#include "Random.hpp"
// List of includes of C++ implementations
// of the returned gsl_rng_types
#include "Ranq1.hpp"
#include "Mersenne.hpp"
#include "Ran.hpp"
#include "VanDerCorput.hpp"
#include "RanVec.hpp"

using namespace offboard::maths::rng;

// Ranq1 class
extern "C" const gsl_rng_type* get_gsl_rng_ranq1()
{
	return getGslRngFromRandomClass<Ranq1>();
}

// Mersenne class
extern "C" const gsl_rng_type* get_gsl_rng_mersenne()
{
	return getGslRngFromRandomClass<Mersenne>();
}

// Ran class
extern "C" const gsl_rng_type* get_gsl_rng_ran()
{
	return getGslRngFromRandomClass<Ran>();
}

// VanDerCorput class
extern "C" const gsl_rng_type* get_gsl_rng_vandercorput()
{
	return getGslRngFromRandomClass<VanDerCorput>();
}

// Simon's Ran Vector class
extern "C" const gsl_rng_type* get_gsl_rng_ranvec()
{
	return getGslRngFromRandomClass<RanVec>();
}
