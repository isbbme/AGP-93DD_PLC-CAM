
// MFC20191205Dlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include <windows.h>
#include "MFC20191205.h"
#include "MFC20191205Dlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
#include "iostream" 
#include "conio.h"
#include <tchar.h>
#include <windef.h>

#include "EthernetPort.h"
#include "CKeyencePlcAccess.h"

#include <sstream>
#include <mutex>
#include <fstream>
#include <string> 
#include <atlstr.h>
#include "windows.h"
#include "resource.h"
#include <time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui_c.h>

#include "GenICam\System.h"
#include "GenICam\Camera.h"
#include "GenICam\GigE\GigECamera.h"
#include "GenICam\GigE\GigEInterface.h"
#include "Infra\PrintLog.h"
#include "Memory\SharedPtr.h"
#include "StreamRetrieve.h"

#pragma comment(lib, "Ws2_32.lib")
#define WIN32_LEAN_AND_MEAN
#define DEFAULT_BUFLEN 32
#define DEFAULT_PORT 8501
#define DEFAULT_X 51790
#define DEFAULT_Y 42580
#define DEFAULT_Z 15792
#define DEFAULT_PZ 26420

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//WSADATA wsaData;
//SOCKET *SocketNumber;
//HWND hWnd;
//struct sockaddr_in clientService;

WSADATA wsaData;
SOCKET SocketNumber = INVALID_SOCKET;
HWND hWnd;
struct sockaddr_in clientService;
int recvbuflen = DEFAULT_BUFLEN;

using namespace std; using namespace cv;
using namespace Dahua::GenICam;
using namespace Dahua::Infra;

//char szValue[8];
//char szCommand[32];
//char szReturn[32];
//char szRegNum[8];

DWORD valuex;
DWORD valuey;
DWORD valuez;
DWORD valuepltz;
////////////////////////////////////////////////////////////////////////////////////
//Global Declarations and init for cam
bool bRet = FALSE;
ICameraPtr cameraSptr;
CSystem& systemObj = CSystem::getInstance();
TVector<ICameraPtr> vCameraPtrList;

/////////////////////////////////////////////////////////////////////////////////////////////////////

//set timeout


//int mr = 000;     //3int   ~000
//int dm = 000;     //3int   x=000 y=002 z=004
//DWORD dmvalue = 00000; //5int   ~17000
//int namer;
// 對 App About 使用 CAboutDlg 對話方塊

CKeyencePlcAccess *PlcAccess;   //
//EthernetPort* m_pEtherPort;

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////
/////////KeyencePlcAccess
CKeyencePlcAccess::CKeyencePlcAccess(void)    //初始化定義
{
	m_pEtherPort = NULL;
	AfxMessageBox(L"yes", MB_YESNO | MB_ICONWARNING);
}

CKeyencePlcAccess::~CKeyencePlcAccess(void)
{
	AfxMessageBox(L"No", MB_YESNO | MB_ICONWARNING);
	if (m_pEtherPort)
		delete m_pEtherPort;
}

BOOL CKeyencePlcAccess::OpenDevice(int port_num)
{
	int Result; 
	if (m_pEtherPort == NULL)
		m_pEtherPort = new EthernetPort;
	Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != NO_ERROR)
	{
		AfxMessageBox(L"WSAStartup failed with error:", MB_YESNO | MB_ICONWARNING);
		return FALSE;
	}

	SocketNumber = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SocketNumber == INVALID_SOCKET) 
	{
		AfxMessageBox(L"socket failed with error: ", MB_YESNO | MB_ICONWARNING);
		WSACleanup();
		return FALSE;
	}
	AfxMessageBox(L"socket works!!", MB_YESNO | MB_ICONINFORMATION);
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("192.168.0.10"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port_num);

	Result = connect(SocketNumber, (SOCKADDR*)&clientService, sizeof(clientService));
	if (Result == SOCKET_ERROR)
	{
		AfxMessageBox(L"connect failed with error: ", MB_YESNO | MB_ICONWARNING);
		closesocket(SocketNumber);
		WSACleanup();
		return FALSE;
	}
	AfxMessageBox(L"Connected!!", MB_YESNO | MB_ICONINFORMATION);

	/*return StartComm();*/
	return TRUE;
}

//BOOL CKeyencePlcAccess::StartComm()
//{
//	return TRUE;
//}

BOOL WriteRegister_MR_BITTEST1(int regNum, int regNum2, int regNum3)
{

	int Result;
	Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != NO_ERROR)
	{
		AfxMessageBox(L"WSAStartup failed with error:", MB_YESNO | MB_ICONWARNING);
		return FALSE;
	}
	SocketNumber = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SocketNumber == INVALID_SOCKET)
	{
		AfxMessageBox(L"socket failed with error: ", MB_YESNO | MB_ICONWARNING);
		WSACleanup();
		return FALSE;
	}
	AfxMessageBox(L"socket works!!", MB_YESNO | MB_ICONINFORMATION);
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("192.168.0.10"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(8501);

	Result = connect(SocketNumber, (SOCKADDR*)&clientService, sizeof(clientService));
	if (Result == SOCKET_ERROR)
	{
		AfxMessageBox(L"connect failed with error: ", MB_YESNO | MB_ICONWARNING);
		closesocket(SocketNumber);
		WSACleanup();
		return FALSE;
	}
	AfxMessageBox(L"Connected!!", MB_YESNO | MB_ICONINFORMATION);


	char szCommand[32] = "";
	char* cp = szCommand;
	char szReturn[32] = "";
	char* cpr = szReturn;
	char szRegNum[8] = "";
	BYTE value = 1;

	wsprintfA(szRegNum, "%03d", regNum);

	szCommand[0] = 'W';
	szCommand[1] = 'R';
	szCommand[2] = ' ';
	szCommand[3] = 'M';
	szCommand[4] = 'R';
	szCommand[5] = szRegNum[0];
	szCommand[6] = szRegNum[1];
	szCommand[7] = szRegNum[2];
	szCommand[8] = '.';
	szCommand[9] = 'D';
	szCommand[10] = ' ';
	szCommand[11] = '1';
	//szCommand[11] = (value == 1) ? '1' : '0';
	szCommand[12] = 0x0d;
	AfxMessageBox(L"1.準備開 ", MB_YESNO | MB_ICONWARNING);   
	Result = send(SocketNumber, cp, (int)strlen(cp), 0);
	AfxMessageBox(L"有傳東西", MB_YESNO | MB_ICONWARNING);   
	Result = recv(SocketNumber, cpr, recvbuflen, 0);


	wsprintfA(szRegNum, "%03d", regNum2);

	szCommand[0] = 'W';
	szCommand[1] = 'R';
	szCommand[2] = ' ';
	szCommand[3] = 'M';
	szCommand[4] = 'R';
	szCommand[5] = szRegNum[0];
	szCommand[6] = szRegNum[1];
	szCommand[7] = szRegNum[2];
	szCommand[8] = '.';
	szCommand[9] = 'D';
	szCommand[10] = ' ';
	szCommand[11] = '1';
	//szCommand[11] = (value == 1) ? '1' : '0';
	szCommand[12] = 0x0d;
	AfxMessageBox(L"1.準備動 ", MB_YESNO | MB_ICONWARNING);   
	Result = send(SocketNumber, cp, (int)strlen(cp), 0);
	Result = recv(SocketNumber, cpr, recvbuflen, 0);

	wsprintfA(szRegNum, "%03d", regNum3);

	szCommand[0] = 'W';
	szCommand[1] = 'R';
	szCommand[2] = ' ';
	szCommand[3] = 'M';
	szCommand[4] = 'R';
	szCommand[5] = szRegNum[0];
	szCommand[6] = szRegNum[1];
	szCommand[7] = szRegNum[2];
	szCommand[8] = '.';
	szCommand[9] = 'D';
	szCommand[10] = ' ';
	szCommand[11] = '1';
	//szCommand[11] = (value == 1) ? '1' : '0';
	szCommand[12] = 0x0d;

	Result = send(SocketNumber, cp, (int)strlen(cp), 0);
	Result = recv(SocketNumber, cpr, recvbuflen, 0);
	AfxMessageBox(L"有傳東西", MB_YESNO | MB_ICONWARNING);   

	

	return TRUE;
	
}


BOOL CKeyencePlcAccess::WriteRegister_MR_BIT(int regNum, BYTE value)
{

	//char szCommand[32];
	//char szReturn[32];
	//char szRegNum[8];
	
	char szCommand[32];
	//char* cp = szCommand;
	char szReturn[32];
	//char* cpr = szReturn;
	char szRegNum[8];
	int length;
	wsprintfA(szRegNum, "%03d", regNum);

	szCommand[0] = 'W';
	szCommand[1] = 'R';
	szCommand[2] = ' ';
	szCommand[3] = 'M';
	szCommand[4] = 'R';
	szCommand[5] = szRegNum[0];
	szCommand[6] = szRegNum[1];
	szCommand[7] = szRegNum[2];
	szCommand[8] = '.';
	szCommand[9] = 'D';
	szCommand[10] = ' ';
	if (value == 1)
		szCommand[11] = '1';
	if (value == 0)
		szCommand[11] = '0';
	//szCommand[11] = (value == 1) ? '1' : '0';
	szCommand[12] = 0x0d;
	//TRACE("The value of szCommand[11] is %c \n", szCommand[11]);

	BOOL bSuccess = FALSE;
	////Try not to use for
	//
	//m_pEtherPort->WriteEthernetPort(szCommand, 13);
	//{
	//	//TRACE("The value of szCommand is %s \n", szCommand);

	//	if (m_pEtherPort->ReadEthernetPort(szReturn, &length) == TRUE)
	//	{
	//		//TRACE("The value of szReturn is %s \n", szReturn);
	//		bSuccess = TRUE;
	//	}
	//}
	for (int i = 0; i < 5; i++)  // try to read 3 times at max
	{
		m_pEtherPort->WriteEthernetPort(szCommand, 13);
		{
		
			if (m_pEtherPort->ReadEthernetPort(szReturn, &length) == TRUE)
			{
				bSuccess = TRUE;
				szReturn[2] = 0;
				break;
			}
		}
	
	}

	if (strcmp(szReturn, "OK") == 0)
	{
		//AfxMessageBox(L"Returning WR MR success", MB_YESNO | MB_ICONWARNING);
		return bSuccess;
	}
	
	AfxMessageBox(L"失敗", MB_YESNO | MB_ICONWARNING);
	return FALSE;
}

BOOL CKeyencePlcAccess::ReadRegister_MR_BIT(int regNum, BYTE* value)
{
	char szCommand[32], szReturn[32];
	char szRegNum[8];
	int length;
	//int Result;

	wsprintfA(szRegNum, "%03d", regNum);

	szCommand[0] = 'R';
	szCommand[1] = 'D';
	szCommand[2] = ' ';
	szCommand[3] = 'M';
	szCommand[4] = 'R';
	szCommand[5] = szRegNum[0];
	szCommand[6] = szRegNum[1];
	szCommand[7] = szRegNum[2];
	szCommand[8] = '.';
	szCommand[9] = 'D';
	szCommand[10] = 0x0d;

	BOOL bSuccess = FALSE;

	m_pEtherPort->WriteEthernetPort(szCommand, 11);
	{

		if (m_pEtherPort->ReadEthernetPort(szReturn, &length) == TRUE)
		{
			bSuccess = TRUE;
			//AfxMessageBox(L"ReadRegister_MR_BIT successed!!", MB_YESNO | MB_ICONINFORMATION);
		}
	}

	return bSuccess;
}
BOOL Lights_Toggle(DWORD v)
{
	char szCommand[32], szReturn[32];
	char szRegNum[8];
	szCommand[0] = 'W';
	szCommand[1] = 'R';
	szCommand[2] = ' ';
	szCommand[3] = 'M';
	szCommand[4] = 'R';
	szCommand[5] = '0';
	szCommand[6] = '0';
	szCommand[7] = '7';
	szCommand[8] = '.';
	szCommand[9] = 'D';
	szCommand[10] = ' ';
	if (v == 1)
		szCommand[11] = '1';
	if (v == 0)
		szCommand[11] = '0';
	szCommand[12] = 0x0d;
	int bResult = send(SocketNumber, szCommand, 13, 0);
	bResult = recv(SocketNumber, szReturn, recvbuflen, 0);
	if (bResult == SOCKET_ERROR)
	{
		return FALSE;
	}
	else
		return TRUE;

	return FALSE;
}

BOOL CKeyencePlcAccess::WriteRegister_DM_WORD(int regNum, DWORD value)
{
	char szCommand[32], szReturn[32];
	char szRegNum[8], szValue[8];
	int length;
	wsprintfA(szRegNum, "%03d", regNum);
	wsprintfA(szValue, "%06d", value);

	szCommand[0] = 'W';
	szCommand[1] = 'R';
	szCommand[2] = ' ';
	szCommand[3] = 'D';
	szCommand[4] = 'M';
	szCommand[5] = szRegNum[0];
	szCommand[6] = szRegNum[1];
	szCommand[7] = szRegNum[2];
	szCommand[8] = '.';
	szCommand[9] = 'D';
	szCommand[10] = ' ';
	szCommand[11] = szValue[0];
	szCommand[12] = szValue[1];
	szCommand[13] = szValue[2];
	szCommand[14] = szValue[3];
	szCommand[15] = szValue[4];
	szCommand[16] = szValue[5];
	szCommand[17] = 0x0d;

	BOOL bSuccess = FALSE;
	for (int i = 0; i < 5; i++)  // try to read 3 times at max
	{
	

		m_pEtherPort->WriteEthernetPort(szCommand, 18);
		{

			if (m_pEtherPort->ReadEthernetPort(szReturn, &length))
			{
				szReturn[2] = 0;
				bSuccess = TRUE;
				break;
			}
		}
	}

	
	if (strcmp(szReturn, "OK") == 0)
	{
		//AfxMessageBox(L"Write DM OK!!", MB_YESNO | MB_ICONINFORMATION);
		return TRUE;
	}


	return FALSE;
}

//BOOL CKeyencePlcAccess::ReadRegister_DM_WORD(int regNum, int* value)
////BOOL CKeyencePlcAccess::ReadRegister_DM_WORD(int regNum, WORD* value)
//{
//	char szCommand[32], szReturn[32], tmpcommand[5]="";
//	char szRegNum[8];
//
//
//	wsprintfA(szRegNum, "%03d", regNum);
//
//	szCommand[0] = 'R';
//	szCommand[1] = 'D';
//	szCommand[2] = ' ';
//	szCommand[3] = 'D';
//	szCommand[4] = 'M';
//	szCommand[5] = szRegNum[0];
//	szCommand[6] = szRegNum[1];
//	szCommand[7] = szRegNum[2];
//	szCommand[8] = '.';
//	szCommand[9] = 'D';
//
//	szCommand[10] = 0x0d;
//
//	BOOL bSuccess = FALSE;
//	
//	m_pEtherPort->WriteEthernetPort(szCommand, 11);
//
//	if (m_pEtherPort->ReadEthernetPort(szReturn) == TRUE)
//	{
//		bSuccess = TRUE;
//		for (int j = 0; j < 5; j++)
//		{
//			tmpcommand[j] = szReturn[j];
//		}
//		
//		return TRUE;
//	
//	}
//	
//	*value = atoi(tmpcommand);
//	//if (bSuccess && strlen(szReturn) == 7)
//	//{
//	//	szReturn[5] = 0;
//	//	*value = atoi(szReturn);
//	//	return TRUE;
//	//}
//
//	return bSuccess;
//}

//BOOL CKeyencePlcAccess::ReadRegister_DM_WORD(int regNum, WORD* value)
int CKeyencePlcAccess::ReadRegister_DM_WORD(int regNum)
{
	char szCommand[32], szReturn[32], tmpcommand[32] = "";
	char szRegNum[8];
	int val;
	int length;
	//int Result;

	wsprintfA(szRegNum, "%03d", regNum);

	szCommand[0] = 'R';
	szCommand[1] = 'D';
	szCommand[2] = ' ';
	szCommand[3] = 'D';
	szCommand[4] = 'M';
	szCommand[5] = szRegNum[0];
	szCommand[6] = szRegNum[1];
	szCommand[7] = szRegNum[2];
	szCommand[8] = '.';
	szCommand[9] = 'D';
	szCommand[10] = 0x0d;

	m_pEtherPort->WriteEthernetPort(szCommand, 11);
	{

		if (m_pEtherPort->ReadEthernetPort(szReturn, &length) == TRUE)
		{
			for (int j = 0; j < 10; j++)
			{
				tmpcommand[j] = szReturn[j];
			}

		}
	}

	val = atoi(tmpcommand);
	return 	val;
}

void CKeyencePlcAccess::CloseDevice()
{
	m_pEtherPort->CloseEthernetPort();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

//bool SendAll(SOCKET sock, char* buffer, int size)
//{
//	while (size > 0)
//	{
//		int SendSize = send(sock, buffer, size, 0);
//		if (SOCKET_ERROR == SendSize)
//			return FALSE;
//		size = size - SendSize;//用於迴圈傳送且退出功能
//		buffer += SendSize;//用於計算已發buffer的偏移量
//		TRACE("The value of send size is %d \n", SendSize);
//	}
//	return TRUE;
//}
//bool RecvAll(SOCKET sock, char* buffer, int size)
//{
//	while (size > 0)//剩餘部分大於0
//	{
//		int RecvSize = recv(sock, buffer, size, 0);
//		if (SOCKET_ERROR == RecvSize)
//			return FALSE;
//		size = size - RecvSize;
//		buffer += RecvSize;
//	}
//	return TRUE;
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class definition and loading for EthernetPort
EthernetPort::EthernetPort(void)
{
	SocketNumber = NULL;
	//m_hMutex = CreateMutex(NULL, FALSE, NULL);
	AfxMessageBox(L"yes2", MB_YESNO | MB_ICONWARNING);
}

EthernetPort::~EthernetPort(void)
{
	AfxMessageBox(L"No2", MB_YESNO | MB_ICONWARNING);
	//CloseHandle(m_hMutex);
	CloseEthernetPort();
	//CloseHandle(m_hMutex);
}
void EthernetPort::CloseEthernetPort()
{
	if (SocketNumber)
	{
		closesocket(SocketNumber);
	}
}
BOOL EthernetPort::WriteEthernetPort( char* szString, int nLengthToWrite)
{
	if (SocketNumber == NULL)
		return FALSE;
	BOOL bsuccess;
	//WaitForSingleObject(m_hMutex, INFINITE);
	
	bsuccess = WriteEthernetPort_non_overlapped(szString, nLengthToWrite);
	
	//ReleaseMutex(m_hMutex);

	return bsuccess;
}
BOOL EthernetPort::WriteEthernetPort_non_overlapped(char* szString, int nLengthToWrite)
{
	const char* yalamuta;
	yalamuta = szString;
	
	//bool bResult = SendAll(SocketNumber, yalamuta, nLengthToWrite);

	
	int bResult = send(SocketNumber, yalamuta, nLengthToWrite, 0);
	//TRACE("The value of send yalamuta is %s \n", yalamuta);
	//TRACE("The value of send BYTES is %d \n", bResult);

	if (bResult == SOCKET_ERROR)
	{
		return FALSE;
	}
	 
	return TRUE;	

}
BOOL EthernetPort::ReadEthernetPort(char* szString, int* nLengthRead)
{
	if (SocketNumber == NULL)
		return FALSE;
	BOOL bsuccess;
	
	bsuccess = ReadEthernetPort_non_overlapped(szString, nLengthRead);
	//ReleaseMutex(m_hMutex);
	return bsuccess;
}
BOOL EthernetPort::ReadEthernetPort_non_overlapped(char* szString,int* nLengthRead)
{
	char* sulamayo;
	sulamayo = szString;
	
	
	//bool bResult = RecvAll(SocketNumber, sulamayo, (int)strlen(sulamayo));

	int bResult = recv(SocketNumber, sulamayo, (int)strlen(sulamayo), 0);
	

	//TRACE("The value of recv sulamayo is %s \n", sulamayo);
	//TRACE("The value of len is %d \n", len);

	*nLengthRead = (int)strlen(sulamayo);
	
	if (bResult == SOCKET_ERROR)
	{
		AfxMessageBox(L"SOCKET_ERROR FALSE!!", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
	}
	if (bResult == 0)
	{
		AfxMessageBox(L"disconnect FALSE!!", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
	}
	//AfxMessageBox(L"ReadEthernetPort successed!!", MB_YESNO | MB_ICONINFORMATION);
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////
//Class declarations for cam
static void modifyCameragainRaw(ICameraPtr& cameraSptr, int64_t asdf)
{


	CDoubleNode nodegainRaw(cameraSptr, "GainRaw");
	if (!nodegainRaw.isValid())
	{
		AfxMessageBox(L" get gainRaw node fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}
	double dbValue = 0.0;
	if (false == nodegainRaw.getValue(dbValue))
	{
		AfxMessageBox(L" get gainRaw fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}
	 
	if (false == nodegainRaw.setValue(dbValue + 0.5))
		//if (false == nodeExposureTime.setValue(dbValue/2))
	{
		AfxMessageBox(L" set nodegainRaw fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}

	if (false == nodegainRaw.getValue(dbValue))
	{
		AfxMessageBox(L" get nodegainRaw fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}
}

static void modifybrightness(ICameraPtr& cameraSptr)
{

	CIntNode nodebrightness(cameraSptr, "Brightness");
	if (false == nodebrightness.isValid())
	{
		AfxMessageBox(L" get nodebrightness node fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}
	int64_t intValue = 0;
	if (false == nodebrightness.getValue(intValue))
	{
		AfxMessageBox(L" get nodebrightness fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}
	 
	if (false == nodebrightness.setValue(intValue + 10))
		//if (false == nodeExposureTime.setValue(dbValue/2))
	{
		AfxMessageBox(L" set nodebrightness fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}

	if (false == nodebrightness.getValue(intValue))
	{
		AfxMessageBox(L" get nodebrightness fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}
}

static void modifyCameraExposureTime(ICameraPtr& cameraSptr)
{
	Dahua::GenICam::CDoubleNode nodeExposureTime(cameraSptr, "ExposureTime");
	if (!nodeExposureTime.isValid())
	{
		AfxMessageBox(L" get ExposureTime node fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}

	double dbValue = 0.0;
	if (false == nodeExposureTime.getValue(dbValue))
	{
		AfxMessageBox(L" get ExposureTime fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}


	if (false == nodeExposureTime.setValue(dbValue))
		//if (false == nodeExposureTime.setValue(dbValue/2))
	{
		AfxMessageBox(L" set ExposureTime fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}

	if (false == nodeExposureTime.getValue(dbValue))
	{
		AfxMessageBox(L" get ExposureTime fail.", MB_YESNO | MB_ICONINFORMATION);
		return;
	}
}

static bool setSoftTriggerConf(IAcquisitionControlPtr sptrAcquisitionCtl)
{
	//扢离揖楷埭峈揖楷
	CEnumNode enumNode = sptrAcquisitionCtl->triggerSource();
	bool bRet = enumNode.setValueBySymbol("Software");
	if (bRet != true)
	{
		printf("set trigger source fail.\n");
		return false;
	}

	//扢离揖楷
	enumNode = sptrAcquisitionCtl->triggerSelector();
	bRet = enumNode.setValueBySymbol("FrameStart");
	if (bRet != true)
	{
		printf("set trigger selector fail.\n");
		return false;
	}

	//扢离揖楷耀宒
	enumNode = sptrAcquisitionCtl->triggerMode();
	//bRet = enumNode.setValueBySymbol("On");
	bRet = enumNode.setValueBySymbol("Off");
	if (bRet != true)
	{
		printf("set trigger mode fail.\n");
		return false;
	}
	return true;
}
//////////BEGIN/////////
static void displayDeviceInfo(TVector<ICameraPtr>& vCameraPtrList)
{
	ICameraPtr cameraSptr;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> csMsg;

	//printf("Idx Type Vendor     Model      S/N             DeviceUserID    IP Address    \n");
	//printf("------------------------------------------------------------------------------\n");
	for (int cameraIndex = 0; cameraIndex < vCameraPtrList.size(); cameraIndex++)
	{
		cameraSptr = vCameraPtrList[cameraIndex];

		IGigECameraPtr gigeCameraPtr = IGigECamera::getInstance(cameraSptr);
		if (NULL != gigeCameraPtr.get())
		{
			//char message[2000];
			//const wchar_t* asdf;
			Dahua::Infra::CString ip = gigeCameraPtr->getIpAddress();
			//csMsg.Format(L"%s", ip);							//From Dahua CString to CString
			//LPCTSTR a = LPCWSTR(csMsg);									//From CString to int
			////sprintf_s(message, "... format %d", a);				//From int to char

			//AfxMessageBox(csMsg);

			////wsprintfA(" %s", ip.c_str());

		}


	}
}

static char* trim(char* pStr)
{
	char* pDst = pStr;
	char* pTemStr = NULL;
	int ret = -1;

	if (pDst != NULL)
	{
		pTemStr = pDst + strlen(pStr) - 1;
		//壺趼睫揹忑窒諾跡
		while (*pDst == ' ')
		{
			pDst++;
		}
		//壺趼睫揹帣窒諾跡
		while ((pTemStr > pDst) && (*pTemStr == ' '))
		{
			*pTemStr-- = '\0';
		}
	}
	return pDst;
}

static int isInputValid(char* pInpuStr)
{
	char numChar;
	char* pStr = pInpuStr;
	while (*pStr != '\0')
	{
		numChar = *pStr;
		if ((numChar > '9') || (numChar < '0'))
		{
			return -1;
		}
		pStr++;
	}
	return 0;
}

static int selectDevice(int cameraCnt)
{
	//char inputStr[256] = { 0 };
	//char* pTrimStr;
	//int inputIndex = -1;
	//int ret = -1;


	//AfxMessageBox(L"\nPlease input the camera index:", MB_YESNO | MB_ICONINFORMATION);

	//while (1)
	//{

	//	memset(inputStr, 0, sizeof(inputStr));

	//	wsprintfA("%s", inputStr);
	//	//scanf_s("%s", inputStr);

	//	fflush(stdin);


	//	pTrimStr = trim(inputStr);

	//	ret = isInputValid(pTrimStr);
	//	if (ret == 0)
	//	{

	//		inputIndex = atoi(pTrimStr);

	//		inputIndex -= 1;
	//		if ((inputIndex >= 0) && (inputIndex < cameraCnt))
	//		{
	//			break;
	//		}
	//	}

	//	printf("Input invalid! Please input the camera index: ");
	//}
	return 0;
}

//Set ExposureTime
static bool LightsConditionInit(CStringT<wchar_t, StrTraitMFC<wchar_t>> cstr)
{
	Dahua::GenICam::CDoubleNode nodeExposureTime(cameraSptr, "ExposureTime");
	if (!nodeExposureTime.isValid())
	{
		AfxMessageBox(L" get ExposureTime node fail.", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
	}
	double XposureTime = _wtof(cstr);
	if (false == nodeExposureTime.setValue(XposureTime))
	{
		AfxMessageBox(L" set ExposureTime fail.", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
	}

	CIntNode nodebrightness(cameraSptr, "Brightness");
	if (false == nodebrightness.isValid())
	{
		AfxMessageBox(L" get nodebrightness node fail.", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
	}
	if (false == nodebrightness.setValue(40))
	{
		AfxMessageBox(L" set nodebrightness fail.", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
	}

	CDoubleNode nodegainRaw(cameraSptr, "GainRaw");
	if (!nodegainRaw.isValid())
	{
		AfxMessageBox(L" get gainRaw node fail.", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
		
	}
	if (false == nodegainRaw.setValue(15.0))
		//if (false == nodeExposureTime.setValue(dbValue/2))
	{
		AfxMessageBox(L" set nodegainRaw fail.", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
		
	}

	//if (false == nodeExposureTime.getValue(dbValue))
	//{
	//	AfxMessageBox(L" get ExposureTime fail.", MB_YESNO | MB_ICONINFORMATION);
	//	return;
	//}
	return TRUE;
}

static bool CreateThreadandGetImages(DWORD c, DWORD vx, DWORD vz, DWORD vz1, DWORD vpltz)
{
	//Create Thread開始串流
	//goto astar if grabbing failed
	modifyCameraExposureTime(cameraSptr);
	//modifyCameragainAuto(cameraSptr);
	//modifybrightness(cameraSptr);
	astar:
	IStreamSourcePtr streamPtr = systemObj.createStreamSource(cameraSptr);
	bool isStartGrabbingSuccess = streamPtr->startGrabbing();
	if (!isStartGrabbingSuccess)
	{
		AfxMessageBox(L"StartGrabbing  fail!!", MB_YESNO | MB_ICONINFORMATION);
		streamPtr->stopGrabbing();
		goto astar;
	}

	Dahua::Memory::TSharedPtr<StreamRetrieve> streamThreadSptr(new StreamRetrieve(streamPtr));
	if (NULL == streamThreadSptr.get())
	{
		AfxMessageBox(L"get thread FALSE!!", MB_YESNO | MB_ICONINFORMATION);
		return FALSE;
	}
	streamThreadSptr->start(c,vx,vz, vz1,vpltz);   //m_loop = true    return createThread
	CThread::sleep(500);     //1min streaming
	streamThreadSptr->stop();
	streamPtr->stopGrabbing();
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC20191205Dlg 對話方塊


IMPLEMENT_DYNAMIC(CMFC20191205Dlg, CDialogEx);

CMFC20191205Dlg::CMFC20191205Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC20191205_DIALOG, pParent)

	, m_editctrl_v(_T(""))
	, Y_Show(_T(""))
	, Z_Show(_T(""))
	, plat_Z_show(_T(""))
	, z_step(_T(""))

	, exposure_time(0)
	, Exposure_time(_T(""))
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
}

CMFC20191205Dlg::~CMFC20191205Dlg()
{
	// 如果有此對話方塊的 Automation Proxy，
	//  請將其指向此對話方塊的返回指標設為 null，讓其知道
	// 所以會知道是否已經刪除對話方塊。
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;
}

void CMFC20191205Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editCtrl);
	DDX_Text(pDX, IDC_EDIT6, m_editctrl_v);

	DDX_Control(pDX, IDC_EDIT5, Y_EDIT);
	DDX_Text(pDX, IDC_EDIT2, Y_Show);
	DDX_Control(pDX, IDC_EDIT3, Z_edit);
	DDX_Text(pDX, IDC_EDIT4, Z_Show);
	DDX_Control(pDX, IDC_EDIT7, plate_Z_edit);
	DDX_Text(pDX, IDC_EDIT8, plat_Z_show);
	DDX_Control(pDX, IDC_CHECK1, Lights_switch);
	DDX_Control(pDX, IDC_EDIT9, Moving_TImes);
	DDX_Control(pDX, IDC_CHECK2, Stream_ONnOff);
	DDX_Control(pDX, IDC_PICTURE, picpicpic);
	DDX_Text(pDX, IDC_EDIT10, z_step);
	DDX_Scroll(pDX, IDC_SCROLLBAR2, exposure_time);
	DDX_Text(pDX, IDC_EDIT11, Exposure_time);
}

BEGIN_MESSAGE_MAP(CMFC20191205Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC20191205Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC20191205Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC20191205Dlg::OnBnClickedButton2)
	
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC20191205Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC20191205Dlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFC20191205Dlg::OnCbnSelchangeCombo2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFC20191205Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT6, &CMFC20191205Dlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT5, &CMFC20191205Dlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT2, &CMFC20191205Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMFC20191205Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMFC20191205Dlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFC20191205Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT7, &CMFC20191205Dlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CMFC20191205Dlg::OnEnChangeEdit8)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFC20191205Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFC20191205Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_CHECK1, &CMFC20191205Dlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT9, &CMFC20191205Dlg::OnEnChangeEdit9)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFC20191205Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMFC20191205Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMFC20191205Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON12, &CMFC20191205Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_CHECK2, &CMFC20191205Dlg::OnBnClickedCheck2)
	ON_STN_CLICKED(IDC_PICTURE, &CMFC20191205Dlg::OnStnClickedPicture)
	ON_BN_CLICKED(IDC_BUTTON13, &CMFC20191205Dlg::OnBnClickedButton13)
	ON_EN_CHANGE(IDC_EDIT10, &CMFC20191205Dlg::OnEnChangeEdit10)
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR2, &CMFC20191205Dlg::OnNMThemeChangedScrollbar2)
	ON_EN_CHANGE(IDC_EDIT11, &CMFC20191205Dlg::OnEnChangeEdit11)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFC20191205Dlg 訊息處理常式

BOOL CMFC20191205Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	///
	////繫結視窗
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWndl = (HWND)cvGetWindowHandle("view");//hWnd 表示視窗控制代碼,獲取視窗控制代碼
	HWND hParent1 = ::GetParent(hWndl);//GetParent函式一個指定子視窗的父視窗控制代碼
	::SetParent(hWndl, GetDlgItem(IDC_PICTURE)->m_hWnd);
	::ShowWindow(hParent1, SW_HIDE);//ShowWindow指定視窗中顯示
	//UpdateWindow();

	
	///////////
	//((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->SetScrollRange(0, 200000);
	//((CScrollBar*)GetDlgItem(IDC_SCROLLBAR2))->SetScrollPos(100000);
	
	// 將 [關於...] 功能表加入系統功能表。
	//((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
	
	   	  
	//m_edit.SetWindowText(_T("welcome to edit"));
	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CStringT<wchar_t, StrTraitMFC<wchar_t>> strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFC20191205Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。
void CMFC20191205Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此加入您的訊息處理常式程式碼


}

void CMFC20191205Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFC20191205Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 如果控制器仍保持其物件之一，而使用者
// 關閉 UI 時，Automation 伺服器不應該結束。
// 這些訊息處理常式會確認是否仍在使用 Proxy，
// 如果已結束使用，則會隱藏 UI，但是對話方塊
// 仍保持在附近。

void CMFC20191205Dlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMFC20191205Dlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMFC20191205Dlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMFC20191205Dlg::CanExit()
{
	// 如果 Proxy 物件仍在附近，則 Automation 控制器
	// 仍掌控此應用程式。請將對話方塊保持在附近，
	// 但是隱藏其 UI。
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////
//介面功能區

void CMFC20191205Dlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CDialogEx::OnOK();
}
//連線
void CMFC20191205Dlg::OnBnClickedButton1()
{
	
	//PlcAccess->OpenDevice(8501);
	PlcAccess = new CKeyencePlcAccess;
	PlcAccess->OpenDevice(DEFAULT_PORT);

}
//氣壓缸上升
void CMFC20191205Dlg::OnBnClickedButton2()
{
	//氣壓缸上升
	PlcAccess->WriteRegister_MR_BIT(14, 1);

}
//氣壓缸下降
void CMFC20191205Dlg::OnBnClickedButton6()
{
	// 氣壓缸下降
	PlcAccess->WriteRegister_MR_BIT(15, 1);
}
//快速給值
void CMFC20191205Dlg::OnBnClickedButton7()
{
	CEdit* pBoxOne_X, * pBoxOne_Y, * pBoxOne_Z;
	CEdit* pPlateOne_Z;



	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_z;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> strplate_z;

	pBoxOne_X = (CEdit*)GetDlgItem(IDC_EDIT1);
	pBoxOne_Y = (CEdit*)GetDlgItem(IDC_EDIT5);
	pBoxOne_Z = (CEdit*)GetDlgItem(IDC_EDIT3);
	pPlateOne_Z = (CEdit*)GetDlgItem(IDC_EDIT7);

	str2_x.Format((_T("%06d")), DEFAULT_X);		  //DWORD轉換為CSTRING
	str2_y.Format((_T("%06d")), DEFAULT_Y);
	str2_z.Format((_T("%06d")), DEFAULT_Z);
	strplate_z.Format((_T("%06d")), DEFAULT_PZ);

	pBoxOne_X->SetWindowText(str2_x);
	pBoxOne_Y->SetWindowText(str2_y);
	pBoxOne_Z->SetWindowText(str2_z);
	pPlateOne_Z->SetWindowText(strplate_z);

	//PlcAccess->WriteRegister_MR_BIT(7, 1);
	//Lights_Toggle(1);

}
//開關燈
void CMFC20191205Dlg::OnBnClickedCheck1()
{

	// TODO: 在此加入控制項告知處理常式程式碼
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		//WriteRegister_MR_BITTEST1(7, 1 , 7);
		/*PlcAccess->WriteRegister_MR_BIT(7, 1);
		Sleep(1000);*/
			PlcAccess->WriteRegister_MR_BIT(7, 1);
		
	}
	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck())
	{
		PlcAccess->WriteRegister_MR_BIT(7, 0);
	}
	

	
}

//前光三軸移動
void CMFC20191205Dlg::OnBnClickedButton3()
{
	//前光學三軸移動
	//////////////////////////////////////////
	CEdit* pBoxOne_X, *pBoxOne_Y, *pBoxOne_Z;
	CEdit* pBoxTwo_X, * pBoxTwo_Y, * pBoxTwo_Z;
	
	//取得輸入的變量
	pBoxOne_X = (CEdit*)GetDlgItem(IDC_EDIT1);
	pBoxOne_Y = (CEdit*)GetDlgItem(IDC_EDIT5);
	pBoxOne_Z = (CEdit*)GetDlgItem(IDC_EDIT3);
	//pBoxOne_Z = (CEdit*)GetDlgItem();

	//取得現在的位置
	pBoxTwo_X = (CEdit*)GetDlgItem(IDC_EDIT6);
	pBoxTwo_Y = (CEdit*)GetDlgItem(IDC_EDIT2);
	pBoxTwo_Z = (CEdit*)GetDlgItem(IDC_EDIT4);


	CStringT<wchar_t, StrTraitMFC<wchar_t>> str_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str_z;


	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_z;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_z;


	pBoxOne_X->GetWindowText(str_x);    //我去拿第一個框框裡面的值 存到str
	pBoxOne_Y->GetWindowText(str_y);
	pBoxOne_Z->GetWindowText(str_z);
	

	//string到unsigned long int
	DWORD tmp_x = (DWORD)_wtoi(str_x);
	DWORD tmp_y = (DWORD)_wtoi(str_y);
	DWORD tmp_z = (DWORD)_wtoi(str_z);
	/////testingtesting~~~~~~~~~~~~~~~~~~~~~~~~



	//PlcAccess->WriteRegister_MR_BIT(7, 1);
	// Move XYZ
	//判斷速度過快:要找出一個確定讓plc動完之後才更新好的確認訊號 確認收到訊號再下一個動作
	
	if (PlcAccess->WriteRegister_DM_WORD(0, tmp_x)==TRUE && PlcAccess->WriteRegister_DM_WORD(2, tmp_y) == TRUE && PlcAccess->WriteRegister_DM_WORD(4, tmp_z) == TRUE) //前光學XYZ軸改   
	{
		//AfxMessageBox(L"數據讀取成功請確認", MB_YESNO | MB_ICONINFORMATION);

		if (PlcAccess->WriteRegister_MR_BIT(1, 1) == TRUE) //前光學3軸動 pc 寫1
		{

			PlcAccess->WriteRegister_MR_BIT(7, 1);
			//Timer: update windowtext
			
			for (int timer = 0; timer < 64; timer ++)
			{
				valuex = PlcAccess->ReadRegister_DM_WORD(30); //顯示前光學X
				valuey = PlcAccess->ReadRegister_DM_WORD(32); //顯示前光學Y
				valuez = PlcAccess->ReadRegister_DM_WORD(34); //顯示前光學Z
				str2_x.Format((_T("%06d")), valuex);		  //DWORD轉換為CSTRING
				str2_y.Format((_T("%06d")), valuey);
				str2_z.Format((_T("%06d")), valuez);

				pBoxTwo_X->SetWindowText(str2_x);
				pBoxTwo_Y->SetWindowText(str2_y);
				pBoxTwo_Z->SetWindowText(str2_z);
				pBoxTwo_X->UpdateWindow();
				pBoxTwo_Y->UpdateWindow();
				pBoxTwo_Z->UpdateWindow();

				if ((str2_x == tmpt_x) && (str2_y == tmpt_y) && (str2_z == tmpt_z))
				{
					break;
				}
				tmpt_x = str2_x;
				tmpt_y = str2_y;
				tmpt_z = str2_z;

				Sleep(1000);
			}
			PlcAccess->WriteRegister_MR_BIT(101, 0);

			//if (PlcAccess->WriteRegister_MR_BIT(101, 0)) //通知前光學3軸動完成 pc 寫0
			//{
			//	AfxMessageBox(L"前光學三軸移動完成請確認", MB_YESNO | MB_ICONINFORMATION);
			//}				
		}
	}
	
}
//載台Z軸移動
void CMFC20191205Dlg::OnBnClickedButton4()
{
	// 載台Z軸移動
	/////////////////////////////////////////////
	CEdit* pPlateOne_Z;
	CEdit* pPlateTwo_Z;

	//取得輸入的變量
	DWORD valuepz = 0;
	pPlateOne_Z = (CEdit*)GetDlgItem(IDC_EDIT7);
	//取得現在的位置
	pPlateTwo_Z = (CEdit*)GetDlgItem(IDC_EDIT8);

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str_z;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_z;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_z;

	pPlateOne_Z->GetWindowText(str_z);

	DWORD tmp_z = (DWORD)_wtoi(str_z);

	if (PlcAccess->WriteRegister_DM_WORD(12, tmp_z) == TRUE)   //載台Z軸移動座標寫入
	{
		//AfxMessageBox(L"載台Z軸準備移動請確認", MB_YESNO | MB_ICONINFORMATION);

		if (PlcAccess->WriteRegister_MR_BIT(3, 1) == TRUE) //載台Z軸移動
		{
			PlcAccess->WriteRegister_MR_BIT(7, 1);
			//Timer: update windowtext
			for (int timer = 0; timer < 50; timer++)
			{
				valuepz = PlcAccess->ReadRegister_DM_WORD(42); //顯示載台Z軸
				str2_z.Format((_T("%06d")), valuepz);

				pPlateTwo_Z->SetWindowText(str2_z);
				pPlateTwo_Z->UpdateWindow();
			
				if ((str2_z == tmpt_z))
				{
					break;
				}

				tmpt_z = str2_z;

				Sleep(1000);
			}
			if (PlcAccess->WriteRegister_MR_BIT(103, 0)) //通知載台Z軸移動完成 
			{
				//AfxMessageBox(L"載台Z軸移動完成請確認", MB_YESNO | MB_ICONINFORMATION);
			}
		}	
	}
}
//回歸原點
void CMFC20191205Dlg::OnBnClickedButton5()
{
	// 回歸原點
	///////////////////////////////////////////
	CEdit* pBoxTwo_X, * pBoxTwo_Y, * pBoxTwo_Z;

	//取得現在的位置
	pBoxTwo_X = (CEdit*)GetDlgItem(IDC_EDIT6);
	pBoxTwo_Y = (CEdit*)GetDlgItem(IDC_EDIT2);
	pBoxTwo_Z = (CEdit*)GetDlgItem(IDC_EDIT4);

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_z;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_z;


	if (PlcAccess->WriteRegister_MR_BIT(0, 1))    //三軸回歸原點
	{
		PlcAccess->WriteRegister_MR_BIT(7, 1);
		for (int timer = 0; timer < 50; timer++)
		{
			valuex = PlcAccess->ReadRegister_DM_WORD(30); //顯示前光學X
			valuey = PlcAccess->ReadRegister_DM_WORD(32); //顯示前光學Y
			valuez = PlcAccess->ReadRegister_DM_WORD(34); //顯示前光學Z
			str2_x.Format((_T("%06d")), valuex);		  //DWORD轉換為CSTRING
			str2_y.Format((_T("%06d")), valuey);
			str2_z.Format((_T("%06d")), valuez);

			pBoxTwo_X->SetWindowText(str2_x);
			pBoxTwo_Y->SetWindowText(str2_y);
			pBoxTwo_Z->SetWindowText(str2_z);
			pBoxTwo_X->UpdateWindow();
			pBoxTwo_Y->UpdateWindow();
			pBoxTwo_Z->UpdateWindow();

			if ((str2_x == tmpt_x) && (str2_y == tmpt_y) && (str2_z == tmpt_z))
			{
				break;
			}
			tmpt_x = str2_x;
			tmpt_y = str2_y;
			tmpt_z = str2_z;

			Sleep(1000);
		}
		if (PlcAccess->WriteRegister_MR_BIT(100, 0)) //通知前光學3軸原點回歸完成
		{
			AfxMessageBox(L"前光學三軸原點回歸完成請確認", MB_YESNO | MB_ICONINFORMATION);
		}
	}

}
//前光學三軸分段移動測試
void CMFC20191205Dlg::OnBnClickedButton8()
{
	//前光學三軸分段移動測試
	//////////////////////////////////////////
	CEdit* pBoxOne_X, * pBoxOne_Y, * pBoxOne_Z;
	CEdit* pBoxTwo_X, * pBoxTwo_Y, * pBoxTwo_Z;
	CEdit* pBoxThree_X;

	//取得輸入的變量
	pBoxOne_X = (CEdit*)GetDlgItem(IDC_EDIT1);
	//pBoxOne_Z = (CEdit*)GetDlgItem();

	//取得現在的位置
	pBoxTwo_X = (CEdit*)GetDlgItem(IDC_EDIT6);
	pBoxTwo_Y = (CEdit*)GetDlgItem(IDC_EDIT2);
	pBoxTwo_Z = (CEdit*)GetDlgItem(IDC_EDIT4);

	pBoxThree_X = (CEdit*)GetDlgItem(IDC_EDIT9);

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str_x;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_z;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str3_x;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_x;

	DWORD movex;
	DWORD movex_s;
	DWORD start_x;

	pBoxOne_X->GetWindowText(str_x);    //我去拿第一個框框裡面的值 存到str

	pBoxThree_X->GetWindowText(str3_x);  //移動的次數

	//string到unsigned long int
	DWORD tmp_x = (DWORD)_wtoi(str_x);
	DWORD times_x = (DWORD)_wtoi(str3_x);//移動的次數


	//目前的位置
	start_x = PlcAccess->ReadRegister_DM_WORD(30);

	//目標座標比現在座標大或是小 制定移動距離
	//大
	if (start_x < tmp_x)
	{
		movex = tmp_x - start_x;
	}
	//小
	else
		movex = start_x - tmp_x;  //  movex移動距離

	movex_s = movex / times_x;   //每次移動距離

	//開始移動
	for (DWORD counts = 0; counts < times_x; counts++)
	{
		//目標座標比現在座標大或是小 制定每次的目標座標
		if (start_x < tmp_x)
			tmp_x = start_x + movex_s * (counts + 1);
		else
			tmp_x = start_x - movex_s * (counts + 1);

		//開始讀取X 並移動
		if (PlcAccess->WriteRegister_DM_WORD(0, tmp_x) == TRUE) //前光學XYZ軸改   
		{
			AfxMessageBox(L"已讀取，準備移動", MB_YESNO | MB_ICONINFORMATION);

			if (PlcAccess->WriteRegister_MR_BIT(1, 1) == TRUE) //前光學3軸動 pc 寫1
			{
				PlcAccess->WriteRegister_MR_BIT(7, 1);
				//Timer: update windowtext
				tmpt_x = L"0";
				for (int timer = 0; timer < 64; timer++)
				{
					valuex = PlcAccess->ReadRegister_DM_WORD(30); //顯示前光學X
					valuey = PlcAccess->ReadRegister_DM_WORD(32); //顯示前光學Y
					valuez = PlcAccess->ReadRegister_DM_WORD(34); //顯示前光學Z
					str2_x.Format((_T("%06d")), valuex);		  //DWORD轉換為CSTRING
					str2_y.Format((_T("%06d")), valuey);
					str2_z.Format((_T("%06d")), valuez);

					pBoxTwo_X->SetWindowText(str2_x);
					pBoxTwo_Y->SetWindowText(str2_y);
					pBoxTwo_Z->SetWindowText(str2_z);
					pBoxTwo_X->UpdateWindow();
					pBoxTwo_Y->UpdateWindow();
					pBoxTwo_Z->UpdateWindow();

					if ((str2_x == tmpt_x))    //移動完成
					{
						break;
					}
					else
						tmpt_x = str2_x;

					Sleep(1200);
				}
			}
		}
		AfxMessageBox(L"移動暫停，存取影像....", MB_YESNO | MB_ICONINFORMATION);
		Sleep(800);
	}
	//完成
	if (PlcAccess->WriteRegister_MR_BIT(101, 0)) //通知前光學3軸動完成 pc 寫0
	{
		AfxMessageBox(L"前光學三軸移動完成請確認", MB_YESNO | MB_ICONINFORMATION);
	}
}
//相機連線
void CMFC20191205Dlg::OnBnClickedButton9()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	bRet = systemObj.discovery(vCameraPtrList);

	if (!bRet)
	{
		AfxMessageBox(L"discovery device failed.\n", MB_YESNO | MB_ICONINFORMATION);
	}

	if (0 == vCameraPtrList.size())
	{
		AfxMessageBox(L"no camera device find.\n", MB_YESNO | MB_ICONINFORMATION);
	}

	int cameraIndex = selectDevice(vCameraPtrList.size());

	cameraSptr = vCameraPtrList[cameraIndex];
	//cameraSptr->connect()
	if (cameraSptr->connect())
	{
		AfxMessageBox(L"Camera connected.\n", MB_YESNO | MB_ICONINFORMATION);
	}
	if (!cameraSptr->connect())
	{
		AfxMessageBox(L"Connection failed.\n", MB_YESNO | MB_ICONINFORMATION);
	}
}
//////存取移動X軸測試 
void CMFC20191205Dlg::OnBnClickedButton10()
{
	CEdit* pBoxOne_X, * pBoxOne_Y, * pBoxOne_Z;
	CEdit* pBoxTwo_X, * pBoxTwo_Y, * pBoxTwo_Z;
	CEdit* pBoxThree_X;

	//取得輸入的變量
	pBoxOne_X = (CEdit*)GetDlgItem(IDC_EDIT1);
	//pBoxOne_Z = (CEdit*)GetDlgItem();

	//光學現在的位置
	pBoxTwo_X = (CEdit*)GetDlgItem(IDC_EDIT6);
	pBoxTwo_Y = (CEdit*)GetDlgItem(IDC_EDIT2);
	pBoxTwo_Z = (CEdit*)GetDlgItem(IDC_EDIT4);
	//光學移動的次數
	pBoxThree_X = (CEdit*)GetDlgItem(IDC_EDIT9);

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str_x;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_z;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str3_x;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_x;

	DWORD movex;
	DWORD movex_s;
	DWORD start_x;

	pBoxOne_X->GetWindowText(str_x);    //x框框裡面的值 存到str

	pBoxThree_X->GetWindowText(str3_x);  //移動的次數

	//string到unsigned long int
	DWORD tmp_x = (DWORD)_wtoi(str_x);   //x框框裡面的值 存到DWORD
	DWORD times_x = (DWORD)_wtoi(str3_x);//移動的次數


	//目前的位置
	start_x = PlcAccess->ReadRegister_DM_WORD(30);  

	//目標座標比現在座標大或是小 制定移動距離
	//大
	if (start_x < tmp_x)
	{
		movex = tmp_x - start_x;
	}
	//小
	else
		movex = start_x - tmp_x;  //  movex移動距離

	movex_s = movex / times_x;   //每次移動距離



	//開始移動
	for (DWORD counts = 0; counts < times_x; counts++)
	{
		//目標座標比現在座標大或是小 制定每次的目標座標
		if (start_x < tmp_x)
			tmp_x = start_x + movex_s * (counts + 1);
		else
			tmp_x = start_x - movex_s * (counts + 1);

		//開始讀取X 並移動
		if (PlcAccess->WriteRegister_DM_WORD(0, tmp_x) == TRUE) //前光學XYZ軸改   
		{
			AfxMessageBox(L"已讀取，準備移動", MB_YESNO | MB_ICONINFORMATION);

			if (PlcAccess->WriteRegister_MR_BIT(1, 1) == TRUE) //前光學3軸動 pc 寫1
			{
				PlcAccess->WriteRegister_MR_BIT(7, 1);
				//Timer: update windowtext
				tmpt_x = L"0";
				for (int timer = 0; timer < 64; timer++)
				{
					valuex = PlcAccess->ReadRegister_DM_WORD(30); //顯示前光學X
					valuey = PlcAccess->ReadRegister_DM_WORD(32); //顯示前光學Y
					valuez = PlcAccess->ReadRegister_DM_WORD(34); //顯示前光學Z
					str2_x.Format((_T("%06d")), valuex);		  //DWORD轉換為CSTRING
					str2_y.Format((_T("%06d")), valuey);
					str2_z.Format((_T("%06d")), valuez);
					pBoxTwo_X->SetWindowText(str2_x);
					pBoxTwo_Y->SetWindowText(str2_y);
					pBoxTwo_Z->SetWindowText(str2_z);
					pBoxTwo_X->UpdateWindow();
					pBoxTwo_Y->UpdateWindow();
					pBoxTwo_Z->UpdateWindow();
					Sleep(500);//給予光學移動短暫移動時間 若完成便不會移動
					if ((str2_x == tmpt_x))    //移動完成
					{
						break;
					}
					else
						tmpt_x = str2_x;      //移動尚未完成

					Sleep(500);//給予光學移動短暫移動時間 若完成便不會移動
				}
			}
		}
		//AfxMessageBox(L"移動暫停，存取影像...", MB_YESNO | MB_ICONINFORMATION);
		//CreateThreadandGetImages(counts, valuex, valuez, valuepltz);

		AfxMessageBox(L"存成功。", MB_YESNO | MB_ICONINFORMATION);



	}
	//完成
	
	if (PlcAccess->WriteRegister_MR_BIT(101, 0)) //通知前光學3軸動完成 pc 寫0
	{
		AfxMessageBox(L"前光學三軸移動完成請確認", MB_YESNO | MB_ICONINFORMATION);

	}

}
//調整曝光時間按鈕
void CMFC20191205Dlg::OnBnClickedButton12()
{
	CEdit* pBoxExposureTime;
	pBoxExposureTime = (CEdit*)GetDlgItem(IDC_EDIT11);
	CStringT<wchar_t, StrTraitMFC<wchar_t>> cstr;//光學載台Z移動距離
	pBoxExposureTime->GetWindowText(cstr);
	LightsConditionInit(cstr);
}
//串流開關
void CMFC20191205Dlg::OnBnClickedCheck2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	IStreamSourcePtr streamPtr = systemObj.createStreamSource(cameraSptr);
	bool isStartGrabbingSuccess = streamPtr->startGrabbing();
	if (!isStartGrabbingSuccess)
	{
		AfxMessageBox(L"Stop Grabbing.", MB_YESNO | MB_ICONINFORMATION);
	}

	int frameCount = 0;
	int j = 0;
	Size dsize = Size(3072 * 0.625 * 0.9 * 0.5, 2048 * 0.5 * 0.9 * 0.5);
	Mat image2;
	//Mat m2(2048 * 0.5 * 0.9 * 0.5, 3072 * 0.625 * 0.9 * 0.5, CV_8UC1, Scalar(0, 0, 0));
	image2 = Mat(dsize, CV_8U);
	cv::Mat mat;

	while (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck())
	{
		CFrame frame;

		bool isSuccess = streamPtr->getFrame(frame, 100);
		if (!isSuccess)
		{
			continue;
		}
		bool isValid = frame.valid();
		if (!isValid)
		{
			continue;
		}

		uint32_t* JPEG;
		JPEG = (uint32_t*)malloc(sizeof(uint32_t) * frame.getImageSize());
		if (JPEG) {
			memcpy(JPEG, frame.getImage(), frame.getImageSize());
		}
		mat = cv::Mat(frame.getImageHeight(), frame.getImageWidth(), CV_8UC1, JPEG);

		//imshow approac one
		cv::resize(mat, image2, dsize);
		free(JPEG);
		cv::imshow("view", image2);
		cv::waitKey(30);
		 
	}
	//AfxMessageBox(L"unchecked!", MB_YESNO | MB_ICONINFORMATION);
	//streamPtr->stopGrabbing();
}
//chuck and camera z elevation
void CMFC20191205Dlg::OnBnClickedButton13()
{
	//((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(FALSE);
	// TODO: 在此加入控制項告知處理常式程式碼
	CEdit* pBoxOne_X, * pBoxOne_Y, * pBoxOne_Z;
	CEdit* pBoxTwo_X, * pBoxTwo_Y, * pBoxTwo_Z;
	CEdit* pBoxTimes;
	CEdit* pBoxDistance;
	CEdit* pPlateOne_Z;
	CEdit* pPlateTwo_Z;

	//取得Z的變量
	//pBoxOne_Z = (CEdit*)GetDlgItem(IDC_EDIT3);      //cameraz
	//pPlateOne_Z = (CEdit*)GetDlgItem(IDC_EDIT7);    //chuckz
	//光學載台移動的次數 距離
	pBoxTimes = (CEdit*)GetDlgItem(IDC_EDIT9);
	pBoxDistance = (CEdit*)GetDlgItem(IDC_EDIT10);
	//光學現在的位置
	pBoxTwo_X = (CEdit*)GetDlgItem(IDC_EDIT6);
	pBoxTwo_Y = (CEdit*)GetDlgItem(IDC_EDIT2);
	pBoxTwo_Z = (CEdit*)GetDlgItem(IDC_EDIT4);
	//載台現在的位置
	pPlateTwo_Z = (CEdit*)GetDlgItem(IDC_EDIT8);

	//CStringT<wchar_t, StrTraitMFC<wchar_t>> str_z; //光學Z移動座標
	//CStringT<wchar_t, StrTraitMFC<wchar_t>> strplt_z; //載台Z移動座標

	//光學載台顯示座標使用
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_x;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_z;
	//CStringT<wchar_t, StrTraitMFC<wchar_t>> str2_y;
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str2plt_z;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> str3_z;//光學載台Z移動次數
	CStringT<wchar_t, StrTraitMFC<wchar_t>> str3d_z;//光學載台Z移動距離


	//pBoxOne_Z->GetWindowText(str_z);    //光學z移動座標 存到str_z
	//pPlateOne_Z->GetWindowText(strplt_z);//載台Z移動座標 存到strplt_z
	pBoxTimes->GetWindowText(str3_z);  //移動的次數 存到str3_z
	pBoxDistance->GetWindowText(str3d_z);  //移動的距離 存到str3d_z

	//string到unsigned long int
	//DWORD tmp_z = (DWORD)_wtoi(str_z);   //光學z移動座標 存到DWORD tmp_z
	//DWORD tmpplt_z = (DWORD)_wtoi(strplt_z);//載台Z移動座標 存到DWORD tmpplt_z
	DWORD times_z = (DWORD)_wtoi(str3_z);//光學載台移動的次數 存到DWORD times_z
	DWORD distance_z = (DWORD)_wtoi(str3d_z);//光學載台移動的距離 存到DWORD distance_z
	//目前的位置
	DWORD start_z = PlcAccess->ReadRegister_DM_WORD(34);  //光學
	DWORD startplt_z = PlcAccess->ReadRegister_DM_WORD(42); //載台
	DWORD tmpz;
	DWORD tmpplatez;

	DWORD compx;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmpt_z;

	CStringT<wchar_t, StrTraitMFC<wchar_t>> tmptplt_z;

	//開啟EXCEL
	ofstream ExcelFile;
	
	ExcelFile.open("C:\\Users\\陳聖諺\\Desktop\\SoftwareExcel.csv", ofstream::out | ofstream::app);
	//先預設成都是往上走 走完要回歸原點
	double db = 0.0;
	DWORD accu_compen_z = 0;
	DWORD accu_compen_x = 0;
	ExcelFile << "次數, 補償的光學X, Before光學Z,After光學Z, 載台Z" << endl;
	CreateThreadandGetImages(0, DEFAULT_X, DEFAULT_Z, DEFAULT_Z, DEFAULT_PZ);
	//db += 1.0;
	ExcelFile << 0 << "," << DEFAULT_X << "," << DEFAULT_Z << "," << DEFAULT_Z << "," << DEFAULT_PZ << endl;
	for (DWORD counts = 0; counts < times_z; counts++)
	{
		//Z補償
		DWORD compen_opt_z = 0;
		if (counts == 1  || counts == 9 || counts == 12 || counts == 13)
		{
			compen_opt_z = 2;
			accu_compen_z += compen_opt_z;
		}
		if (counts == 3 || counts == 5 || counts == 10 || counts == 11 || counts == 14)
		{
			compen_opt_z = 1;
			accu_compen_z += compen_opt_z;
		}
		if (counts == 7 || counts == 8 || counts == 15)
		{
			compen_opt_z = -1;
			accu_compen_z += compen_opt_z;
		}

		//X補償表
		DWORD compen_opt_x = 0;
		if (counts == 10 )
		{
			compen_opt_x = 3;
			accu_compen_x += compen_opt_x;
		}
		if (counts == 2 || counts == 9 || counts == 11 )
		{
			compen_opt_x = 1;
			accu_compen_x += compen_opt_x;
		}
		if (counts == 3 || counts == 8 || counts == 18)
		{
			compen_opt_x = -1;
			accu_compen_x += compen_opt_x;
		}
		if (counts == 6 || counts == 7)
		{
			compen_opt_z = -2;
			accu_compen_x += compen_opt_z;
		}
		if (counts == 13 || counts == 14)
		{
			compen_opt_x = -3;
			accu_compen_x += compen_opt_x;
		}
		if (counts == 4 || counts == 15 || counts == 16 || counts == 17)
		{
			compen_opt_x = -4;
			accu_compen_x += compen_opt_x;
		}
		if (counts == 5)
		{
			compen_opt_x = -6;
			accu_compen_x += compen_opt_x;
		}
		//制定每次的目標座標
		tmpz = start_z + distance_z * (counts + 1) + accu_compen_z;
		//tmpz = start_z + distance_z * (counts + 1) ;
		tmpplatez = startplt_z + distance_z * (counts + 1);
		//x補償後的目標座標
		compx = DEFAULT_X + accu_compen_x;

		//開始讀取XZ並移動
		if (PlcAccess->WriteRegister_DM_WORD(0, compx) && PlcAccess->WriteRegister_DM_WORD(4, tmpz) && PlcAccess->WriteRegister_DM_WORD(12, tmpplatez)) //前光學 載台 Z軸改   前光學 X軸補償
		{
			//AfxMessageBox(L"已讀取，準備移動", MB_YESNO | MB_ICONINFORMATION);

			if (PlcAccess->WriteRegister_MR_BIT(1, 1) && PlcAccess->WriteRegister_MR_BIT(3, 1)) //前光學 載台z軸動 

				PlcAccess->WriteRegister_MR_BIT(7, 1);
			//Timer: update windowtext
			tmpt_z = L"0";    //
			tmptplt_z = L"0";    //
			for (int timer = 0; timer < 64; timer++)
			{

				valuex = PlcAccess->ReadRegister_DM_WORD(30); //顯示前光學X
				valuey = PlcAccess->ReadRegister_DM_WORD(32); //顯示前光學Y
				valuez = PlcAccess->ReadRegister_DM_WORD(34); //顯示前光學Z
				valuepltz = PlcAccess->ReadRegister_DM_WORD(42); //顯示載台Z
				str2_x.Format((_T("%06d")), valuex);		  //DWORD轉換為CSTRING
				str2_y.Format((_T("%06d")), valuey);
				str2_z.Format((_T("%06d")), valuez);
				str2plt_z.Format((_T("%06d")), valuepltz);

				pBoxTwo_X->SetWindowText(str2_x);
				pBoxTwo_Y->SetWindowText(str2_y);
				pBoxTwo_Z->SetWindowText(str2_z);
				pPlateTwo_Z->SetWindowText(str2plt_z);

			/*	pBoxTwo_X->UpdateWindow();
				pBoxTwo_Y->UpdateWindow();
				pBoxTwo_Z->UpdateWindow();
				pPlateTwo_Z->UpdateWindow();*/

				Sleep(500);//給予短暫移動時間 若完成便不會移動
				if ((str2_z == tmpt_z) && (str2plt_z == tmptplt_z))    //移動完成
				{
					break;
				}
				else
				{
					tmpt_z = str2_z;      //光學移動尚未完成
					tmptplt_z = str2plt_z;//載台移動尚未完成

					Sleep(500);//給予短暫移動時間 若完成便不會移動
				}
			}
		}
		//AfxMessageBox(L"移動暫停，存取影像...", MB_YESNO | MB_ICONINFORMATION);
		//存影像 輸入資訊:第幾次 光學xz 載台z
		CreateThreadandGetImages(counts+1, valuex, start_z + distance_z * (counts + 1), valuez,  valuepltz + distance_z * (counts + 1));
		//db += 1.0;
		ExcelFile << counts << "," << valuex << "," << start_z + distance_z * (counts + 1) << "," << valuez << "," << valuepltz << endl;
		//AfxMessageBox(L"存成功。", MB_YESNO | MB_ICONINFORMATION);
	}
	ExcelFile.close();
	//完成
	if (PlcAccess->WriteRegister_MR_BIT(101, 0) && PlcAccess->WriteRegister_MR_BIT(103, 0)) //通知前光學3軸動完成 pc 寫0
	{
		AfxMessageBox(L"光學載台Z軸移動完成請確認", MB_YESNO | MB_ICONINFORMATION);
	}
	//((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(TRUE);
}

//////////////////////////////////////////////////////////////////////////////////

void CMFC20191205Dlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}

void CMFC20191205Dlg::OnEnChangeEdit1()
{

}

void CMFC20191205Dlg::OnEnChangeEdit6()
{

}

void CMFC20191205Dlg::OnEnUpdateEdit6()
{

}

void CMFC20191205Dlg::OnEnChangeEdit5()
{

}

void CMFC20191205Dlg::OnEnChangeEdit2()
{

}

void CMFC20191205Dlg::OnEnChangeEdit3()
{

}

void CMFC20191205Dlg::OnEnChangeEdit4()
{

}

void CMFC20191205Dlg::OnEnChangeEdit7()
{

}

void CMFC20191205Dlg::OnEnChangeEdit8()
{

}

void CMFC20191205Dlg::OnEnChangeEdit9()
{
	// TODO:  在此加入控制項告知處理常式程式碼
}

void CMFC20191205Dlg::OnStnClickedPicture()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}

void CMFC20191205Dlg::OnEnChangeEdit10()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
}

void CMFC20191205Dlg::OnNMThemeChangedScrollbar2(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 此功能需要 Windows XP 或更新的版本。
	// 符號 _WIN32_WINNT 必須是 >= 0x0501。
	// TODO: 在此加入控制項告知處理常式程式碼
	*pResult = 0;


}

void CMFC20191205Dlg::OnEnChangeEdit11()
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
}



