// Probabilistic test for Primality:

// Rabin, M. O. "Probabilistic Algorithm for Testing Primality." J. Number Th. 12, 128-138, 1980.
// Miller, G. "Riemann's Hypothesis and Tests for Primality." J. Comp. Syst. Sci. 13, 300-317, 1976.
// http://en.wikipedia.org/wiki/Miller-Rabin_primality_test

// Based on simple python code here
// http://krenzel.info/?p=83#rabin
// Note: This guy makes some optimizations I haven't implemented yet - see article

#ifndef RABINMILLER_HPP
#define RABINMILLER_HPP

#include "definitions.h"

DLLEXPORT bool isPseudoPrime( const unsigned int n, const unsigned int numberOfTests = 100 );

#endif //RABINMILLER_HPP

