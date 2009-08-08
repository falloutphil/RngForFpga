/*
 * Sobol.hpp
 *
 *  Created on: Jul 8, 2008
 *      Author: philipbeadling
 */

#ifndef SOBOL_HPP_
#define SOBOL_HPP_

#include <vector>

#include "definitions.h"

#include "Random.hpp"

namespace offboard { namespace maths { namespace rng {

// Sobol Quasi-Random sequence
// Adapted from Press et al, 2007.
class Sobol : public Random
{
	public:
		DLLEXPORT Sobol( const unsigned int _dimensions );

		DLLEXPORT std::vector<double> getUniformVector();

	private:
		static const int MAXBIT=30, MAXDIM=6;
		const unsigned int dimensions;
		int j,k,l;
		unsigned int i,im,ipp;
		static int mdeg[MAXDIM];
		unsigned int in;
		std::vector<unsigned int> ix;
		std::vector<unsigned int*> iu;
		static unsigned int ip[MAXDIM];
		static unsigned int iv[MAXDIM*MAXBIT];
		double fac;
		std::vector<double> result;


};

// Retarded, I know, we'll do something about this later....
// These don't look const to me - I believe they are manipulated
// in directly by pointers in iu.
int Sobol::mdeg[] = {1,2,3,3,4,4};
unsigned int Sobol::ip[] = {0,1,1,2,1,4};
unsigned Sobol::iv[] = {1,1,1,1,1,1,3,1,3,3,1,1,5,7,7,3,3,5,15,11,5,15,13,9};


} } } // namespace

#endif /* SOBOL_HPP_ */

