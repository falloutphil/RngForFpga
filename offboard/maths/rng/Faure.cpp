
#include "../prime/SieveOfEratosthenes.hpp"

#include "Faure.hpp"

Faure::Faure( const unsigned long start_n, const unsigned int _dimensions ) :
	                                      n( start_n ),
                                          dimensions( _dimensions ),
                                          base( NextPrimeGreaterOrEqualTo(_dimensions) )
{

}

std::vector<double> Faure::getUniformVector() const
{
	// To keep the compiler happy for now
	return std::vector<double>(1);
}
