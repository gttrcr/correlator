#ifdef __linux__
#define SIGNATURE 
#elif _WIN32
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>
#define SIGNATURE extern "C" __declspec (dllexport)
#endif

#define STRING char***

SIGNATURE bool __cdecl ping(void)
{
	return true;
}

SIGNATURE unsigned int __cdecl computePolyFit(const unsigned int a)
{
	return a + 3;
}

SIGNATURE unsigned int __cdecl inputString(STRING str)
{
	return 0;
}