#ifndef vmt_PROJECT_EXPORT_H
#define vmt_PROJECT_EXPORT_H

#ifdef WIN32

#ifdef  BUILDING_CORE
#define COREAPI __declspec(dllexport)
#else
#define COREAPI __declspec(dllimport)
#endif

#else

#ifdef  BUILDING_CORE
#define COREAPI __attribute__ ((visibility ("default")))
#else
#define COREAPI
#endif

#endif

#endif //__PROJECT_EXPORT_H
