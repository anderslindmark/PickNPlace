/*---------------------------------------------------------------------*\
|	This is a part of the Euresys Classes C++ library.					|
|	Copyright (C) Euresys												|
|	All rights reserved.												|
|																		|
|	This source code is only intended as a supplement to the			|
|	samples illustrating the use the driver API and related				|
|	electronic documentation provided at this subject.					|
|	See these sources for detailed information regarding the			|
|	Euresys MultiCam product.											|
\*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*\
|	PicoloMultiCamChannel.h: interface for the CPicoloMultiCamChannel class.	|
|	31/5/2000: First version by Godefroid Dislaire						|
|		To do :	remove Sleep(200) in MultiCamTerminate,...				|
\*---------------------------------------------------------------------*/
#if !defined(_PICOLO_MULTICHANNEL_H____INCLUDED_)
#define _PICOLO_MULTICHANNEL_H____INCLUDED_

#pragma warning (disable : 4786)
#include <list>
#pragma warning (default : 4786)

#include <easy.h>
#include <eImage.h>
#include <multicam32.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef void (WINAPI *PCBFUNC_EVISION)(PVOID context,EGenericROI* pROI,BOOL last);
typedef void (WINAPI *PCBFUNC_SURFACE)(PVOID context,ECHANDLE hSurface,BOOL last);
/*---------------------------------------------------------------------*\
|	Macro definitions													|
\*---------------------------------------------------------------------*/
#define DEFINE_PICOLO_MULTICAMCHANNEL_CALLBACK(ClassName,CallBackFuncName,ReturnType)\
static void WINAPI _##CallBackFuncName##_eVision(PVOID context,EGenericROI* pROI,BOOL last)\
{\
	((ClassName*)context)->CallBackFuncName((ReturnType)pROI,last);\
}\
static void WINAPI _##CallBackFuncName##_Surface(PVOID context,ECHANDLE hSurface,BOOL last)\
{\
	((ClassName*)context)->CallBackFuncName((ReturnType)hSurface,last);\
}\

#define REGISTER_PICOLO_MULTICAMCHANNEL_CALLBACK(Server,Client,CallBackFuncName)\
	INT32 type = Server.GetCallBackType();\
	Server.CreationSuite();\
	MultiCamSignalMask (EC_SIGNAL_SURFACE_AVAILABLE,1);\
	if(type == 1){\
		Server.RegisterCB_eVision (this, _##CallBackFuncName##_eVision);\
	}else if(type == 2){\
		Server.RegisterCB_Surface (this, _##CallBackFuncName##_Surface);\
	}
#define REGISTER_PICOLO_CHANNEL()\
	PICOLO_CHANNELLIST	CPicoloMultiCamChannel::m_ChannelList;		

enum PicoloCallBackTypes{
	PicoloCallBackType_undefined = 0,
	PicoloCallBackType_eVision,
	PicoloCallBackType_User
};
enum CreationTypes{
	CreationType_undefined = 0,
	CreationType_eVision_MemByChannel,
	CreationType_eVision_MemByUser,
	CreationType_User
};
enum ErrorMode{
	ERROR_MODE_NONE =0,
	ERROR_MODE_DISPLAY_MSGBOX
};
/*---------------------------------------------------------------------*\
|	CMultiChannel definition											|
\*---------------------------------------------------------------------*/
static DWORD	s_PicoloInstanceNumber=0;

using namespace std ;
class CPicoloMultiCamChannel;
typedef list<CPicoloMultiCamChannel*> PICOLO_CHANNELLIST;

class CPicoloMultiCamChannel  
{
protected:
	ECHANDLE		m_hChannel;
	void**			m_ppImageBuffer;
	ECHANDLE*		m_phSurface;	
	EGenericROI**	m_ppROIList;
	DWORD			m_SurfaceNumber;

	INT32			m_ImageSizeX, m_ImageSizeY, m_ImageSize ;
	INT32			m_SurfaceSizeX, m_SurfaceSizeY, m_SurfaceSize ;
	INT32			m_PixelSize;	
	
	DWORD			m_CallBackType;
	DWORD			m_CreationType;
	BOOL			m_bMemoryAllocatedByUser;
	void*			m_pClientClass;
	BOOL			m_ErrorMode;

public:
	static PICOLO_CHANNELLIST		m_ChannelList;

protected:
//internal function
	HRESULT			InitializeDriver();
	HRESULT			MultiCamTerminate();
	HRESULT			PreCreate_Board(int Board=0, int Source=0);
	HRESULT			CreateSurfaces(DWORD SurfaceNumber);
	HRESULT			CreateSurfacesFromROIList(DWORD SurfaceNumber,EGenericROI** ROIList);
	HRESULT			AddSurfaces(DWORD SurfaceNumber,ECHANDLE* phSurface=NULL);
	HRESULT			ComputeImageSize();	
	void			SurfaceAvailableCallBack(PECEVENTINFO pInfo);
	PCBFUNC_EVISION	m_pCallBack_eVision;
	PCBFUNC_SURFACE	m_pCallBack_Surface;
	void			DisplayError(const char *Msg, int Code=0);
	
public:
//Construction
	CPicoloMultiCamChannel();
	virtual ~CPicoloMultiCamChannel();
//Implementation
	operator		ECHANDLE(){return m_hChannel;}
	ECHANDLE		GetChannelHdl(){return m_hChannel;}

	void			RegisterCB_eVision(void* This, PCBFUNC_EVISION pCallBack_eVision){
						m_pClientClass = This;
						m_pCallBack_eVision = pCallBack_eVision;
						return;
					}
	void			RegisterCB_Surface(void* This, PCBFUNC_SURFACE pCallBack_Surface){
						m_pCallBack_Surface = pCallBack_Surface;
						m_pClientClass = This;
						return;
					}
	HRESULT			Create(unsigned long SurfaceNumber=3,int Board=0, int Source=0);
	HRESULT			Create(EGenericROI** ROIList,unsigned long SurfaceNumber,INT32 Board=0, int Source=0);
	HRESULT			Create(ECHANDLE* phSurface,  unsigned long SurfaceNumber,INT32 Board=0, int Source=0);

	HRESULT			CreationSuite();

	HRESULT			Grab(DWORD GrabCount=1);
	HRESULT			Live();
	HRESULT			Stop();

	EGenericROI*	GetImage(unsigned long Index){
						return m_ppROIList[Index%m_SurfaceNumber];
					}
	SIZE			ImageSize()		{SIZE sz ={m_ImageSizeX, m_ImageSizeY};return sz;}
	SIZE			SurfaceSize()		{SIZE sz ={m_ImageSizeX, m_ImageSizeY};return sz;}

	HRESULT			SetParam(ECPARAMID ParamID, INT32 ValueInt){
						return	MultiCamChannelSetParameterInt (m_hChannel, ParamID, ValueInt );
					}
	HRESULT			SetParam(ECPARAMID ParamID, FLOAT32 ValueFloat){
						return	MultiCamChannelSetParameterFloat (m_hChannel, ParamID, ValueFloat );
					}
	HRESULT			SetParam( ECPARAMID ParamID, PCCHAR ValueStr){
						return MultiCamChannelSetParameterString (m_hChannel, ParamID, ValueStr );
					}	
	HRESULT			GetParam(ECPARAMID ParamID, INT32* pValueInt){
						return	MultiCamChannelGetParameterInt (m_hChannel, ParamID, pValueInt );
					}	
	HRESULT			GetParam(ECPARAMID ParamID, FLOAT32* pValueFloat){
						return MultiCamChannelGetParameterFloat (m_hChannel, ParamID, pValueFloat );
					}
	HRESULT			GetParam(ECPARAMID ParamID, PCHAR pValueStr, UINT32 MaxLength){
						return MultiCamChannelGetParameterString (m_hChannel, ParamID, pValueStr, MaxLength );
					}
	HRESULT			SetErrorMode(DWORD ErrorMode){
						m_ErrorMode = ErrorMode; return S_OK;
					}
	int				GetCallBackType(){return m_CallBackType;}	
	static void	__stdcall StaticSurfaceAvailableCallBack(PVOID context,PECEVENTINFO pInfo);
};

/*---------------------------------------------------------------------*\
|	CMultiChannel implementation										|
|	Constructor/destructor												|
\*---------------------------------------------------------------------*/
inline CPicoloMultiCamChannel::CPicoloMultiCamChannel(){
	m_pClientClass = NULL;
	m_phSurface = NULL;
	m_ppImageBuffer = NULL;
	m_hChannel = NULL;
	m_ppROIList = NULL;
	m_ImageSizeX = m_ImageSizeY =0;
	m_PixelSize = 0;
	m_SurfaceNumber = 3;
	m_CallBackType = 0;
	m_CreationType = 0;
	m_bMemoryAllocatedByUser = FALSE;
	m_pCallBack_eVision=NULL;
	m_pCallBack_Surface=NULL;
	m_ErrorMode =ERROR_MODE_DISPLAY_MSGBOX;
	if(s_PicoloInstanceNumber++==0)
		InitializeDriver();
}
inline CPicoloMultiCamChannel::~CPicoloMultiCamChannel(){
	ECSTATUS status = MultiCamChannelSetParameterInt (m_hChannel, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE); 
	if (status != EC_OK) 
	{
		DisplayError("Error: Cannot put channel in IDLE state.", status);
		return;
	}
	if(m_phSurface)
		delete m_phSurface;
	if(m_bMemoryAllocatedByUser ==FALSE){
		if(m_ppImageBuffer!=NULL){
			for( DWORD i = 0; i<m_SurfaceNumber;i++){
				if (m_ppImageBuffer[i]!=NULL)
					VirtualFree(m_ppImageBuffer[i], 0, MEM_RELEASE);
			}
			delete m_ppImageBuffer;
		}
		if(m_ppROIList!=NULL){
			for( DWORD i = 0; i<m_SurfaceNumber;i++){
				if(m_ppROIList[i] !=NULL){
					((EImageBW8*)m_ppROIList[i])->SetImagePtr(NULL);
					delete ((EImageBW8*)m_ppROIList[i]);
				}
			}
			delete m_ppROIList;
		}
	}
	if(--s_PicoloInstanceNumber==0)
		MultiCamTerminate();
}

inline void __stdcall CPicoloMultiCamChannel::StaticSurfaceAvailableCallBack ( PVOID context, PECEVENTINFO pInfo) 
{
	PICOLO_CHANNELLIST::iterator iter;
	for(iter = m_ChannelList.begin();iter != m_ChannelList.end();++iter){
		if((*iter)->GetChannelHdl()==pInfo->ChannelID){ 
			(*iter)->SurfaceAvailableCallBack( pInfo );
			return;
		}
	}
	return;
}
inline void CPicoloMultiCamChannel::SurfaceAvailableCallBack(PECEVENTINFO pInfo){
	for(int i = 0;i< m_SurfaceNumber; i++){
		if (pInfo->SurfaceID==m_phSurface[i]){			
			if (m_pCallBack_eVision){
				m_pCallBack_eVision(m_pClientClass,m_ppROIList[i],TRUE);
			}
			if (m_pCallBack_Surface){
				m_pCallBack_Surface(m_pClientClass,pInfo->SurfaceID,FALSE);
			}
			return;
		}
	}
}
/*---------------------------------------------------------------------*\
|	functions depending on the static (i.e. unique for all instances of	|
|	the class) variable counter s_InstanceNumber. for earch instance	|
|	creation/destruction, the counter changes (++/--).		 			|
|	s_InstanceNumber:  0--->1 => InitializeDriver()						|
|	s_InstanceNumber:  1--->0 => MultiCamTerminate()					|
\*---------------------------------------------------------------------*/

inline HRESULT	CPicoloMultiCamChannel::InitializeDriver(){
	ECSTATUS Status ;
	m_ChannelList.clear();
	// Establish communication with the driver
	Status = MultiCamSystemInitialize();
	if (Status != EC_OK){
		DisplayError("Error: Picolo OpenDriver failed.", Status);
		return E_FAIL ;
	}
	// Enable image acquisitions
	Status = MultiCamSystemAcquisitionStart ();
	if (Status != EC_OK)
	{
		AfxMessageBox("Cannot enable acquisition", MB_OK | MB_APPLMODAL | MB_ICONSTOP);
		return FALSE;
	}

	return S_OK;	
}

inline HRESULT	CPicoloMultiCamChannel::MultiCamTerminate(){
	ECSTATUS Status ;
	// Disable image acquisitions
	Status = MultiCamSystemAcquisitionStop ();
	if (Status != EC_OK){ 
		DisplayError("Error: McStartAcq failed.", Status);
		return E_FAIL ;
	}
	Sleep(200);	
	// Terminate communication with the driver
	Status = MultiCamSystemTerminate();
	if ( Status != EC_OK ){
		DisplayError("Error: CloseDriver failed.", Status);
		return E_FAIL ;
	}
	return S_OK ;	
}
/*---------------------------------------------------------------------*\
|	Channel creation functions											|
|		Create call CreateSurfacesFromROIList							|
|					CreateSurfaces										|
|					AddSurfacesToCluster								|
\*---------------------------------------------------------------------*/
inline HRESULT	CPicoloMultiCamChannel::PreCreate_Board(int Board, int Source){
	ECSTATUS Status;
	//========================================================================
	// Channel(s) creation									--->>>
	//
	char BoardIdentificator[3];
	sprintf(BoardIdentificator,"#%u",Board);
	m_hChannel = MultiCamChannelCreate (NULL, BoardIdentificator, Source);
	if (m_hChannel <= 0)
	{
		DisplayError("Cannot Create Channel to board");
		return E_FAIL;
	}
	Status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_TriggerMask, TRIGGERMASK_BYPASS);
	Status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_AssemblerMask, ASMMASK__DELAY);
	Status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_Standard, EC_STANDARD_PAL);
	Status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_FieldMode, 2);
	Status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_AcqColFmt, EC_COLORFORMAT_RGB24);
	MultiCamSignalRegister (EC_SIGNAL_SURFACE_AVAILABLE, StaticSurfaceAvailableCallBack, this);
	//
	// Channel(s) creation									<<<---	
	//========================================================================
	return S_OK;
}
inline HRESULT	CPicoloMultiCamChannel::Create(unsigned long SurfaceNumber,int Board,int Source){
	m_CallBackType=	PicoloCallBackType_eVision;
	m_SurfaceNumber=SurfaceNumber;
	if(PreCreate_Board(Board, Source)!=S_OK)
		return E_FAIL;
	m_CreationType=CreationType_eVision_MemByChannel;
	return S_OK;
}

inline HRESULT	CPicoloMultiCamChannel::Create(EGenericROI** ROIList,
										 unsigned long SurfaceNumber,
										 INT32 Board,
										 int Source){
	m_CallBackType=PicoloCallBackType_eVision;
	m_SurfaceNumber=SurfaceNumber;
	m_ppROIList = ROIList;
	m_bMemoryAllocatedByUser = TRUE;
	if(PreCreate_Board(Board, Source)!=S_OK)
		return E_FAIL;
	m_CreationType=CreationType_eVision_MemByUser;
	return S_OK;
}

inline HRESULT	CPicoloMultiCamChannel::Create(ECHANDLE* phSurface,
										 unsigned long SurfaceNumber,
										 INT32 Board,
										 int Source){
	m_CallBackType=PicoloCallBackType_User;
	m_SurfaceNumber=SurfaceNumber;
	m_bMemoryAllocatedByUser = TRUE;
	m_phSurface;
	if(PreCreate_Board(Board, Source)!=S_OK)
		return E_FAIL;
	m_CreationType=CreationType_User;
	return S_OK;
}
inline HRESULT	CPicoloMultiCamChannel::CreationSuite(){
	switch(m_CreationType){
	case CreationType_eVision_MemByChannel:
		if(CreateSurfaces(m_SurfaceNumber)!=S_OK)
			return E_FAIL;
		if(CreateSurfacesFromROIList(m_SurfaceNumber, m_ppROIList)!=S_OK)
			return E_FAIL;
		if(AddSurfaces(m_SurfaceNumber)!=S_OK)
			return E_FAIL;
		break;
	case CreationType_eVision_MemByUser:
		if(CreateSurfacesFromROIList(m_SurfaceNumber, m_ppROIList)!=S_OK)
			return E_FAIL;
		if(AddSurfaces(m_SurfaceNumber)!=S_OK)
			return E_FAIL;
		break;
	case CreationType_User:
		if(AddSurfaces(m_SurfaceNumber, m_phSurface)!=S_OK)
			return E_FAIL;
		break;
	}
	return S_OK;
}
inline HRESULT	CPicoloMultiCamChannel::CreateSurfaces(DWORD SurfaceNumber){	
	if(m_ppImageBuffer==NULL)
		m_ppImageBuffer = new PVOID[SurfaceNumber];
	m_ppROIList = new EGenericROI*[SurfaceNumber];
	ComputeImageSize();
	for (DWORD i=0; i<SurfaceNumber ;i++){
		m_ppImageBuffer[i] = VirtualAlloc(NULL, m_ImageSize, MEM_COMMIT, PAGE_READWRITE);
		if (m_ppImageBuffer [i] == NULL) {
			DisplayError("Cannot allocate image buffer", 0);
			return E_FAIL;
		}		
		// Set the EImage... object to the appropriate size 
		switch (m_PixelSize){
			case 1:// 8-bit monochrome
				m_ppROIList[i] = new EImageBW8(m_ImageSizeX,m_ImageSizeY);
				((EImageBW8*)m_ppROIList[i])->SetImagePtr(m_ppImageBuffer[i]);
				break;
			case 2:// 16-bit monochrome
				m_ppROIList[i] = new EImageBW16(m_ImageSizeX,m_ImageSizeY);
				((EImageBW16*)m_ppROIList[i])->SetImagePtr(m_ppImageBuffer[i]);
				break;
			case 3:	// 24 bits RGB color
				m_ppROIList[i] = new EImageC24(m_ImageSizeX,m_ImageSizeY);
				((EImageC24*)m_ppROIList[i])->SetImagePtr(m_ppImageBuffer[i]);
				break;
			default:
				DisplayError("Unsupported image format", 0);
				return E_FAIL;
		}
	}
	return S_OK;
}
inline HRESULT	CPicoloMultiCamChannel::CreateSurfacesFromROIList(DWORD SurfaceNumber, EGenericROI** ROIList){
	ComputeImageSize();
	if(m_phSurface==NULL)
		m_phSurface = new ECHANDLE[SurfaceNumber];
	if(m_ppImageBuffer==NULL){
		m_ppImageBuffer = new PVOID[SurfaceNumber];
		for (DWORD i=0; i<SurfaceNumber ;i++){
			switch (m_PixelSize){
				case 1:// 8-bit monochrome
					m_ppImageBuffer[i]=((EImageBW8*)ROIList[i])->GetImagePtr();
					break;
				case 2:// 16-bit monochrome
					m_ppImageBuffer[i]=((EImageBW16*)ROIList[i])->GetImagePtr();
					break;
				case 3:	// 24 bits RGB color
					m_ppImageBuffer[i]=((EImageC24*)ROIList[i])->GetImagePtr();
					break;
				default:
					DisplayError("Unsupported image format", 0);
					return E_FAIL;
			}			
		}
	}
	ECSURFACEINFO SurfInfo ;
	SurfInfo.StructSize = sizeof (ECSURFACEINFO) ;
	SurfInfo.Type = EC_SURFACE_TYPE_PC ;
	SurfInfo.Address = NULL ;
	SurfInfo.UserAllocatedMemory = 0 ;
	SurfInfo.Pitch = m_ImageSizeX*m_PixelSize;
	SurfInfo.Size= m_ImageSize;
	for (DWORD i=0; i<SurfaceNumber ;i++){
		// Create a surface
		SurfInfo.Address=m_ppImageBuffer[i];
		m_phSurface[i] = MultiCamSurfaceCreate(&SurfInfo);
		if (m_phSurface[i] < 0) 
		{
			DisplayError("Cannot Create Surface");
			return E_FAIL;
		}
		memset(SurfInfo.Address, 0, SurfInfo.Size);
	}

	return S_OK;
}
inline HRESULT	CPicoloMultiCamChannel::AddSurfaces(DWORD SurfaceNumber, ECHANDLE* phSurface){
	ECSTATUS Status;
	if((phSurface == NULL)&(m_phSurface!=NULL)){
		phSurface = m_phSurface;
		for (DWORD i=0; i<SurfaceNumber ;i++){
			Status = MultiCamChannelAddSurface (m_hChannel, phSurface[i]);
			if (Status != EC_OK)
			{
				AfxMessageBox("Cannot add surface into channel", MB_OK | MB_APPLMODAL | MB_ICONSTOP);
				return FALSE;
			}
		}
		m_ChannelList.insert(m_ChannelList.end(),this);
		return S_OK;
	}
	return E_FAIL;
}
inline HRESULT CPicoloMultiCamChannel::ComputeImageSize(){
	// Retrieve image parameters
	ECSTATUS status = MultiCamChannelGetParameterInt ( m_hChannel, EC_PARAM_ImageSizeX, &m_ImageSizeX);
	if (status != EC_OK) 
	{
		DisplayError("Error: MultiCamChannelGetParameterInt EC_PARAM_ImageSizeX failed.", status);
		return E_FAIL;
	}
	status = MultiCamChannelGetParameterInt ( m_hChannel, EC_PARAM_ImageSizeY, &m_ImageSizeY);
	if (status != EC_OK) 
	{
		DisplayError("Error: MultiCamChannelGetParameterInt EC_PARAM_ImageSizeY failed.", status);
		return E_FAIL;
	}
	// Check the pixel-size
	int colorformat;
	status = MultiCamChannelGetParameterInt ( m_hChannel, EC_PARAM_AcqColFmt, &colorformat);
	if (status != EC_OK) 
	{
		DisplayError("Error: MultiCamChannelGetParameterInt EC_PARAM_AcqColFmt failed.", status);
		return E_FAIL;
	}else{
		switch (colorformat){
		case EC_COLORFORMAT_RGB32 :
			m_PixelSize = 4;
			break;
		case EC_COLORFORMAT_RGB24 :
			m_PixelSize = 3;
			break;
		case EC_COLORFORMAT_RGB16 :
			m_PixelSize = 2;
			break;
		case EC_COLORFORMAT_RGB15 :
			m_PixelSize = 2;
			break;
		case EC_COLORFORMAT_Y8:
			m_PixelSize = 1;
			break;
		}
	}
	m_ImageSize = m_ImageSizeY * m_ImageSizeX * m_PixelSize;

	return S_OK;
}

inline HRESULT	CPicoloMultiCamChannel::Grab(DWORD GrabCount){
	ECSTATUS status ;
	// Set Channel to Idle state
	status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);
	status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_RepeatGrabCount, 0 );
	status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_ChannelState, CHANNEL_STATE_ACTIVE);
	return S_OK ;
}

inline HRESULT	CPicoloMultiCamChannel::Live(){
	ECSTATUS status ;
	// Set Channel to Idle state
	status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_RepeatGrabCount, -1 );
	status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_ChannelState, CHANNEL_STATE_ACTIVE);
	return S_OK ;
}
inline HRESULT	CPicoloMultiCamChannel::Stop(){
	ECSTATUS status ;
	// Set Channel to Idle state
	status = MultiCamChannelSetParameterInt ( m_hChannel, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);
	return S_OK ;
}

inline void CPicoloMultiCamChannel::DisplayError(const char *Msg, int Code){
	if(m_ErrorMode==ERROR_MODE_DISPLAY_MSGBOX){
		char Txt[100];
		sprintf(Txt,"%s\n Return value = %d", Msg, Code);
		MessageBox( NULL,Txt,NULL,MB_OK);
	}
}
#endif // !defined(_PICOLO_MULTICHANNEL_H____INCLUDED_)
