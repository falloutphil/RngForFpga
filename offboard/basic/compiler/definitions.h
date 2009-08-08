#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// MSVC needs shared library interfaces exported
#if defined(_MSC_VER)
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT
#endif

#endif //DEFINITIONS_H
