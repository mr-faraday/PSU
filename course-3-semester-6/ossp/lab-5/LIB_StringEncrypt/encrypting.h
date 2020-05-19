#pragma once

#ifdef MATHLIBRARY_EXPORTS
#define ENCRYPTING_API __declspec(dllexport)
#else
#define ENCRYPTING_API __declspec(dllimport)
#endif

#include <string>

const int MAX_STRING_SIZE = 4096;

extern "C" ENCRYPTING_API void encrypt(wchar_t*, int, const wchar_t*);
