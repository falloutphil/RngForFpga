#include <vector>
#include <iostream>
#include <numeric>

#include <boost/assign/list_of.hpp>

#include "../../../basic/stl/algorithms.hpp"

#include "../SieveOfEratosthenes.hpp"
#include "../RabinMiller.hpp"

using namespace std;
using namespace boost::assign;
using namespace offboard::basic;
using namespace offboard::maths::prime;

inline unsigned int PrimalityTest( const vector<unsigned int>& primeCandidates )
{
	return accumulate( primeCandidates.begin(),
			           primeCandidates.end(), 0,
			           PassFailAccumulator<unsigned int>( &isPseudoPrime ) );
}


int main(int argc, char *argv[])
{
	unsigned int totalFails = 0;
	unsigned int testFails = 0;

	// *************** isPseudoPrime Self Tests ***************
	// Some random definitely-not prime values to self test Rabin Miller
	const vector< unsigned int > notPrime = list_of(0)(1)(4)(6)(8)(9)(10)(12)(14)(15)(16)(7917)(86633)(104727)(179424669);
	cout << "\n\nSelf-Test - the following values should fail our Rabin Miller test ....";
	totalFails += notPrime.size() - PrimalityTest( notPrime );

	// *************** FristNEratosPrimes Correct Number Returned ***************
	cout << "\n\nTesting FristNEratosPrimes...";
	const unsigned int requestedNumberOfPrimes = 1000000;
	cout << "\n\nAsk for the first " << requestedNumberOfPrimes << " primes";
	const auto_ptr< const vector<unsigned int> >
		firstNPrimes( FirstNEratosPrimes( requestedNumberOfPrimes ) );
	const unsigned int returnedNumberOfPrimes = firstNPrimes->size();
	cout << "\nFirstNEratosPrimes returned " << returnedNumberOfPrimes << " .... ";
	if ( requestedNumberOfPrimes == returnedNumberOfPrimes )
		cout << "OK";
	else
	{
		cout << "FAILURE - Incorrect number of primes returned";
		++totalFails;
	}

	// *************** Equivalence Test For Two Prime Functions ***************
	cout << "\n\nCompare output to EratosPrimesUpTo, using last value returned from FristNEratosPrimes .... ";
	const auto_ptr< const vector<unsigned int> >
		primesUpToLastFirstN ( EratosPrimesUpTo( firstNPrimes->back() ) );
	if ( *firstNPrimes == *primesUpToLastFirstN )
		cout << "OK";
	else
	{
		cout << "FAILURE - EratosPrimesUpTo() returned different vector to FristNEratosPrimes()";
		++totalFails;
	}

	// *************** Actual Primality Test Of Returned Values ***************
	// Assuming above test has passed only need to
	// to test one array - as both methods (should) have returned the same primes!
	cout << "\n";
	testFails = PrimalityTest( *firstNPrimes );
	totalFails += testFails;
	cout << "\n\n" << testFails << " failures detected.\n";

	cout << "\n\n\n\n**** " << totalFails << " total failures detected ****\n\n";
	return 0;
}
