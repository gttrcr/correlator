#ifdef __linux__
#define SIGNATURE 
#elif _WIN32
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#define SIGNATURE extern "C" __declspec (dllexport)
#endif

#define STRING char***

SIGNATURE unsigned int __cdecl ComputePolyFit(const unsigned int a)
{
	return a + 3;
}

SIGNATURE unsigned int __cdecl InputString(STRING str)
{
	return 0;
}