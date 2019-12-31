#ifndef __DAHUA_GENICAM_ICAMERA_H__
#define __DAHUA_GENICAM_ICAMERA_H__


#include "Defs.h"
#include "Frame.h"
#include "Memory/SharedPtr.h"
#include "StreamSource.h"

GENICAM_NAMESPACE_BEGIN


class GENICAM_API ICamera
{
protected:

	virtual ~ICamera(){}
	
public:

	enum ECameraAccessPermission
	{
		accessPermissionOpen = 0, /// < \~english The GigE vision device isn't connected to any application. 
		accessPermissionExclusive, ///< \~english Exclusive Access Permission   
		accessPermissionControl, 	///< \~english Non-Exclusive Readbale Access Permission  
		accessPermissionControlWithSwitchover,  	///< \~chinese Control access with switchover enabled.        ///< \~english Control access with switchover enabled.	
		accessPermissionUnknown = 254,  	///< \~english Value not known; indeterminate.   	
		accessPermissionUndefined     	///< \~english Undefined Access Permission
	};

	enum ECameraType
	{
		typeGige = 0,	        ///< \~english GigE Vision Camera
		typeU3v = 1,	       ///< \~english USB3.0 Vision Camera
        typeCL = 2,		   ///< \~english Cameralink camera
        typePCIe = 3,           ///< \~english PCIe Camera
		typeUndefined = 255	      ///< \~english Undefined Camera
	};
	

	virtual int32_t getType() const = 0;
	

	virtual const char * getName() = 0;
	

	virtual const char * getKey()  = 0;
	

	virtual bool connect(ECameraAccessPermission accessPermission = accessPermissionControl) = 0;
		

	virtual bool disConnect() = 0;
		

	virtual bool isConnected() = 0;
		      								

	virtual const char * getInterfaceName()  = 0;

	virtual int32_t getInterfaceType() const = 0;
	

	virtual bool downLoadGenICamXML(const char* aFullFilename) = 0;


	virtual size_t readUserPrivateData(void* pBuffer, size_t dwCount) = 0;
	

	virtual size_t writeUserPrivateData(const void *pBuffer, size_t dwCount) = 0;

	virtual const char * getVendorName() = 0;

	virtual const char * getModelName() = 0;


	virtual const char * getSerialNumber() = 0;

	virtual const char * getDeviceVersion() = 0;

	virtual size_t writeUARTData(const void* pBuffer, size_t dwCount) = 0;


	virtual size_t readUARTData(void* pBuffer, size_t dwCount) = 0;

    virtual const char * getManufactureInfo() = 0;
};

typedef Memory::TSharedPtr<ICamera> ICameraPtr;


GENICAM_NAMESPACE_END

#endif //__DAHUA_GENICAM_ICAMERA_H__
