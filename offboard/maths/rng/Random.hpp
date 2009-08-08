#ifndef RANDOM_HPP
#define RANDOM_HPP

// Top level interface class for all C++ RNGs
// and a factory to produce generic gsl_rng_type
// for any specialisation of this class.

#include <limits>
#include <typeinfo>
#include <string>
#include <new>

#include <gsl/gsl_rng.h>

namespace offboard { namespace maths { namespace rng {

class Random
{
	public:
		virtual ~Random() {};
		//virtual double getDouble() = 0;
	protected:
		Random() {};

};

// This is the 'meat' of the CPP interface INTO GSL.
// GSL gives us some raw memory to store the 'state'
// of our RNG in.  We just stick our C++ RNG
// object in here and typecast it back from
// GSL's void* every time the GSL interface
// requests an action from our RNG.  We
// can then call the object's internal functions
// which will do the job.

// Would be nice to put all these templates into
// one templated structure, but then they would be
// 'member functions' and C cannot accept pointers
// to member functions (they are not the same
// as function pointers).
// Note that obviously C can't handle templates
// either, but it doesn't have to, as templates
// are resolved at COMPILE time.

// First we define all the functions we will
// need for our rng_gsl_type structure.
// Finally we define a factory that will
// create the in a nice generic way.

// **** Functions needed by gsl_rng_type ****

template<class MY_RNG_CLASS>
void rngSet( void* mem, unsigned long int seed )
{
	//GSL has already malloc'd us memory of size MY_RNG_CLASS,
	//so we use 'placement new' to contruct our class inside this memory.
	//GSL refers to this memory as gsl_rng->state.
	//We just let out reference myRng die at the end of the function,
	//but don't worry, GSL will clean up for us and we will be passed
	//back the same peice of memory with every subsequent call.

	/* MY_RNG_CLASS* myRng = */ (void) new (mem) MY_RNG_CLASS(seed);
}

// Helper function to typecast the void state from
// GSL into a C++ Random class
template<class MY_RNG_CLASS>
MY_RNG_CLASS* recastVoidStateFromGsl( void* voidRngClass )
{
	return static_cast<MY_RNG_CLASS*> ( voidRngClass );
}

// Functions that pass back to GSL new random
// number upon request.
template<class MY_RNG_CLASS>
unsigned long int rngGet( void* voidRngClass )
{
	return recastVoidStateFromGsl<MY_RNG_CLASS>( voidRngClass )->get();
}

template<class MY_RNG_CLASS>
double rngGet_double( void* voidRngClass )
{
	return recastVoidStateFromGsl<MY_RNG_CLASS>( voidRngClass )->get_double();
}


// **** GSL rng_type factory ****
// Uses the definitions above to create
// a usuable gsl_rng_type structure specific
// to the template parameter class-type.
template<class MY_RNG_CLASS>
const gsl_rng_type* getGslRngFromRandomClass()
{
	// As we only need 1 rng *type* per class
	// We *should* just be able to create this
	// once (per template type, in effect) and
	// from then on return a reference to it whenever
	// asked.  This way C++ cleans up for us!

	// Handle GCC's typeinfo with strpbrk (see Google)
	static const std::string rngName = std::string("C++ - ").append(
                	strpbrk( typeid(MY_RNG_CLASS).name(),
                        	 "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUV WXYZ" )
                );

	// The actual struct we pass to GSL
	static const gsl_rng_type gsl_rng_myRandomType =
	{
		rngName.c_str(),
		//GSL can't use our 64-bit implementation max
		//is that returned by our int32()
		std::numeric_limits<unsigned int>::max(),
		0,
		sizeof(MY_RNG_CLASS),
		&rngSet<MY_RNG_CLASS>,
		&rngGet<MY_RNG_CLASS>,
		&rngGet_double<MY_RNG_CLASS>
	};
	return &gsl_rng_myRandomType;
}

} } } //namespace

#endif //RANDOM_HPP





