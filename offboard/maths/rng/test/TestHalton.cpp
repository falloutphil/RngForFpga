
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include "../../basic/IntegerPowers.hpp"
#include "../Halton.hpp"
#include "../VanDerCorput.hpp"

int main(int argc, char *argv[])
{
	// Average value of U[0,1] should be 0.5 - so if we sum enough of them
	// we should get a result which approximates 0.5*number_summed - let's test this
	std::cout << "\n\n\nTEST 1: 1D Van der Corput Central Limit Theory Test";
	double sum=0.0;
	unsigned long long sum2=0;
	const double iters = 1000000.0;
	const unsigned int iters2 = 1000000;
	const VanDerCorput myV( 250 );
	for (unsigned int i=0;i<iters;++i)
		sum += myV.getDouble();
	std::cout << "\n\nU[0,1] Expected:" << 0.5*iters << "\tSum:" << sum;
	std::cout << "\nDifference:" << ((iters * 0.5) - sum);
	for (unsigned int i=0;i<iters2;++i)
		sum2 += myV.int32();
	unsigned long long expected = std::numeric_limits<unsigned int>::max() / 2;
	std::cout << "\n\nU[0,int(max)] Expected:" << iters2 * expected  << "\tSum:" << sum2;
	std::cout << "\nDifference:" << ((iters2 * expected) - sum2);

	// Test distribution of draws from Halton sequence
	// in hypercube - this will take a *long* time to run
	// to the full 15 dimensions (Halton's accepted usuage maximum)
	// Build it in 'release' and grab a very large cup of tea!
	std::cout << "\n\n\nTEST 2: nD Halton Ratios of Distribution Test";
	// Dimensions - 6 results in approx 24 hour test on Mac 2GHz G5 PPC!
	const unsigned int max_dimension = 6;
	// Number of draws from sequence (dependand on dimensionality)
	unsigned long long numHaltons;
	// Number of draws that fall into our sliced hypercube
	unsigned int numBoundedHaltons;
	// Length of 1 side of our hypercube
	long double hypercubeLength;
	// Test if point lives in the hypercube
	bool isInSlicedHyperCube;
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
	std::vector< std::vector< unsigned int > >
		vToleranceBuckets( max_dimension, std::vector< unsigned int >(numberOfBuckets,0) );
	for ( unsigned int dimensions=1; dimensions<=max_dimension; ++dimensions )
	{
		std::cout << std::setprecision(16) << "\n\n************ Testing distribution in " << dimensions << "-D hypercube ************";
		const Halton myH2( 1, dimensions );
		std::vector< double > thisHalton;
		// No need to modify through iterator
		std::vector< double >::const_iterator itHalton;
		// We can control the number of haltons required depending on
		// the dimensionality of the test.  For example in 1000 draws
		// in a 3D cube we would only expect 1 halton, so we do 1000*100 draws
		// to test across a more sensible range of values (hunting for 1 is a bit hit and miss!)
		// If we don't do this we have to test all dimensions assuming our maximum dimensionality
		// for example it would not be unreasonable for their to be no points in a given area
		// for 10000 draws from a 15-D hypercube (indeed for 5-D hypercube this would hold!).
		numHaltons = ullPow( 10, dimensions + 2 );
		std::cout << "\nTesting with " << numHaltons << " draws";
		for( hypercubeLength = 0.1; hypercubeLength <= 1; hypercubeLength += 0.01 )
		{
			std::cout << "\n\n**** Hypercube length = " << hypercubeLength << " ****";
			// Commented out a piss-on to weight the power by the exponent of the hypercubeLength
			// - this would mean we could start our hypercubeLength at 0.01 rather than 0.1
			//numHaltons = ullPow( 10, dimensions + static_cast<unsigned long long>(fabs( log10(hypercubeLength) )) + 1 );
			slicedHypercubeVolume = pow( hypercubeLength, static_cast<long double>(dimensions) );
			expectedHits = static_cast<unsigned int>(slicedHypercubeVolume * numHaltons);
			std::cout << "\nWe should see ~" << expectedHits << " points in our hypercube";
			lowerHypercubeBound = 0;
			upperHypercubeBound = lowerHypercubeBound + hypercubeLength;
			for( ;
			     upperHypercubeBound <= 1;
			     lowerHypercubeBound = upperHypercubeBound, upperHypercubeBound += hypercubeLength )
			{
				numBoundedHaltons = 0;
				for (unsigned long long i=0;i<numHaltons;++i)
				{
					thisHalton = myH2.getUniformVector();
					// Is this Halton in our hypercube
					isInSlicedHyperCube = true;
					itHalton = thisHalton.begin();
					while( isInSlicedHyperCube && (itHalton != thisHalton.end()) )
					{
						isInSlicedHyperCube = ( (lowerHypercubeBound <= *itHalton) && (*itHalton <= upperHypercubeBound));
						++itHalton;
					}
					if ( isInSlicedHyperCube )
						// We have a winner!
						++numBoundedHaltons;
				}
				long double ratioOfHaltons = static_cast<long double>( numBoundedHaltons ) / static_cast<long double>( numHaltons );
				std::cout << "\n\nNumber of Haltons in hypercube: " << numBoundedHaltons;
				hitError = abs( static_cast<int>(expectedHits - numBoundedHaltons) );
				// If we are ever more than 15 out, record the problem
				// I don't think we should have to scale this by number of
				// draws as Halton's accuracy shouldn't decrease with number of draws.
				++vToleranceBuckets[dimensions-1][ hitError ];
				if ( hitError > 20 )
				{
					std::cout << "\nWARNING: Sequence has strayed by an unusually large value";
					++toleranceFailures;
				}
				std::cout << "\nDifference from expected value: " << hitError;
				std::cout << "\nTotal number of Haltons used: " << numHaltons;
				std::cout << "\nRatio of Haltons (in/total): " << ratioOfHaltons ;
				// as the unit hypercube always has a volume of 1.
				std::cout << "\nRatio of Volumes (hyper_vol/unit_vol): " << slicedHypercubeVolume;
				std::cout << "\nDifference in ratios: " << fabs( ratioOfHaltons - slicedHypercubeVolume );

			}
		}
	}
	std::cout << "\n\n\n**** TOTAL FAILURES >20 for nD Halton - " << toleranceFailures << " ****";
	std::cout << "\n\nDistribution of tolerance failures (size of error, number of errors at that size)";
	for( unsigned int i=0; i<max_dimension; ++i)
	{
		std::cout << "\nDistribution of " << i+1 << "-D errors";
		for( unsigned int j=0; j<numberOfBuckets; ++j)
			std::cout << "\n" << j << "\t" << vToleranceBuckets[i][j];
	}
	std::cout << "\n\n";
	return 0;
}

