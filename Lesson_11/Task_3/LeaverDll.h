#pragma once
#include <string>

#ifdef LeaveDll_EXPORTS
#define LeaverDll_API __declspec(dllexport)
#else
#define LeaverDll_API __declspec(dllimport)
#endif

class Leaver {
public:

	LeaverDll_API static std::string leave(std::string* name);
};