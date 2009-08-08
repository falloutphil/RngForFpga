/*
 * TestFaure.cpp
 *
 *  Created on: Jul 7, 2008
 *      Author: philipbeadling
 */


#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <algorithm>
#include "../../../basic/stl/algorithms.hpp"
#include "../../basic/IntegerPowers.hpp"
#include "../Faure.hpp"


using namespace std;
using namespace offboard::basic;
using namespace offboard::maths::basic;
using namespace offboard::maths::rng;

int main(int argc, char *argv[])
{

	// Test distribution of draws from Faure sequence
	// in hypercube - this will take a *long* time to run
	// to the full 15 dimensions (Faure's accepted usuage maximum)
	// Build it in 'release' and grab a very large cup of tea!
	cout << "\n\n\nTEST 1: nD Faure Ratios of Distribution Test";
	// Dimensions - 6 results in approx 24 hour test on Mac 2GHz G5 PPC!
	const unsigned int max_dimension = 6;
	// Number of draws from sequence (dependand on dimensionality)
	unsigned long long numFaures;
	// Number of draws that fall into our sliced hypercube
	unsigned int numBoundedFaures;
	// Length of 1 side of our hypercube
	long double hypercubeLength;
	// Low and high points of test hypercube inside the unit hypercube
	double lowerHypercubeBound;
	double upperHypercubeBound;
	// Volume of our test hypercube
	long double slicedHypercubeVolume;
	// Expected number of points inside our test hypercube
	unsigned int expectedHits;
	// Error from expected hits
	unsigned int hitError;
	// Number of failures;
	unsigned int toleranceFailures = 0;
	// Lets look at the distributions of the failures
	// assume nothing will shoot out past 100!
	const unsigned int numberOfBuckets = 100;
	vector< vector< unsigned int > >
		vToleranceBuckets( max_dimension, vector< unsigned int >(numberOfBuckets,0) );
	for ( unsigned int dimensions=1; dimensions<=max_dimension; ++dimensions )
	{
		cout << setprecision(16) << "\n\n************ Testing distribution in " << dimensions << "-D hypercube ************";
		const Faure myFaure( 1, dimensions );
		vector< double > thisFaure;
		// We can control the number of Faures required depending on
		// the dimensionality of the test.  For example in 1000 draws
		// in a 3D cube we would only expect 1 Faure, so we do 1000*100 draws
		// to test across a more sensible range of values (hunting for 1 is a bit hit and miss!)
		// If we don't do this we have to test all dimensions assuming our maximum dimensionality
		// for example it would not be unreasonable for their to be no points in a given area
		// for 10000 draws from a 15-D hypercube (indeed for 5-D hypercube this would hold!).
		numFaures = ullPow( 10, dimensions + 2 );
		cout << "\nTesting with " << numFaures << " draws";
		for( hypercubeLength = 0.1; hypercubeLength <= 1; hypercubeLength += 0.01 )
		{
			cout << "\n\n**** Hypercube length = " << hypercubeLength << " ****";
			// Commented out a piss-on to weight the power by the exponent of the hypercubeLength
			// - this would mean we could start our hypercubeLength at 0.01 rather than 0.1
			//numFaures = ullPow( 10, dimensions + static_cast<unsigned long long>(fabs( log10(hypercubeLength) )) + 1 );
			slicedHypercubeVolume = pow( hypercubeLength, static_cast<long double>(dimensions) );
			expectedHits = static_cast<unsigned int>(slicedHypercubeVolume * numFaures);
			cout << "\nWe should see ~" << expectedHits << " points in our hypercube";
			lowerHypercubeBound = 0;
			upperHypercubeBound = lowerHypercubeBound + hypercubeLength;
			for( ;
			     upperHypercubeBound <= 1;
			     lowerHypercubeBound = upperHypercubeBound, upperHypercubeBound += hypercubeLength )
			{
				numBoundedFaures = 0;
				for (unsigned long long i=0;i<numFaures;++i)
				{
					thisFaure = myFaure.getUniformVector();
					// Is this Faure in our hypercube - check each dimension sits between bounds
					// - drop out if one doesn't, i.e. not1
					if ( find_if( thisFaure.begin(), thisFaure.end(),
							      not1(BoundedBy<double>( lowerHypercubeBound, upperHypercubeBound )) ) == thisFaure.end() )
						++numBoundedFaures;
				}
				long double ratioOfFaures = static_cast<long double>( numBoundedFaures ) / static_cast<long double>( numFaures );
				cout << "\n\nNumber of Faures in hypercube: " << numBoundedFaures;
				hitError = abs( static_cast<int>(expectedHits - numBoundedFaures) );
				// If we are ever more than 15 out, record the problem
				// I don't think we should have to scale this by number of
				// draws as Faure's accuracy shouldn't decrease with number of draws.
				++vToleranceBuckets[dimensions-1][ hitError ];
				if ( hitError > 20 )
				{
					cout << "\nWARNING: Sequence has strayed by an unusually large value";
					++toleranceFailures;
				}
				cout << "\nDifference from expected value: " << hitError;
				cout << "\nTotal number of Faures used: " << numFaures;
				cout << "\nRatio of Faures (in/total): " << ratioOfFaures ;
				// as the unit hypercube always has a volume of 1.
				cout << "\nRatio of Volumes (hyper_vol/unit_vol): " << slicedHypercubeVolume;
				cout << "\nDifference in ratios: " << fabs( ratioOfFaures - slicedHypercubeVolume );

			}
		}
	}
	cout << "\n\n\n**** TOTAL FAILURES >20 for nD Faure - " << toleranceFailures << " ****";
	cout << "\n\nDistribution of tolerance failures (size of error, number of errors at that size)";
	for( unsigned int i=0; i<max_dimension; ++i)
	{
		cout << "\nDistribution of " << i+1 << "-D errors";
		for( unsigned int j=0; j<numberOfBuckets; ++j)
			cout << "\n" << j << "\t" << vToleranceBuckets[i][j];
	}
	cout << "\n\n";
	return 0;
}

