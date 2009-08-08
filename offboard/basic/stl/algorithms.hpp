#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <iostream>
#include <functional>

namespace offboard { namespace basic {


// Generic pass/fail testing accumulator functor
// If you have a container of test candidates and you want to iterate over
// them applying a true/false test and accumulate the results - don't
// loop over them, use this with std::accumulate instead!

// TestDataType - the data type that we are testing
// TestFunctionType - A test function with the signature "bool myFunc( const TestDataType& )"
template< typename TestDataType >
class PassFailAccumulator : public std::binary_function< unsigned int, TestDataType, unsigned int >
{
	typedef bool (*TestFunctionType)( const TestDataType& );
	public:
		PassFailAccumulator( TestFunctionType _testFunction ) : testFunction( _testFunction ) {};

		inline unsigned int operator()( unsigned int failsSoFar, const TestDataType& testCandidate ) const
		{
			std::cout << "\nTesting Candidate " << testCandidate << " .... ";
			if ( (*testFunction)( testCandidate ) )
				std::cout << "OK";
			else
			{
				std::cout << "Failure";
				++failsSoFar;
			}

			return failsSoFar;
		}

	private:
		const TestFunctionType testFunction;
};



// Does our test value lie *ON* or inside
// the range bounded by our high and low values?
template< typename BoundType >
class BoundedBy : public std::unary_function< BoundType, bool >
{
	public:
		BoundedBy( const BoundType& lowValue, const BoundType& highValue )
			: lowerBound( lowValue ), upperBound( highValue ) {};

		inline bool operator()( const BoundType& val ) const
		{
			return ( (lowerBound <= val) && ( val <= upperBound ) );
		}

	private:
		const BoundType lowerBound;
		const BoundType upperBound;
};


} } // namespace

#endif // ALGORITHMS_HPP
