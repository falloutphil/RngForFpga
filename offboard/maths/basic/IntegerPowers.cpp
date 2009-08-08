
#include "IntegerPowers.hpp"


// Don't use this for mod calculations - the numbers get too large
// and the returned value cannot be correctly mod-ed - see powAndMod below
// that incorporates the mod into the loop to handle this.
unsigned long long ullPow(const unsigned int base,unsigned int exponent)
{
	if(exponent == 0)
		return 1;

  	if(base == 0)
		return 0;

  	// Take uints as inputs but output may be
  	// larger so work with ulls
  	unsigned long long r = 1;
  	unsigned long long ullBase = base;
  	while(exponent)
	{
    		if(exponent & 1)
    			r *= ullBase;

    	//divide by 2
		exponent >>= 1;
    	ullBase *= ullBase;
  	}

	return r;
}

// result = (base^exp) % mod
unsigned int powAndMod(const unsigned int base, unsigned int exp, const unsigned int mod)
{

      // use ull 64bits to prevent overflow when calculate 32bit x 32bit
      unsigned long long ullResult = 1;
      unsigned long long ullValue = base;

      while(exp)
      {
            if(exp & 1)
            {
		  // odd
                  // result = (result * value) % mod
                  ullResult *= ullValue;
                  ullResult %= mod;
            }

            // value = (value * value) % mod
            ullValue *= ullValue;
            ullValue %= mod;

            // exp = exp / 2
            exp >>= 1;
      }

      return( static_cast<unsigned int>(ullResult) );

}


