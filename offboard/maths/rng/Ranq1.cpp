#include "Ranq1.hpp"

// Implementation of NRC's everyday RNG - Ranq1

Ranq1::Ranq1( const unsigned long long j ) : v(4101842887655102017LL)
{
	v ^= j;
	v = int64();
}

double Ranq1::getDouble() const
{
	return 5.42101086242752217E-20 * int64();
}

unsigned long long Ranq1::int64() const
{
	v ^= v >> 21;
	v ^= v << 35;
	v ^= v >> 4;
	return v * 2685821657736338717LL;
}

unsigned int Ranq1::int32() const
{
	return static_cast<unsigned int> ( int64() );
}

