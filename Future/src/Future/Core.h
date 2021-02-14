#pragma once

#ifdef FT_PLATFORM_WINDOWS
	#ifdef FT_BUILD_DLL
		#define FUTURE_API __declspec(dllexport)
	#else
		#define FUTURE_API __declspec(dllimport)
	#endif
#else
	#error Future only supports Windows!
#endif