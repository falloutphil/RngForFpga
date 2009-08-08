/*
 * Sobol.cpp
 *
 *  Created on: Jul 8, 2008
 *      Author: philipbeadling
 */

#include <iostream>

#include "Sobol.hpp"

using namespace std;

namespace offboard { namespace maths { namespace rng {

Sobol::Sobol( const unsigned int _dimensions ) :
									dimensions ( _dimensions ),
									in(0),
									ix( MAXDIM, 0 ),
									iu( MAXBIT ),
									result( _dimensions, 0. )

{
	if ( iv[0] != 1 )
		return;

	fac = 1.0/( 1 << MAXBIT );
	for (j=0,k=0;j<MAXBIT;++j,k+=MAXDIM)
		iu[j] = &iv[k];

	for (k=0;k<MAXDIM;++k)
	{
		for(j=0;j<mdeg[k];++j)
			iu[j][k] <<= (MAXBIT-1-j);


		for (j=mdeg[k];j<MAXBIT;++j)
		{
			ipp=ip[k];
			i=iu[ j-mdeg[k] ][k];
			i ^= ( i >> mdeg[k] );
			for(l=mdeg[k]-1;l>=1;--l)
			{
				if ( ipp & 1 )
					i ^= iu[j-1][k];
				ipp >>= 1;
			}
		}
	}
}

vector<double> Sobol::getUniformVector()
{
	//vector<double> result( dimensions, 0. );
	im=in++;
	for(j=0;j<MAXBIT;++j)
	{
		if (!(im & 1))
			break;
		im >>=1;
	}
	if (j > MAXBIT)
		throw("MAXBIT too small in Sobol class");

	im=j*MAXDIM;
	for(k=0;k<dimensions;++k)
	{
		ix[k] ^= iv[im+k];
		result[k] = ix[k] * fac;
	}

	return result;
}

} } } // namespace

