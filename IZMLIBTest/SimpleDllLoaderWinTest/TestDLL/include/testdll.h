// testdll.h
#ifndef TESTDLL_H
#define TESTDLL_H

#ifdef EXPORTS
#define EXPORT extern __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C"
{
EXPORT int GetNext( int val );
EXPORT int GetPrevious( int val );
}

#endif // TESTDLL_H
