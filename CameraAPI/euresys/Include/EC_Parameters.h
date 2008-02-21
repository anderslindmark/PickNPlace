// ****************************************************************************
// EC_Parametes.h - Revision 3.6.3
//

// ****************************************************************************
// MultiCam Channel Parameters 
//	
#ifndef __EC_PARAMETERS_ID
#define __EC_PARAMETERS_ID

// ****************************************************************************
// MultiCam Channel Parameters : Parameter ID + specific values
//

// FileNames
#define	EC_PARAM_FileName		0x10	// Channel Configuration File
#define	EC_PARAM_TdfFile		0x11	// EasyCam TDF file


// Model
#define	EC_PARAM_Camera			0x0		// Model Camera Designator
#define	EC_PARAM_Operation		0x1		// Operationnal Mode for the Camera


// Geometric
#define	EC_PARAM_ImageScaleX	0x3B	// Horizontal scaling factor
#define	EC_PARAM_ImageSizeX		0x3C	// Horizontal size in pixel
#define	EC_PARAM_ImageOffsetX	0x3D	// Horizontal offset in pixel
#define	EC_PARAM_ImageScaleY	0x3E	// Vertical scaling factor
#define	EC_PARAM_ImageSizeY		0x3F	// Vertical size in pixel
#define	EC_PARAM_ImageOffsetY	0x40	// Vertical offset in pixel
#define	EC_PARAM_ImageFlipX		0x41	// Flip X direction
#define	EC_PARAM_ImageFlipY		0x42	// Flip Y direction
#define	EC_PARAM_ImageTranspose	0x43	// Permutation of lines and rows
#define	EC_PARAM_PicTmgScaleX	0x2		// Picolo specific Horizontal scaling factor
#define	EC_PARAM_PicTmgSizeX	0x3		// Picolo specific Horizontal size in pixel
#define	EC_PARAM_PicTmgOffsetX	0x4		// Picolo specific orizontal offset in pixel
#define	EC_PARAM_PicTmgScaleY	0x5		// Picolo specific Vertical scaling factor
#define	EC_PARAM_PicTmgSizeY	0x6		// Picolo specific Vertical size in pixel
#define	EC_PARAM_PicTmgOffsetY	0x7		// Picolo specific Vertical offset in pixel

// Exposure
#define	EC_PARAM_ShutterSpeed	0x8		// Exposure Time in seconds (-1 = no control)
#define	EC_PARAM_ExpMode		0x9		// Exposure mode (Fast or Slow)
#define	EC_PARAM_StrobeDur		0xA		// Storbe duration (in sec)
#define	EC_PARAM_StrobePos		0xB		// Programmable location (in sec)
#define	EC_PARAM_DualFlash		0xC		// Flash Pulse (1 or 2)

enum {
	EC_EXPOSURE_MODE_FAST,
	EC_EXPOSURE_MODE_SLOW
};


// Features
#define	EC_PARAM_Standard		0xD		// CCIR or EIA
#define	EC_PARAM_Scanning		0xE		// Progressive or interlaced
#define	EC_PARAM_Resolution		0xF		// Square, Lowres, ...
#define	EC_PARAM_FieldMode		0x12	// 2 (interlaced) or 1(progressive)
#define EC_PARAM_AcqColFmt		0x92	// Color Format

enum {
	EC_STANDARD_CCIR,
	EC_STANDARD_EIA,
	EC_STANDARD_PAL,
	EC_STANDARD_NTSC,
	EC_STANDARD_SECAM
};

enum {
	EC_SCANNING_INTERLACED,
	EC_SCANNING_PROGRESSIVE
};

enum {
	EC_RESOLUTION_SQUARE,
	EC_RESOLUTION_LOWRES,
	EC_RESOLUTION_BROADCAST,
	EC_RESOLUTION_SONY,
	EC_RESOLUTION_HALFLINE
};

enum {
	EC_FIELDMODE_INTERLACED = 2 ,
	EC_FIELDMODE_PROGRESSIVE = 1
};

enum {
	EC_COLORFORMAT_Y8,
	EC_COLORFORMAT_RGB32,
	EC_COLORFORMAT_RGB24,
	EC_COLORFORMAT_RGB16,
	EC_COLORFORMAT_RGB15,
	EC_COLORFORMAT_YUV422,
	EC_COLORFORMAT_YUV411,
	EC_COLORFORMAT_PLANAR_YUV422,
	EC_COLORFORMAT_PLANAR_YUV411,
	EC_COLORFORMAT_PLANAR_YUV420,
	EC_COLORFORMAT_PLANAR_YUV410,
	EC_COLORFORMAT_PLANAR_YVU410,
	EC_COLORFORMAT_PLANAR_YVU420,
	MC_COLORFORMAT_YUV422,
	MC_COLORFORMAT_YUV411,
	MC_COLORFORMAT_PLANAR_YUV422,
	MC_COLORFORMAT_PLANAR_YUV411,
	MC_COLORFORMAT_PLANAR_YUV420,
	MC_COLORFORMAT_PLANAR_YUV410,
	MC_COLORFORMAT_PLANAR_YVU410,
	MC_COLORFORMAT_PLANAR_YVU420
};

#define MC_COLORFORMAT_Y8 EC_COLORFORMAT_Y8
#define MC_COLORFORMAT_RGB32 EC_COLORFORMAT_RGB32
#define MC_COLORFORMAT_RGB24 EC_COLORFORMAT_RGB24
#define MC_COLORFORMAT_RGB16 EC_COLORFORMAT_RGB16
#define MC_COLORFORMAT_RGB15 EC_COLORFORMAT_RGB15

// System
#define	EC_PARAM_CablePN		0x13	// Cable P/N
#define	EC_PARAM_CableAD		0x14	// Cable Auto-Detection I/O lines
#define	EC_PARAM_CableID		0x15	// Cable Auto-Detection ID
#define	EC_PARAM_ShutterAD		0x16	// Shutter I/O lines
#define	EC_PARAM_SystStrobe		0x18	// I/O line used  for Syst. Strobe
#define	EC_PARAM_StrobeQuiescent 0x19	// Innactive logic state for the strobe

#define	EC_PARAM_SystTriggerBoardName	0x3A	// Name of the board used  for Syst. Trigger
#define	EC_PARAM_SystTriggerLine		0x17	// I/O line used  for Syst. Trigger


// Synchronisation
#define	EC_PARAM_LockMode		0x1A	// Sensitivity of the PLL during vertical interval
#define	EC_PARAM_Horizontal		0x1B	// H drive
#define	EC_PARAM_Vertical		0x1C	// V drive
#define	EC_PARAM_HorSyncIn		0x1D	// Incoming H
#define	EC_PARAM_VerSyncIn		0x1E	// Incoming V

enum {
	EC_LOCKMODE_NORMAL,
	EC_LOCKMODE_SWITCH,
	EC_LOCKMODE_VCRLOCK
};

enum {
	EC_HORIZONTAL_NONE,
	EC_HORIZONTAL_NORMAL,
	EC_HORIZONTAL_ADVANCED,
	EC_HORIZONTAL_COMPOSITE
};

enum {
	EC_VERTICAL_NONE,
	EC_VERTICAL_SHORT,
	EC_VERTICAL_LONG
};

enum {
	EC_HORSYNCIN_NONE,
	EC_HORSYNCIN_HSYNC,
	EC_HORSYNCIN_CLOCKDV
};

enum {
	EC_VERSYNCIN_NONE,
	EC_VERSYNCIN_PARITY,
	EC_VERSYNCIN_VSYNC,
	EC_VERSYNCIN_VALDV,
	EC_VERSYNCIN_VALDH
};


// Acquisition
#define EC_PARAM_AcqOnUp		0x1F	// First line number for UP or for Progressive frame
#define EC_PARAM_AcqLenUp		0x20	// Number of Lines for UP or for Progressive frame
#define EC_PARAM_AcqOnDw		0x21	// First line number for DW
#define EC_PARAM_AcqLenDw		0x22	// Number of Lines for DW
#define EC_PARAM_AcqOnT			0x23	// ...


// Timing
#define EC_PARAM_LineDuration	0x24	// (in sec) Duration of the total video line
#define EC_PARAM_PixelFrequency	0x25	// (in Hertz) sampling frequency
#define EC_PARAM_ClockCode		0x26	// Hex code (Domino firmware)
#define EC_PARAM_ClockDivider	0x27	// Pre scaling used by Domino
#define EC_PARAM_PixelDuration	0x28	// (in sec) Inverse of the sampling frequency


// Format
#define EC_PARAM_SensorSizeX	0x29	// H size of CCD sensor (in pixels at sampling freq)
#define EC_PARAM_SensorSizeY	0x2A	// V size of CCD sensor (in lines)
#define EC_PARAM_TotalLine		0x2B	// Total number of line (625 or 525)
#define EC_PARAM_LineLength		0x2C	// Total length of the scanning line (in )
#define EC_PARAM_PreCall		0x2D	// Setup time (in lines)


// HorSyncOut
#define EC_PARAM_HorQuiescent	0x2E	// Inactive state 
#define EC_PARAM_HorOnT			0x2F	// Delay between reference pos and start of pulse (in sec)
#define EC_PARAM_HorDurT		0x30	// Duration of the pulse (in sec)


// VerSyncOut
#define EC_PARAM_VerQuiescent	0x31	// Inactive State
#define EC_PARAM_VerOnUp		0x32	// Line number of the first line of the vertical driving pulse marking the UP field or the frame
#define EC_PARAM_VerOnUpT		0x33	// Delay (in sec) between ref. in the line and the start of the VD pulse marking the UP field
#define EC_PARAM_VerOffUp		0x34	// Line number of the last line of the VD pulse marking the uP field
#define EC_PARAM_VerOffUpT		0x35	// Delay (in sec) between ref. in the line and the end of the VD pulse marking the UP field
#define EC_PARAM_VerOnDw		0x36	// ..
#define EC_PARAM_VerOnDwT		0x37	// ..  idem for DW
#define EC_PARAM_VerOffDw		0x38	// ..
#define EC_PARAM_VerOffDwT		0x39	// ..


// Inhibit
#define EC_PARAM_InhOnUp		0x50	// Line number of the first line of the inhibit for UP
#define EC_PARAM_InhOffUp		0x51	// Line number of the Last line of the inhibit for UP
#define EC_PARAM_InhOnDw		0x52	// Line number of the first line of the inhibit for DW
#define EC_PARAM_InhOffDw		0x53	// Line number of the Last line of the inhibit for DW
#define EC_PARAM_InhTogT		0x54	// Delay between ref in line an exact position of toggling point


// Clamp
#define EC_PARAM_ClmOnUp		0x55	// Line number
#define EC_PARAM_ClmOffUp		0x56	// Line number
#define EC_PARAM_ClmOnDw		0x57	// Line number
#define EC_PARAM_ClmOffDw		0x58	// Line number
#define EC_PARAM_ClmOnT			0x59	// (in sec)
#define EC_PARAM_ClmDurT		0x5A	// (in sec)


// Sequences
#define EC_PARAM_BeginUp		0x5B	// Line number
#define EC_PARAM_EndUp			0x5C	// Line number
#define EC_PARAM_LengthUp		0x5D	// (in lines)
#define EC_PARAM_BeginDw		0x5E	// Line number
#define EC_PARAM_EndDw			0x5F	// Line number
#define EC_PARAM_LengthDw		0x60	// (in lines)
#define EC_PARAM_BeginPr		0x61	// Line number
#define EC_PARAM_EndPr			0x62	// Line number
#define EC_PARAM_LengthPr		0x63	// (in lines)


// Signals 
#define EC_PARAM_End			0x64	// Pattern for end of line
#define EC_PARAM_Mid			0x65	// Pattern for middle of line
#define EC_PARAM_ACQ			0x66	// Pattern for Acquisition Gate
#define EC_PARAM_Line			0x67	// Pattern for acquisition line phys number
#define EC_PARAM_CallAcq		0x68	// Pattern for the calling signal notifying the acquisition
#define EC_PARAM_CallUser		0x69	// Pattern for the calling signal notifying a user function
#define EC_PARAM_QH				0x6A	// Pattern for HD
#define EC_PARAM_QV				0x6B	// Pattern for VD
#define EC_PARAM_INH			0x6C	// Pattern for INHIBIT
#define EC_PARAM_CLM			0x6D	// Pattern for CLAMP
#define EC_PARAM_Q_1			0x6E	// Pattern for gp signal 1
#define EC_PARAM_Q_2			0x6F	// Pattern for gp signal 1
#define EC_PARAM_Q_3			0x70	// Pattern for gp signal 1


// Camera Specific
#define EC_PARAM_CamRstLock		0x71	//
#define EC_PARAM_CamRstDur		0x72	//
#define EC_PARAM_CamRstGap		0x73	//
#define EC_PARAM_CamPreRst		0x74	//
#define EC_PARAM_CamExpAdjust	0x75	//
#define EC_PARAM_CamDrainDly	0x76	//


// Transfer Gate
#define EC_PARAM_SGUp			0x80	// Line number
#define EC_PARAM_SGUpT			0x81	// Delay (in sec)
#define EC_PARAM_SGDw			0x82	// Line number
#define EC_PARAM_SGDwT			0x83	// Delay (in sec)


// Call User
#define EC_PARAM_CallUser1		0x84	// Line number
#define EC_PARAM_CallUser2		0x85	// Line number
#define EC_PARAM_CallUser3		0x86	// Line number
#define EC_PARAM_CallUser4		0x87	// Line number


// Video 
#define EC_PARAM_AcqSource		0x88	// Acquisition source (on the spec. board)
#define EC_PARAM_SyncSource		0x89	// Sync Input


// Filters
#define EC_PARAM_ColorTrap		0x8A	// Color Trap
#define EC_PARAM_VideoFilter	0x8B	// Antialiasing
#define	EC_PARAM_Coring			0x8C	// Coring
#define EC_PARAM_VerticalYComb	0xA6	// Picolo vertical luma scaling filter (comb)
#define EC_PARAM_VerticalCComb	0xA7	// Picolo vertical chroma scaling filter
#define EC_PARAM_CAGC			0xA8	// Picolo chroma AGC
#define EC_PARAM_CKILL			0xA9	// Picolo low chroma detection & removal
#define EC_PARAM_Gamma			0xAA	// Picolo gamma correction removal : 1 = enable gamma correction removal; 0 disables gamma correction removal

enum {
	EC_COLORTRAP_NONE,
	EC_COLORTRAP_PAL,
	EC_COLORTRAP_NTSC
};

enum {
	EC_VIDEOFILTER_NONE,		
	EC_VIDEOFILTER_LP8MHZ,		// Domino only
	EC_VIDEOFILTER_LP5MHZ,		// Domino only
	EC_VIDEOFILTER_LP2MHZ,		// Domino only
	EC_VIDEOFILTER_LP_NORMAL,	// Picolo Pro only
	EC_VIDEOFILTER_LP_AUTO,		// Picolo only
	EC_VIDEOFILTER_LP_MIN,		// Picolo (Pro) only
	EC_VIDEOFILTER_LP_MED,		// Picolo (Pro) only
	EC_VIDEOFILTER_LP_MAX		// Picolo (Pro) only
};

enum {
	EC_CORING_NONE,
	EC_CORING_8,
	EC_CORING_16,
	EC_CORING_32
};

enum {
	EC_VERTYCOMB_ZORDER1 ,
	EC_VERTYCOMB_ZORDER2 ,
	EC_VERTYCOMB_ZORDER3 ,
	EC_VERTYCOMB_ZORDER4 ,
	EC_VERTYCOMB_INTERPOLATION ,
	EC_VERTYCOMB_INTERPOLATION_ZORDER1 ,
	EC_VERTYCOMB_INTERPOLATION_ZORDER2 ,
	EC_VERTYCOMB_INTERPOLATION_ZORDER3
};

enum {
	EC_VERTCCOMB_ENABLE ,
	EC_VERTCCOMB_DISABLE
};


// Acquisition Dynamic
#define EC_PARAM_VideoGain		0x8D	// Gain
#define EC_PARAM_VideoOffset	0x8E	// Offset
#define EC_PARAM_VideoUGain		0x8F	// U Gain
#define EC_PARAM_VideoVGain		0x90	// V Gain
#define EC_PARAM_VideoHue		0x91	// This parameter is kept for compatibility issue only. Please use EC_PARAM_VideoNtscHue.
#define EC_PARAM_VideoNtscHue	0x77	// Hue
#define EC_PARAM_AcqMinVal		0x93	// Acquisition range minimum value
#define EC_PARAM_AcqMaxVal		0x94	// Acquisition range maximum value



// Channel Acquisition Sequence
#define EC_PARAM_InitPause			0x95	// 
#define EC_PARAM_InitTrigger		0x96	//
#define EC_PARAM_InitGrabSync		0x97	//
#define EC_PARAM_InitGrabDelay		0x98	//
#define EC_PARAM_RepeatPause		0x99	//
#define EC_PARAM_RepeatTrigger		0x9A	//
#define EC_PARAM_RepeatGrabSync		0x9B	//
#define EC_PARAM_RepeatGrabDelay	0x9C	//	
#define EC_PARAM_RepeatGrabCount	0x9D	//

#ifndef __EC_PARAM_acq
#define __EC_PARAM_acq

enum {
	INIT_TRIGGER_PAUSE ,
	INIT_TRIGGER_EXT_HIGH ,
	INIT_TRIGGER_EXT_LOW ,
	INIT_TRIGGER_EXT_GOING_HI ,
	INIT_TRIGGER_EXT_GOING_LOW ,
	INIT_TRIGGER_EXT_GOING_ANY 
};

enum {
	GRABSYNC_NEXT ,
	GRABSYNC_NEXT_UP ,
	GRABSYNC_NEXT_DOWN ,
	GRABSYNC_ASYNC
};

enum {
	REPEAT_TRIGGER_PAUSE ,
	REPEAT_TRIGGER_EXT_HIGH ,
	REPEAT_TRIGGER_EXT_LOW ,
	REPEAT_TRIGGER_EXT_GOING_HI ,
	REPEAT_TRIGGER_EXT_GOING_LOW ,
	REPEAT_TRIGGER_EXT_GOING_ANY 
};

enum {
	TRIGGER_PAUSE ,
	TRIGGER_EXT_HIGH ,
	TRIGGER_EXT_LOW ,
	TRIGGER_EXT_GOING_HI ,
	TRIGGER_EXT_GOING_LOW ,
	TRIGGER_EXT_GOING_ANY 
};


#endif

// Channel Trigger Param
#define EC_PARAM_TriggerMode		0x9E	//
#define EC_PARAM_TriggerMask		0x9F	//
#define EC_PARAM_AssemblerMask		0xA0	//

#ifndef __EC_PARAM_tri
#define __EC_PARAM_tri

enum {
	TRIGGERMODE_AUTO ,
	TRIGGERMODE_SYSTEM
};

enum {
	TRIGGERMASK_NONE ,
	TRIGGERMASK_SKIP ,
	TRIGGERMASK_DELAY_TRIGGER ,
	TRIGGERMASK_DELAY_REPEAT ,
	TRIGGERMASK_STOP ,
	TRIGGERMASK_BYPASS
};

enum {
	ASMMASK__SKIP ,
	ASMMASK__DELAY ,
	ASMMASK__STOP
};

#endif

// Channel Surface descr.
#define EC_PARAM_SurfaceType		0xA1	//


// Channel Param.
#define EC_PARAM_ChannelState		 0xA3	//
#define EC_PARAM_ChannelSurfaceCount 0xA4	//
#define EC_PARAM_ChannelTimeCode	 0xA5	//
#define EC_PARAM_ChannelContext		 0x78	//
#define EC_PARAM_ChannelOperation	 0x45	// 

#ifndef __EC_PARAM_cha
#define __EC_PARAM_cha

enum {
	CHANNEL_STATE_IDLE,		
	CHANNEL_STATE_ACTIVE
};

enum {
	CHANNEL_ACTIVITY_OFFLINE,		
	CHANNEL_ACTIVITY_ONLINE
};

enum {
	CHANNEL_OPERATION_IMAGE,
	CHANNEL_OPERATION_SEQUENCE, 
	CHANNEL_OPERATION_IMAGE_MASTER,
	CHANNEL_OPERATION_SEQUENCE_MASTER
};

#endif


// External Mux
#define EC_PARAM_ExternalMux		0x4B	// "ExternalMux" mode : 1=yes ; 0=no - default is 0


// System Trigger & I/O lines
#define EC_PARAM_DigitalIoControl	0x4C	// IO lines control string
#define EC_PARAM_DigitalIoConfig	0x4D	// IO lines config string
#define EC_PARAM_DigitalIoStatus	0x4E	// IO lines status - read only


// WatchDog parameters
#define EC_PARAM_WatchDog			0x4F
#define EC_PARAM_BootTimeout		0x7B
#define EC_PARAM_ApplicationTimeout	0x7C
#define EC_PARAM_WatchDogConfig		0x7D

#define WATCHDOG_PULSE				0x1
#define WATCHDOG_OFF				0x0
#define WATCHDOG_LONG				0x2
#define WATCHDOG_SHORT				0x4
#define WATCHDOG_SWITCH_ON			0x8

enum {
	WATCHDOG_ENABLE,
	WATCHDOG_DISABLE,
	WATCHDOG_RESTART
};


// Alarm parameters
#define EC_PARAM_AlarmConfig		0xB0
#define EC_PARAM_AlarmTimeout		0xB1

enum {
	ALARM_ENABLE,
	ALARM_DISABLE,
	ALARM_RESTART
};


// Serial Line parameters
#define EC_PARAM_SerialCfg			0x79
#define SERIAL_2_STOP_BITS			1<<6
#define SERIAL_PARITY_BIT			1<<5 
#define SERIAL_SEND_7_BITS			1<<4
			
#define SERIAL_RATE_115K			0x1
#define SERIAL_RATE_115200			0x1
#define SERIAL_RATE_57K				0x2
#define SERIAL_RATE_57600			0x2
#define SERIAL_RATE_28K				0x3
#define SERIAL_RATE_28800			0x3
#define SERIAL_RATE_19200			0xA
#define SERIAL_RATE_14K				0x4
#define SERIAL_RATE_14400			0x4
#define SERIAL_RATE_9600			11
#define SERIAL_RATE_2400			13
#define SERIAL_RATE_600				15

#define EC_PARAM_Serial_RTX			0x7A
#define SERIAL_NO_DATA				0xFFFF


// Thread parameters
#define EC_PARAM_SPL_PtrCpyThreadArray		0x7F


// Source Parameter
#define EC_PARAM_VfWSource			0xB2


// I/O parameters
#define EC_PARAM_InputConfig				0x100
#define EC_PARAM_OutputConfig				0x200
#define EC_PARAM_InputFunction				0x300
#define EC_PARAM_OutputFunction				0x400
#define EC_PARAM_InputState					0x500
#define EC_PARAM_OutputState				0x600
#define EC_PARAM_ModuleCheck				0x700


// ******************
// I/O lines indexing
// 

// Picolo Classic & Picolo Pro

enum {
	P_IN1 = 1,
	P_IN2 = 2,
	P_IN3 = 3,
	P_IN4 = 4
};

enum {
	P_OUT1 = 1,
	P_OUT2 = 2,
	P_OUT3 = 3,
	P_OUT4 = 4
};

// Picolo Pro 2

enum {
	PP2_IN1 = 1,
	PP2_IN2 = 2,
	PP2_IN3 = 3,
	PP2_IN4 = 4,
	PP2_IN5 = 5,
	PP2_IN6 = 6,
	PP2_IN7 = 7,
	PP2_IN8 = 8,
	PP2_IN9 = 9,
	PP2_IN10 = 10,
	PP2_IN11 = 11,
	PP2_IN12 = 12,
	PP2_IN13 = 13,
	PP2_INTR = 14
};

enum {
	PP2_OUT1 = 1,
	PP2_OUT2 = 2,
	PP2_OUT3 = 3,
	PP2_OUT4 = 4,
	PP2_OUT5 = 5,
	PP2_OUT6 = 6,
	PP2_OUT7 = 7,
	PP2_OUT8 = 8,
	PP2_OUT9 = 9,
	PP2_OUT10 = 10,
	PP2_OUT11 = 11,
	PP2_OUT12 = 12,
	PP2_OUT13 = 13
};

// Picolo Pro 3I

enum {
	PP3I_IN1 = 1,
	PP3I_IN2 = 2,
	PP3I_IN3 = 3,
	PP3I_IN4 = 4,
	PP3I_IN5 = 5,
	PP3I_IN1_0 = 6,
	PP3I_IN2_0 = 7,
	PP3I_IN3_0 = 8,
	PP3I_IN4_0 = 9,
	PP3I_IN5_0 = 10,
	PP3I_IN1_1 = 11,
	PP3I_IN2_1 = 12,
	PP3I_IN3_1 = 13,
	PP3I_IN4_1 = 14,
	PP3I_IN5_1 = 15,
	PP3I_IN1_2 = 16,
	PP3I_IN2_2 = 17,
	PP3I_IN3_2 = 18,
	PP3I_IN4_2 = 19,
	PP3I_IN5_2 = 20
};

enum {
	PP3I_OUT1 = 1,
	PP3I_OUT2 = 2,
	PP3I_OUT3 = 3,
	PP3I_OUT4 = 4,
	PP3I_OUT5 = 5,
	PP3I_OUT1_0 = 6,
	PP3I_OUT2_0 = 7,
	PP3I_OUT3_0 = 8,
	PP3I_OUT4_0 = 9,
	PP3I_OUT5_0 = 10,
	PP3I_OUT1_1 = 11,
	PP3I_OUT2_1 = 12,
	PP3I_OUT3_1 = 13,
	PP3I_OUT4_1 = 14,
	PP3I_OUT5_1 = 15,
	PP3I_OUT1_2 = 16,
	PP3I_OUT2_2 = 17,
	PP3I_OUT3_2 = 18,
	PP3I_OUT4_2 = 19,
	PP3I_OUT5_2 = 20
};

// Picolo Pro 3E

enum {
	PP3E_IN1_0 = 1,
	PP3E_IN2_0 = 2,
	PP3E_IN3_0 = 3,
	PP3E_IN4_0 = 4,
	PP3E_IN5_0 = 5,
	PP3E_IN1_1 = 6,
	PP3E_IN2_1 = 7,
	PP3E_IN3_1 = 8,
	PP3E_IN4_1 = 9,
	PP3E_IN5_1 = 10,
	PP3E_IN1_2 = 11,
	PP3E_IN2_2 = 12,
	PP3E_IN3_2 = 13,
	PP3E_IN4_2 = 14,
	PP3E_IN5_2 = 15,
	PP3E_IN1_3 = 16,
	PP3E_IN2_3 = 17,
	PP3E_IN3_3 = 18,
	PP3E_IN4_3 = 19,
	PP3E_IN5_3 = 20
};

enum {
	PP3E_OUT1_0 = 1,
	PP3E_OUT2_0 = 2,
	PP3E_OUT3_0 = 3,
	PP3E_OUT4_0 = 4,
	PP3E_OUT5_0 = 5,
	PP3E_OUT1_1 = 6,
	PP3E_OUT2_1 = 7,
	PP3E_OUT3_1 = 8,
	PP3E_OUT4_1 = 9,
	PP3E_OUT5_1 = 10,
	PP3E_OUT1_2 = 11,
	PP3E_OUT2_2 = 12,
	PP3E_OUT3_2 = 13,
	PP3E_OUT4_2 = 14,
	PP3E_OUT5_2 = 15,
	PP3E_OUT1_3 = 16,
	PP3E_OUT2_3 = 17,
	PP3E_OUT3_3 = 18,
	PP3E_OUT4_3 = 19,
	PP3E_OUT5_3 = 20
};


// MIO Module
enum {
	I1_0 = 21,
	I2_0 = 22,
	I3_0 = 23,
	I4_0 = 24,
	I1_1 = 25,
	I2_1 = 26,
	I3_1 = 27,
	I4_1 = 28,
	I1_2 = 29,
	I2_2 = 30,
	I3_2 = 31,
	I4_2 = 32,
	I1_3 = 33,
	I2_3 = 34,
	I3_3 = 35,
	I4_3 = 36,
	I1_4 = 37,
	I2_4 = 38,
	I3_4 = 39,
	I4_4 = 40
};

enum {
	O1_0 = 21,
	O2_0 = 22,
	O3_0 = 23,
	O4_0 = 24,
	O1_1 = 25,
	O2_1 = 26,
	O3_1 = 27,
	O4_1 = 28,
	O1_2 = 29,
	O2_2 = 30,
	O3_2 = 31,
	O4_2 = 32,
	O1_3 = 33,
	O2_3 = 34,
	O3_3 = 35,
	O4_3 = 36,
	O1_4 = 37,
	O2_4 = 38,
	O3_4 = 39,
	O4_4 = 40
};

// Tetra
enum {
	TETRA_IN1 = 1,
	TETRA_IN2 = 2,
	TETRA_IN3 = 3,
	TETRA_IN4 = 4,
	TETRA_IN5 = 5,
	TETRA_IN6 = 6,
	TETRA_IN7 = 7,
	TETRA_IN8 = 8,
	TETRA_IN9 = 9,
	TETRA_IN10 = 10,
	TETRA_IN11 = 11,
	TETRA_IN12 = 12,
	TETRA_IN13 = 13,
	TETRA_INTR = 14
};

enum {
	TETRA_OUT1 = 1,
	TETRA_OUT2 = 2,
	TETRA_OUT3 = 3,
	TETRA_OUT4 = 4,
	TETRA_OUT5 = 5,
	TETRA_OUT6 = 6,
	TETRA_OUT7 = 7,
	TETRA_OUT8 = 8,
	TETRA_OUT9 = 9,
	TETRA_OUT10 = 10,
	TETRA_OUT11 = 11,
	TETRA_OUT12 = 12,
	TETRA_OUT13 = 13
};

enum {
	MODULE_CHECK_MIO_0,
	MODULE_CHECK_MIO_1,
	MODULE_CHECK_MIO_2,
	MODULE_CHECK_MIO_3,
	MODULE_CHECK_MIO_4,
	MODULE_CHECK_MV4_0,
	MODULE_CHECK_MV4_1,
	MODULE_CHECK_MV4_2,
	MODULE_CHECK_MV4_3,
	MODULE_CHECK_MV12,
	MODULE_CHECK_MIO_SB
};

enum {
	OUTPUT_FUNCTION_UNKNOWN,
	OUTPUT_FUNCTION_SOFT,
	OUTPUT_FUNCTION_WATCHDOG,
	OUTPUT_FUNCTION_ALARM,
	OUTPUT_FUNCTION_INPUT,
};

enum {
	INPUT_FUNCTION_UNKNOWN,
	INPUT_FUNCTION_SOFT,
	INPUT_FUNCTION_OUTPUT,
	INPUT_FUNCTION_TRIG
};

enum {
	OUTPUT_CONFIG_UNKNOWN,
	OUTPUT_CONFIG_SOFT,
	OUTPUT_CONFIG_WATCHDOG,
	OUTPUT_CONFIG_ALARM
};

enum {
	INPUT_CONFIG_SOFT = 1
};

enum {
	INPUT_STATE_LOW,
	INPUT_STATE_HIGH,
	INPUT_STATE_WENTLOW,
	INPUT_STATE_WENTHIGH,
	INPUT_STATE_NONE
};

enum {
	OUTPUT_STATE_LOW,
	OUTPUT_STATE_HIGH,
	OUTPUT_STATE_WENTLOW,
	OUTPUT_STATE_WENTHIGH,
	OUTPUT_STATE_NONE,
	OUTPUT_STATE_TOGGLE
};

// ******************
// Video lines indexing
// 

// Picolo
enum {
	PICOLO_VID1,
	PICOLO_VID2,
	PICOLO_VID3,
	PICOLO_YC
};

// Picolo Pro 2
enum {
	PRO2_VID1,
	PRO2_VID2,
	PRO2_VID3,
	PRO2_VID4
};

// Picolo Pro 3I and modules
enum {
	PRO3I_VID1,
	PRO3I_VID2,
	PRO3I_VID3,
	PRO3I_VID4,
	PRO3I_VID5,
	PRO3I_VID6,
	PRO3I_VID7,
	PRO3I_VID8,
	PRO3I_VID9,
	PRO3I_VID10,
	PRO3I_VID11,
	PRO3I_VID12,
	PRO3I_VID13,
	PRO3I_VID14,
	PRO3I_VID15,
	PRO3I_VID16
};

#define PRO3I_VID1_0	PRO3I_VID5
#define PRO3I_VID2_0	PRO3I_VID6
#define PRO3I_VID3_0	PRO3I_VID7
#define PRO3I_VID4_0	PRO3I_VID8
#define PRO3I_VID1_1	PRO3I_VID9
#define PRO3I_VID2_1	PRO3I_VID10
#define PRO3I_VID3_1	PRO3I_VID11
#define PRO3I_VID4_1	PRO3I_VID12
#define PRO3I_VID1_2	PRO3I_VID13
#define PRO3I_VID2_2	PRO3I_VID14
#define PRO3I_VID3_2	PRO3I_VID15
#define PRO3I_VID4_2	PRO3I_VID16

// Picolo Pro 3E and modules
enum {
	PRO3E_VID1_0,
	PRO3E_VID2_0,
	PRO3E_VID3_0,
	PRO3E_VID4_0,
	PRO3E_VID1_1,
	PRO3E_VID2_1,
	PRO3E_VID3_1,
	PRO3E_VID4_1,
	PRO3E_VID1_2,
	PRO3E_VID2_2,
	PRO3E_VID3_2,
	PRO3E_VID4_2,
	PRO3E_VID1_3,
	PRO3E_VID2_3,
	PRO3E_VID3_3,
	PRO3E_VID4_3,
	PRO3E_VID1,
	PRO3E_VID2,
	PRO3E_VID3,
	PRO3E_VID4
};

// Picolo TETRA
enum {
	TETRA_VID1,
	TETRA_VID2,
	TETRA_VID3,
	TETRA_VID4,
	TETRA_VID5,
	TETRA_VID6,
	TETRA_VID7,
	TETRA_VID8,
	TETRA_VID9,
	TETRA_VID10,
	TETRA_VID11,
	TETRA_VID12,
	TETRA_VID13,
	TETRA_VID14,
	TETRA_VID15,
	TETRA_VID16
};

// Junior 4
enum {
	VID1,
	VID2,
	VID3,
	VID4
};



// System Trigger Extension
#define	EC_PARAM_SetMaskHigh		0x46
#define	EC_PARAM_SetMaskLow			0x47
#define	EC_PARAM_SetMaskGoingHigh	0x48
#define	EC_PARAM_SetMaskGoingLow	0x49
#define	EC_PARAM_SetMaskGoingAny	0x4A
#define	EC_PARAM_ResetMaskHigh		0xB3
#define	EC_PARAM_ResetMaskLow		0xB4
#define	EC_PARAM_ResetMaskGoingHigh	0xB5
#define	EC_PARAM_ResetMaskGoingLow	0xB6
#define	EC_PARAM_ResetMaskGoingAny	0xB7


// Extended parameters
#define EC_PARAM_FlushCurrentAcquisition	0xB8
#define EC_PARAM_TriggerPoint_Packed		0xAB
#define EC_PARAM_TriggerPoint_Planar1		0xAC
#define EC_PARAM_TriggerPoint_Planar23		0xAD

enum {
	FTP_4 = 0x0,
	FTP_8 = 0x1,
	FTP_16 = 0x2,
	FTP_32 = 0x3
};

#define EC_PARAM_TimeStamp_ms    0xB9
#define EC_PARAM_TimeStamp_s     0xBA

// Maximum Parameter ID
#define EC_MAX_PARAM_ID						0xBB

#endif //__EC_PARAMETERS_ID

//
// available ID's : [ 0xAE - 0xB8 ] [ 0xBA - 0xFF ]
// 

