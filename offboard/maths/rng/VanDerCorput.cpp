
#include "VanDerCorput.hpp"


// Simple 1D case - keep GSL happy
VanDerCorput::VanDerCorput( const unsigned long start_n ) : Halton( start_n, 1 )
{
}

double VanDerCorput::getDouble() const
{
	return getUniformVector()[0];
}

unsigned int VanDerCorput::int32() const
{
	// Scale up our U[0,1] - not sure if this is very sound!
	return static_cast<unsigned int>( std::numeric_limits<unsigned int>::max() * getDouble() );
}

