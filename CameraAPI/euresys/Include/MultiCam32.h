// ****************************************************************************
// MultiCam32.h - Revision 3.7.1
//

#ifndef __MULTICAM32_PICOLO__
#define __MULTICAM32_PICOLO__

// ****************************************************************************
// Includes
//
#include "EC_Parameters.h"


// ****************************************************************************
// Status / ErrorCode
//
#define	EC_OK								 0
#define EC_ERROR_DEVICE_NOT_FOUND			-1
#define EC_ERROR_INVALID_PARAMETER			-2
#define	EC_ERROR_TIMEOUT					-3
#define	EC_ERROR_INVALID_HANDLE				-4
#define	EC_ERROR_SURFACE_ERROR				-5
#define	EC_ERROR_CHANNEL_ERROR				-6
#define	EC_ERROR_SYSTEM_ERROR				-7
#define	EC_ERROR_UNSUCCESSFUL				-8
#define EC_ERROR_NO_DATA					-9
#define EC_ERROR_INVALID_PARAMETER_VALUE	-10
#define EC_ERROR_IO_INDEX_ERROR				-11
#define EC_ERROR_INVALID_IO_FUNCTION		-12
#define EC_ERROR_INVALID_PID				-13
#define	EC_ERROR_NOT_IMPLEMENTED			-100


// ****************************************************************************
// Events (warning : copy must be holded)
//
#ifndef __EC_EVENTS
#define	__EC_EVENTS
#define EC_SIGNAL_CHANNEL_STATE		0x0
#define EC_SIGNAL_CHANNEL_ERROR		0x1
#define EC_SIGNAL_SURFACE_STATE		0x2
#define EC_SIGNAL_SURFACE_AVAILABLE	0x3
#define EC_SIGNAL_ASM_STATE			0x4
#define EC_SIGNAL_ASM_ERROR			0x5
#define EC_SIGNAL_SYSTEM_TRIGGER	0x6
#define EC_SIGNAL_IO_ACTIVITY		EC_SIGNAL_SYSTEM_TRIGGER
#define	EC_MAX_EVENTS				0x7
#endif

#define	EC_STD_TIMEOUT		1000


// ****************************************************************************
// Types
//
#ifdef WIN32
#include "windows.h"
#endif

typedef unsigned __int64 UINT64, *PUINT64;
typedef signed __int64 INT64, *PINT64;
typedef unsigned int UINT32, *PUINT32;
typedef unsigned short UINT16, *PUINT16;
typedef unsigned char UINT8, *PUINT8;
typedef signed int INT32, *PINT32;
typedef signed short INT16, *PINT16;
typedef signed char INT8, *PINT8;
typedef char CHAR, *PCHAR;
typedef const char *PCCHAR;
typedef const char *CPCHAR;
typedef float FLOAT32, *PFLOAT32;
typedef double FLOAT64, *PFLOAT64;
typedef void *PVOID;

typedef long ECSTATUS;
typedef long ECHANDLE;
typedef long ECPARAMID;


// ****************************************************************************
// ENVIRONMENT DECLARATIONS
//
#if defined _WINDOWS || defined WIN32 || defined _Windows
#define __WINDOWS_DEFINED__
#endif

#ifdef __WINDOWS_DEFINED__
    #ifdef BUILD_USERMODE_DRIVER
	    #ifdef __BORLANDC__
            #define DllEntry _export WINAPI
        #else
            #define DllEntry __declspec(dllexport) WINAPI
        #endif
    #else
	    #ifdef __BORLANDC__
			#define DllEntry _import WINAPI
        #else
			#define DllEntry __declspec(dllimport) WINAPI
        #endif
    #endif
#else
    #if defined BUILD_USERMODE_DRIVER && defined __BORLANDC__	
		#define DllEntry _loadds _saveregs
    #else
        #define DllEntry
    #endif	
    #define WINAPI
#endif


// ****************************************************************************
// Event Handler
//
typedef struct t_EventInfo {
	UINT32 EventID ;
	UINT32 ChannelID ;
	UINT32 SurfaceID ;
	UINT32 Data ; 
	UINT32 Flags ;
	UINT32 TimeCode ;
	UINT32 Reserved ;
} ECEVENTINFO, *PECEVENTINFO;

typedef struct t_EventTriggerInfo {
	UINT32 EventID ;
	UINT32 BoardID ;
	UINT32 ResultHigh ;
	UINT32 ResultLow ; 
	UINT32 ResultGoingHigh ;
	UINT32 ResultGoingLow ;
	UINT32 ResultGoingAny ;
} ECEVENTTRIGGERINFO, *PECEVENTTRIGGERINFO;


typedef void (WINAPI *ECEVENTHANDLER)(PVOID context, PECEVENTINFO pInfo);

#ifndef __EC_EVENTS_DATA
#define	__EC_EVENTS_DATA

enum {
	SIGNAL_SURFACE_STATE_FREE  ,
	SIGNAL_SURFACE_STATE_CAPTURED  ,
	SIGNAL_SURFACE_STATE_FILLING  ,
	SIGNAL_SURFACE_STATE_FILLED  ,
	SIGNAL_SURFACE_STATE_PROCESSING
};

enum {
	SIGNAL_CHANNEL_STATE_IDLE  ,
	SIGNAL_CHANNEL_STATE_ACTIVE ,
	SIGNAL_CHANNEL_STATE_TRIGGER
};

enum {
	SIGNAL_ASM_STATE_IDLE  ,
	SIGNAL_ASM_STATE_GRABSYNC ,
	SIGNAL_ASM_STATE_GRABDELAY ,
	SIGNAL_ASM_STATE_START_ACQ ,
	SIGNAL_ASM_STATE_END_ACQ 
};

#endif

#include "EC_Surface.h"


// ****************************************************************************
// System information
//
#ifndef __EC_SYSTEM_INFO
#define	__EC_SYSTEM_INFO

#define EC_MAX_SOURCE	30 
#define EC_MAX_BOARD	30

enum t_BoardType {
	EC_BOARD_TYPE_UNKNOWN = 0x0,
	EC_BOARD_TYPE_PICOLO = 0x1,			// Picolo			
	EC_BOARD_TYPE_PICOLO_PRO = 0x2,		// Picolo Pro
	EC_BOARD_TYPE_PICOLO_PRO2 = 0x4,	// Picolo Pro 2
	EC_BOARD_TYPE_PICOLO_PRO3i =0x10,	// Picolo Pro 3 I
	EC_BOARD_TYPE_PICOLO_PRO3e = 0x20,	// Picolo Pro 3 E
	EC_BOARD_TYPE_PICOLO_TETRA = 0x80,	// Picolo Tetra
	EC_BOARD_TYPE_JUNIOR_4 = 0x10000,	// Junior 4
	EC_BOARD_TYPE_PICOLO_TETRA_X = 0x100000, // Picolo Tetra-X
	EC_BOARD_TYPE_PICOLO_TETRA_X_RC = 0x200000 // Picolo Tetra-X-RC
};

#endif

#define ECSOURCE_STATE_USED				 0
#define ECSOURCE_STATE_AVAILABLE		-1
#define ECSOURCE_STATE_NOT_AVAILABLE	-2

typedef struct t_SourceInfo {
	INT32 State ;
	INT32 DeviceID ;
} ECSOURCEINFO, *PECSOURCEINFO;

typedef struct t_BoardInfo {
	UINT32 BoardType;
	UINT32 SerialNumber;
	CHAR   InternalName [16] ;
	UINT32 PciPosition ;
	UINT32 FirmwareRevision;
	UINT32 SourceCount;
	ECSOURCEINFO SourceList[EC_MAX_SOURCE];
} ECBOARDINFO, *PECBOARDINFO;

typedef struct t_BoardInfoEx {
	UINT32 BoardType;
	UINT32 SerialNumber;
	CHAR   InternalName [16] ;
	UINT32 PciPosition ;
	UINT32 FirmwareRevision;
	UINT32 SourceCount;
	ECSOURCEINFO SourceList[EC_MAX_SOURCE];
	UINT32 Size;
	UCHAR  HardwareKey[8];	
} ECBOARDINFOEX, *PECBOARDINFOEX;

// ****************************************************************************
// A.P.I. Functions
//
#ifndef MC_DYNAMIC_BINDING
#ifdef __cplusplus
extern "C" {
#endif 

// -----------------------------------------------------------------------
// System
// Start / Stop
ECSTATUS DllEntry MultiCamSystemInitialize();
ECSTATUS DllEntry MultiCamSystemTerminate();

// System configuration
ECSTATUS DllEntry MultiCamSystemGetBoardInfo(PECBOARDINFO boardList, UINT32 listCount, PUINT32 returnedCount);
ECSTATUS DllEntry MultiCamSystemGetBoardInfoEx(PECBOARDINFOEX boardList, UINT32 listCount, PUINT32 returnedCount);
ECSTATUS DllEntry MultiCamSystemSetBoardName (UINT32 boardID, PCCHAR name);
ECSTATUS DllEntry MultiCamSystemSetOemKey (UINT32 boardID, PVOID key);
ECSTATUS DllEntry MultiCamSystemCheckOemKey (UINT32 boardID, PVOID key);


// Acquisition
ECSTATUS DllEntry MultiCamSystemAcquisitionStart ();
ECSTATUS DllEntry MultiCamSystemAcquisitionStop ();

// Signal
ECSTATUS DllEntry MultiCamSignalRegister(UINT32 EventID, ECEVENTHANDLER handler, PVOID pInfo );
ECSTATUS DllEntry MultiCamSignalUnregister(UINT32 EventID);
ECSTATUS DllEntry MultiCamSignalMask (UINT32 EventID, UINT32 Mask);
ECSTATUS DllEntry MultiCamSignalWait (UINT32 EventID);
ECSTATUS DllEntry MultiCamSignalTrigger (PECEVENTINFO pEventInfo);

// -----------------------------------------------------------------------
// Surface
ECHANDLE DllEntry MultiCamSurfaceCreate(PECSURFACEINFO pSurfaceInfo);
ECSTATUS DllEntry MultiCamSurfaceDelete(ECHANDLE handle);
ECSTATUS DllEntry MultiCamSurfaceGetParameterInt (ECHANDLE hSurface, ECPARAMID ParamID, PINT32 pValue );
ECSTATUS DllEntry MultiCamSurfaceGetParameterInt64 (ECHANDLE hSurface, ECPARAMID ParamID, PINT64 pValue );

// -----------------------------------------------------------------------
// Channel
ECHANDLE DllEntry MultiCamChannelCreate(PCCHAR ChannelConfigurationFile, PCCHAR AsmIdentification, UINT32 SourceID);
ECSTATUS DllEntry MultiCamChannelSave(PCCHAR filename);
ECSTATUS DllEntry MultiCamChannelDelete(ECHANDLE hChannel);
ECSTATUS DllEntry MultiCamChannelAddSurface(ECHANDLE hChannel, ECHANDLE hSurface);

ECSTATUS DllEntry MultiCamChannelSetParameterInt (ECHANDLE hChannel, ECPARAMID ParamID, INT32 Value );
ECSTATUS DllEntry MultiCamChannelGetParameterInt (ECHANDLE hChannel, ECPARAMID ParamID, PINT32 pValue );
ECSTATUS DllEntry MultiCamChannelSetParameterFloat (ECHANDLE hChannel, ECPARAMID ParamID, FLOAT32 Value );
ECSTATUS DllEntry MultiCamChannelGetParameterFloat (ECHANDLE hChannel, ECPARAMID ParamID, PFLOAT32 pValue );
ECSTATUS DllEntry MultiCamChannelSetParameterString (ECHANDLE hChannel, ECPARAMID ParamID, PCCHAR Value );
ECSTATUS DllEntry MultiCamChannelGetParameterString (ECHANDLE hChannel, ECPARAMID ParamID, PCHAR Value, UINT32 MaxLength );

// -----------------------------------------------------------------------
// Board
ECSTATUS DllEntry MultiCamSystemGetBoardParam(ECHANDLE hBoard,
											  ECPARAMID ParamID, PUINT32 pValue);
ECSTATUS DllEntry MultiCamSystemSetBoardParam(ECHANDLE hBoard,
											  ECPARAMID ParamID, UINT32 Value);
ECSTATUS DllEntry MultiCamSystemResetWatchdogTimer(ECHANDLE hBoard);
ECSTATUS DllEntry MultiCamSystemPutChar(ECHANDLE hBoard, UINT8 Value);
ECSTATUS DllEntry MultiCamSystemGetChar(ECHANDLE hBoard, PUINT8 pValue);

#ifdef __cplusplus
} ;
#endif 

#endif // MC_DYNAMIC_BINDING

// Generic test for success on any status value (non-negative numbers
// indicate success).
#define ECSUCCESS(Status) ((ECSTATUS)(Status) >= 0)
// and the inverse
#define ECFAILED(Status) ((ECSTATUS)(Status)<0)

#endif // __MULTICAM32_PICOLO__

