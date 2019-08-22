#pragma once
#ifdef DLL_API_EXPORT//如果已经定义就什么都不做
	#define DLL_API __declspec(dllexport)
#else //否则定义DLL_API
    #define DLL_API __declspec(dllimport)    //_declspec(dllexport)：导出标志
#endif


