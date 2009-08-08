#ifndef VANDERCORPUT_HPP_
#define VANDERCORPUT_HPP_

#include <vector>

#include "definitions.h"

#include "Halton.hpp"

// Numpty 1D implementation of Halton - is compatible with GSL tho!
class VanDerCorput : protected Halton
{
	public:;
		DLLEXPORT VanDerCorput( const unsigned long start_n );
		DLLEXPORT double getDouble() const;
		DLLEXPORT unsigned int int32() const;

		//GSL Interface
		DLLEXPORT unsigned long int get() const { return int32(); }
		DLLEXPORT double get_double() const { return getDouble(); }
};


#endif /*VANDERCORPUT_HPP_*/
