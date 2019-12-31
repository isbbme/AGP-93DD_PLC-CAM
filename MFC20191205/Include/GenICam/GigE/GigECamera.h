#ifndef __DAHUA_GENICAM_IGIGECAMERA_H__
#define __DAHUA_GENICAM_IGIGECAMERA_H__

#include "GenICam/Defs.h"
#include "GenICam/Camera.h"
#include "Infra/String.h"
#include "Memory/SharedPtr.h"

GENICAM_NAMESPACE_BEGIN

class IGigECamera;
typedef Memory::TSharedPtr<IGigECamera> IGigECameraPtr;


/// \~english
/// \brief	camera object interface class
/// \defgroup GigECamera API for GigEVision Cameras Only

/// \~english
/// \brief GigE camera object
class GENICAM_API IGigECamera
{
public:

	enum ECameraAccessPermission
	{
		accessPermissionOpen = 0,		///< \~chinese        ///< \~english The GigE vision device isn't connected to any application. 
		accessPermissionExclusive, 	///< \~chinese         ///< \~english Exclusive Access Permission   
		accessPermissionControl, 	///< \~chinese   ///< \~english Non-Exclusive Readbale Access Permission  
		accessPermissionControlWithSwitchover,  	///< \~chinese Control access with switchover enabled.        ///< \~english Control access with switchover enabled.	
		accessPermissionUnknown = 254,  	///< \~chinese         ///< \~english Value not known; indeterminate.   	
		accessPermissionUndefined     	///< \~chinese       ///< \~english Undefined Access Permission
	};

protected:

	/// \~english
	/// \brief destruct function 
	virtual ~IGigECamera(){}

public: 

	/// \~english
	/// \brief GigE GigE camera object access interface, same cameraPtr is correspond to same GigE camera object
	/// \brief [in] cameraPtr Smart pointer object of GigE camera, if the cameraPtr point to a camera which is not GigE camera, the interface return NULL which means it is invalid
	static  IGigECameraPtr getInstance(const ICameraPtr &cameraPtr);
	

	/// \~english
	/// \brief	get ipAddress of camera
	/// \return success:return ipAddress of camera, fail:return empty string 
	virtual Infra::CString getIpAddress() const = 0;


	/// \~english
	/// \brief	get subnetMask of camera
	/// \return success:return camera's subnetMask, fail:return empty string 
	virtual Infra::CString getSubnetMask() const = 0;

	/// \~english
	/// \brief	get gateway of camera
	/// \return success:return camera's gateway, fail:return empty string 
	virtual Infra::CString getGateway() const = 0;


	/// \~english
	/// \brief	get macAddress of camera
	/// \return success:return camera's macAddress, fail:return empty string 
	virtual Infra::CString getMacAddress() const = 0;
	
	/// \~english
	/// \brief  modify device IP	
	/// \brief 1.When callback this function, if the values of newSubnetMask and newGateway are both valid then we consider the value is correct
	/// \brief 2.When callback this function, if the values of newSubnetMask and newGateway are both NULL, then these values will be replaced by the subnetmask and gateway of NIC which this camera connect to.
	/// \brief 3.When callback this function, if there is one value of newSubnetMask or newGateway is NULL and the other one is not NULL, then return failed
	/// \brief this interface only serve the devices which is connected to NIC. As for other devices, callback this function won't work and return failed
	/// \param [in] newIpAddress  new IP address 
	/// \param [in] newSubnetMask new SubnetMask
	/// \param [in] newGateway    new Gateway
	/// \retval true  modify IP failed
	/// \retval false modify IP success
	virtual bool forceIpAddress (const char* newIpAddress, const char* newSubnetMask = NULL, const char* newGateway = NULL) = 0;

	/// \~english
	/// \brief	get current access permission of camera
	/// \return success:return current access permission of camera, fail:return accessPermissionUnknown 
	virtual ECameraAccessPermission getAccessPermission() const = 0;


    /// \~english
    /// \brief	get Protocol Version of camera
    /// \return success:return camera's Protocol Version, fail:return empty string 
    virtual Infra::CString getProtocolVersion() const = 0;

    /// \~english
    /// \brief	get IP Configuration of camera
    /// \return success:return camera's IP Configuration, fail:return empty string 
    virtual Infra::CString getIPConfiguration() const = 0;

	/// \~english
	/// \brief Set the response timeout interval of camera sends command to SDK
	/// \param [in] Timeout interval, unit:ms
	/// \retval false Configuration fail
	/// \retval true  Configuration success
	virtual bool setAnswerTimeout(uint16_t timeout) = 0;

	/// \~english
	/// \brief	get IP Configuration options of camera
	/// \return success:return camera's IP Configuration options, fail:return 0 
	/// \return value:4 camera supports LLA 
	/// \return value:5 camera supports LLA and Persistent IP
	/// \return value:6 camera supports LLA and DHCP
	/// \return value:7 camera supports LLA, DHCP and Persistent IP
	/// \return value:0 fail
	virtual uint32_t getIpConfigOptions() const = 0;


	/// \~english
	/// \brief	get current IP Configuration options of camera
	/// \return success:return camera's current IP Configuration options, fail:return 0 
	/// \return value:4 LLA is active
	/// \return value:5 LLA and Persistent IP are active
	/// \return value:6 LLA and DHCP are active
	/// \return value:7 LLA, DHCP and Persistent IP are active
	/// \return value:0 fail
	virtual uint32_t getIpConfigCurrent() const = 0;
};


GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_IGIGECAMERA_H__