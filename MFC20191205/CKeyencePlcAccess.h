#pragma once
#include <windows.h>
#include "EthernetPort.h"

class CKeyencePlcAccess
{
public:
	CKeyencePlcAccess(void);
	~CKeyencePlcAccess(void);

	BOOL OpenDevice(int port_num);
	void CloseDevice();

	BOOL WriteRegister_MR_BIT(int regNum, BYTE value);
	BOOL ReadRegister_MR_BIT(int regNum, BYTE* value);

	BOOL WriteRegister_DM_WORD(int regNum, DWORD value);
	//BOOL ReadRegister_DM_WORD(int regNum, WORD* value);
	//BOOL ReadRegister_DM_WORD(int regNum, int* value);
	int ReadRegister_DM_WORD(int regNum);

	//BOOL Lights_Toggle(DWORD v);
	//void ResetProgram();

protected:

	//BOOL StartComm();
	
	//BOOL StopComm();

	EthernetPort* m_pEtherPort;
	

};
