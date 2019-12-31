#pragma once

#include <windows.h>
class EthernetPort
{
public:
	EthernetPort(void);
	~EthernetPort(void);

	
	BOOL WriteEthernetPort(char* szString, int nLengthToWrite);
	BOOL ReadEthernetPort(char* szString, int* nLengthRead);
	void CloseEthernetPort();

protected:

	BOOL WriteEthernetPort_non_overlapped(char* szString, int nLengthToWrite);
	BOOL ReadEthernetPort_non_overlapped(char* szString, int* nLengthRead);

	
	//HANDLE m_hMutex;
};