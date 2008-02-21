// ****************************************************************************
// PicoloVfW.h - Revision 1.0.0.1
//

#ifndef __PICOLO_VFW__
#define __PICOLO_VFW__

#include "multicam32.h"


// ****************************************************************************
// ENVIRONMENT DECLARATIONS
//
#if defined _WINDOWS || defined WIN32 || defined _Windows
#define __WINDOWS_DEFINED__
#endif

#ifdef __WINDOWS_DEFINED__
    #ifdef BUILD_USERMODE_VFWDRIVER
	    #ifdef __BORLANDC__
            #define DllVfWEntry _export WINAPI
        #else
            #define DllVfWEntry __declspec(dllexport) WINAPI
        #endif
    #else
	    #ifdef __BORLANDC__
			#define DllVfWEntry _import WINAPI
        #else
			#define DllVfWEntry __declspec(dllimport) WINAPI
        #endif
    #endif
#else
    #if defined BUILD_USERMODE_VFWDRIVER && defined __BORLANDC__	
		#define DllVfWEntry _loadds _saveregs
    #else
        #define DllVfWEntry
    #endif	
    #define WINAPI
#endif

#ifndef __BUILD_EURECARDACL
#ifdef __cplusplus
extern "C" {
#endif

#if !defined(MC_DYNAMIC_BINDING)

// ****************************************************************************
// System information
//
#define EC_MAX_VFW_PROCESS		32

// ****************************************************************************
// A.P.I. Functions
//

ECSTATUS DllVfWEntry MultiCamVfWInitialize();
ECSTATUS DllVfWEntry MultiCamVfWTerminate();

ECSTATUS DllVfWEntry MultiCamVfWGetPIDList(PUINT32 PIDList, UINT32 ListCount, PUINT32 returnedCount);

ECSTATUS DllVfWEntry MultiCamVfWSetParamInt(UINT32 ProcessID, ECPARAMID ParamID, INT32 Value);
ECSTATUS DllVfWEntry MultiCamVfWGetParamInt(UINT32 ProcessID, ECPARAMID ParamID, PINT32 pValue);


#endif//MC_DYNAMIC_BINDING

#ifdef __cplusplus
} ;
#endif 
#endif // __BUILD_EURECARDACL

#endif // __PICOLO_VFW__