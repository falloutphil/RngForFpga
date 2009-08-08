#ifndef CINTERFACE_H
#define CINTERFACE_H

#include "definitions.h"

#include <gsl/gsl_rng.h>

// This is the Pure C interface exposing our C++ interface into GSL
// to Pure C clients (eg dieharder).
// This is the only file you ever need to include in dieharder's add_ui_rngs.c.
// The actual implementations of these functions is in C_Interface.cpp (using our
// Random.hpp helpers to wrap our C++ objects into C structures recognised
// by GSL's rng library (and thus dieharder).  As the actual interface
// is in Pure C this header hides the C++ internals (in C_Interface.cpp) from dieharder.

// Our C++ Random Class -> Wrapped using C++ into a gsl_rng_type struct -> This C Interface to return these structs back to C clients via accessor functions.

// As C can't link against templates this means (until I can think
// of a better way) that for each new child of our Random class
// you have to add a new C accessor interface, with a tedious 
// one-liner implementation in C_Interface.cpp - still the framework
// as it is takes 95% of the donkey-work out of the equation....

// NOTE: These one-liners, despite how tempting, cannot be inline'd
// as inlining them defeats there whole purpose as a Pure C  separation interface!


// Let's explicitly tell any C++
// compiler that this bit is in pure C
#ifdef __cplusplus
extern "C" {
#endif

// Ranq1 class
DLLEXPORT const gsl_rng_type* get_gsl_rng_ranq1();
// Mersenne class
DLLEXPORT const gsl_rng_type* get_gsl_rng_mersenne();
// Ran class
DLLEXPORT const gsl_rng_type* get_gsl_rng_ran();
// VanDerCorput class
DLLEXPORT const gsl_rng_type* get_gsl_rng_vandercorput();

#ifdef __cplusplus
}
#endif

#endif // CINTERFACE_H
