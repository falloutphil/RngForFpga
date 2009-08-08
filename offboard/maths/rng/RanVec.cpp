#include "RanVec.hpp"

// Vectorised version of NRC's top quality RNG - RanVec

namespace offboard { namespace maths { namespace rng {


RanVec::RanVec( const unsigned long long j ):u_pipe(VECLENGTH),w_pipe(VECLENGTH)
{

	// Initialise circular buffers using random numbers.
	// TODO : neater way to define 'seed' using just one value
	u_pipe.push_back(0x7f45ca1690ba62efLL);
	u_pipe.push_back(0x1ea80e8d5049b39eLL);
	u_pipe.push_back(0x3776a376a22d29f2LL);
	u_pipe.push_back(0x45d8fd8d98c49b98LL);
	u_pipe.push_back(0x5049a7d199eba96bLL);

	w_pipe.push_back(0x7621d9b488e57e9LL);
	w_pipe.push_back(0xb66f2d687ae455adLL);
	w_pipe.push_back(0x99eb92cca76ef75cLL);
	w_pipe.push_back(0xa76edec1923fa4a8LL);
	w_pipe.push_back(0xedeb628980ceef65LL);

	v = 0xc35359f9ea3d8a90LL;

}

RanVec::~RanVec()
{

}

double RanVec::getDouble() const
{
	return 5.42101086242752217E-20 * int64();
}

unsigned long long RanVec::int64() const
{

	//u = u * 2862933555777941757LL + 7046029254386353087LL;
	// Use item at front of pipe (i.e output of multiplier)
	u = u_pipe[0] * 2862933555777941757LL + 7046029254386353087LL;

	// Push result into back of pipe (i.e. input of multiplier)
	u_pipe.push_back(u);

	v ^= v >> 17; v ^= v << 31; v ^= v >> 8; // This can be done in combinational logic, so no pipeline

	//w = 4294957665U*(w & 0xffffffff) + (w >> 32);
	w = 4294957665U*(w_pipe[0] & 0xffffffff) + (w_pipe[0] >> 32);
	w_pipe.push_back(w);

	unsigned long long x = u ^ (u << 21);; x ^= x >> 35; x ^= x << 4;

	return (x + v) ^ w;
}

unsigned int RanVec::int32() const
{
	return static_cast<unsigned int> ( int64() );
}

} } } //namespace
