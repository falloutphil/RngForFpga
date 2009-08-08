#include "definitions.h"

namespace offboard { namespace maths { namespace basic {


DLLEXPORT unsigned long long ullPow( const unsigned int base, unsigned int exponent );

// result = (base^exp) % mod
DLLEXPORT unsigned int powAndMod(const unsigned int base, unsigned int exp, const unsigned int mod);


} } } //namespace
