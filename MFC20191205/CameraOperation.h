#pragma once

#ifndef CameraOperationH
#define CameraOperationH

#include <stdint.h>
//#include "sdk.h"
#include <windows.h>


#pragma pack(2)

typedef struct DH_tagBITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} DH_BITMAPFILEHEADER;
#pragma pack()

#endif