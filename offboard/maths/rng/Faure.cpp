
#include <cmath>

#include "../basic/Factorial.hpp"
#include "../basic/IntegerPowers.hpp"
#include "../prime/SieveOfEratosthenes.hpp"

#include "Faure.hpp"

using namespace std;
using namespace offboard::maths::basic;
using namespace offboard::maths::prime;

namespace offboard { namespace maths { namespace rng {

// To prevent initial clustering around zero, discard first
// (base^4 - 1) generated as suggested by Faure
Faure::Faure( const unsigned long start_n, const unsigned int _dimensions ) :
										  base( NextPrimeGreaterOrEqualTo(_dimensions) ),
										  n( start_n + static_cast<unsigned int>(ullPow(base,4)) - 1 ),
                                          dimensions( _dimensions )
{

}

// See p257 of McLeish, 2005 for theory used
// for this implementation.
// http://www.puc-rio.br/marco.ind/quasi_mc.html is also useful.
vector<double> Faure::getUniformVector() const
{
	vector<unsigned int> a_k;
	// Work out the number of digits to represent n in our new base
	a_k.reserve( 
		         static_cast<size_t>( ceil( log(static_cast<double>(n))/
		                                    log(static_cast<double>(base)) ) )
				);
	// Will have one result for each dimension
	vector<double> result;
	result.reserve( dimensions );

	// Find our initial a_k values in required base
	// Representation of number is SUM,k=0,k<t(a_k*b^k)
	// We want a_0 in position 0 - [a0][a1][a2][a3]...[an]
	// as a_0 is coefficient of base^0 (LSB).
	// This is the reverse order of normal binary representation
	// (LSB to the left) and can be obtained using the division method:
	// http://www.cs.uaf.edu/~cs301/notes/Chapter3/node7.html
	// (Remember - the remainder is represented in terms denominator
	// 2/3 = 1,R1 = 1 + 1/3, hence (+ b0/2) when dividing by 2 *IS* Remainder b0)
	for ( k = n; (k); k/=base )
	{
		a_k.push_back( k % base );
	}

	// Then for each required dimension transform the last a_k vector
	// and use these values to give us our random number
	const unsigned int t = a_k.size();
	vector<unsigned int> c_k;
	c_k.reserve( a_k.size() );
	for ( unsigned int d = 0; d < dimensions; ++d )
	{
		// Make way for new coefficients
		c_k.clear();
		myRandom = 0.;
		primePower = 1.;
		// Calculate every c_k coefficient
		for ( k=0; k<t; ++k )
		{
			// Reset result holder prior to summation
			myC_k = 0;
			// Sum all the values to the right
			// multiplied by the number of k permutations in m.
			// This gives us one c_k coefficient.
			for ( m=k; m<t; ++m )
			{
				// c_k = SUM( m_P_k * a_m ) MOD base
				myC_k += ( n_P_r(m,k) * a_k[m] );
			}
			// MOD with our prime base after summation
			c_k.push_back(myC_k % base);
			// Sum coefficients for  1/b, 1/b^2, 1/b^3, etc (eg 1/2, 1/4, 1/8 in binary)
			// SUM(c_k*b^(-k-1))
			// NOTE:  This is why we wanted out LSB a_0 at a_k[0].  We are now reflecting in
			//        the decimal point so a_0 -> 1/(b^k).  In normal binary representation
			//        a_n would be at a_k[0] (just as with decimal 319 would be
			//        begin[3][1][9]end in string memory), and would be multiplied by 1/2.
			//        Think about it - for 1011, 101[1] -> [1]101
			primePower /= base;
			myRandom += c_k.back() * primePower;
		}
		// Old coefficients can now take the values
		// of the new coefficients to calculate the next
		// dimension: n+1 calculates it's coefficients
		// from n's coefficients.
		a_k = c_k;
		// Store result for this dimension
		result.push_back( myRandom );
	}

	// Increment our seed for next call
	++n;
	return result;
}

} } } //namespace

