#include <vector>
#include <iostream>
#include <numeric>

#include "../SieveOfEratosthenes.hpp"
#include "../RabinMiller.hpp"

unsigned int PrimalityResult( unsigned int failsSoFar, unsigned int primeCandidate )
{
	std::cout << "\nPrimality Testing " << primeCandidate << " .... ";
	if ( isPseudoPrime( primeCandidate, 500 ) )
		std::cout << "OK";
	else
	{
		std::cout << "FAILURE - Rabin Miller disagrees over primality";
		++failsSoFar;
	}
	return failsSoFar;
}


unsigned int PrimalityTest( const std::vector<unsigned int>* const primeCandidates )
{
	return std::accumulate( primeCandidates->begin(), primeCandidates->end(), 0, PrimalityResult );
}




int main(int argc, char *argv[])
{
	unsigned int totalFails = 0;
	unsigned int testFails = 0;
	// Some random definately-not prime values to self test Rabin Miller
	const unsigned int notPrime[] = { 0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16, 7917, 86633, 104727, 179424669 };


	// *************** isPseudoPrime Self Tests ***************

	std::cout << "\n\nSelf-Test - the following values should fail our Rabin Miller test ....";
	for ( unsigned int i = 0; i < sizeof(notPrime)/sizeof(notPrime[0]); ++i )
	{
		std::cout << "\nPrimality Testing " << notPrime[i] << " .... ";
		// Make number of R-M test large (100000) so chance of
		// spurious failure is very small.
		if ( isPseudoPrime( notPrime[i], 100000 ) )
		{
			std::cout << "FAILURE - Rabin Miller thinks this is prime - rerun the test in case Rabin is wrong (i.e. it's pseudoprime)!";
			++totalFails;
		}
		else
			std::cout << "OK";
	}


	// *************** FristNEratosPrimes Tests ***************

	std::cout << "\n\nTesting FristNEratosPrimes...";
	unsigned int requestedNumberOfPrimes = 1000000;

	// First N primes test
	std::cout << "\n\nAsk for the first " << requestedNumberOfPrimes << " primes";
	const std::vector<unsigned int>* const primes = FirstNEratosPrimes( requestedNumberOfPrimes );
	const unsigned int returnedNumberOfPrimes = primes->size();
	std::cout << "\nFirstNEratosPrimes returned " << returnedNumberOfPrimes << " .... ";
	if ( requestedNumberOfPrimes == returnedNumberOfPrimes )
		std::cout << "OK";
	else
	{
		std::cout << "FAILURE - Incorrect number of primes returned";
		++totalFails;
	}

	// Primes agree with EratosPrimesUpTo function
	std::cout << "\n\nCompare output to EratosPrimesUpTo, using last value returned from FristNEratosPrimes .... ";
	const std::vector<unsigned int>* const primes2 = EratosPrimesUpTo( primes->back() );
	if ( *primes == *primes2 )
		std::cout << "OK";
	else
	{
		std::cout << "FAILURE - EratosPrimesUpTo() returned different vector to FristNEratosPrimes()";
		++totalFails;
	}


	// Primality test
	std::cout << "\n";
	testFails = PrimalityTest( primes );
	totalFails += testFails;
	std::cout << "\n\n" << testFails << " failures detected.\n";

	// *************** EratosPrimesUpTo Tests ***s************

	// Primality test - getting maximum number of primes
	//std::numeric_limits<unsigned int>::max() - 1; // - Not on my poxy laptop!
	//requestedNumberOfPrimes = 50000000;
	//std::cout << "\n\nTesting EratosPrimesUpTo for all primes up to " << requestedNumberOfPrimes << " (should be int(max) or max reccomended use of this sieve, but I don't have the memory!) ...";
	//const std::vector<unsigned int>* const primes3 = EratosPrimesUpTo( requestedNumberOfPrimes );
	//std::cout << "\n";
	//testFails = PrimalityTest( primes3 );
	//totalFails += testFails;
	//std::cout << "\n\n" << testFails << " failures detected.\n";

	std::cout << "\n\n\n\n**** " << totalFails << " total failures detected ****\n\n";
	//clean up
	delete primes;
	delete primes2;
	//delete primes3;
	return 0;
}
