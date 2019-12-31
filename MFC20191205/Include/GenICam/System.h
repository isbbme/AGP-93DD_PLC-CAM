#ifndef __DAHUA_GENICAM_CSYSTEM_H__
#define __DAHUA_GENICAM_CSYSTEM_H__

#include "Defs.h"
#include "Camera.h"
#include "StreamSource.h"
#include "ParameterNode.h"
#include "AcquisitionControl.h"
#include "AnalogControl.h"
#include "ImageFormatControl.h"
#include "ISPControl.h"
#include "UserSetControl.h"
#include "DeviceControl.h"
#include "TransportLayerControl.h"
#include "DigitalIOControl.h"
#include "EventSubscribe.h"


GENICAM_NAMESPACE_BEGIN


class GENICAM_API CSystem
{
public:

	enum EInterfaceType
	{
		typeGige = 0,	        ///< \~english GigE Vision Protocol
		typeUsb3 = 1,	     ///< \~english USB3.0 Vision Protocol
		typeCL   = 2,	  ///< \~english Camera Link Protocol
        typePCIe = 3,	      ///< \~english PCIe Protocol
		typeAll  = 255   ///< \~english ALL Supported Protocol
	};
	
	
	///< \~english
	///enumeration: physical interface type extension, support any combination of interface types, only can be used in new camera discovery interface
	enum EInterfaceTypeEx
	{
		interfaceTypeGige = 0x00000001,	   		///< \~english NIC type
		interfaceTypeUsb3 = 0x00000002,	   		///< \~english USB3.0 interface type
		interfaceTypeCL   = 0x00000004,	  	///< \~english CAMERALINK interface type
        interfaceTypePCIe = 0x00000008,            ///< \~english PCIe interface type
		interfaceTypeAll  = 0x00000000     	///< \~english ALL interfaces
	};
	

	/// \~english
	/// \brief CSystem singleton acquisition interface
	/// \return CSystem pointer to the singleton object
	static CSystem& getInstance();


	/// \~english
	/// \brief discover reachable camera which has specified interface type
	/// \param [out] vCameraPtrList camera instance list of specified interface type. when interfaceType = typeAll, discover camerass in all interfaces
	/// \param [in]  interfaceType  interface type.
	/// \return success:true, fail:false
	bool discovery(Infra::TVector<ICameraPtr>& vCameraPtrList, EInterfaceType interfaceType = typeAll);
	

	/// \~english
	/// \brief get smart pointers to Camera according to Camera key "vendor:serial number"
	/// \param [in] pCameraKey Camera's key
	/// \return Camera smart pointer. if the parameter pCameraKey does not exist or is invalid, return empty smart pointer object
	ICameraPtr getCameraPtr(const char * pCameraKey) const;

	/// \~english
	/// \brief create stream object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \param [in] channelId stream channel id, default is 0 
	/// \return smart pointer to stream
	IStreamSourcePtr createStreamSource(const ICameraPtr &cameraPtr, uint16_t channelId = 0);


	/// \~english
	/// \brief create event subscribe object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return event subscribe object
	IEventSubscribePtr createEventSubscribe(const ICameraPtr &cameraPtr);


	/// \~english
	/// \brief create AcquisitionControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return AcquisitionControl object
	IAcquisitionControlPtr createAcquisitionControl(const ICameraPtr &cameraPtr);


	/// \~english
	/// \brief create AnalogControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return AnalogControl object
	IAnalogControlPtr createAnalogControl(const ICameraPtr &cameraPtr);


	/// \~english
	/// \brief create ISPControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return ISPControl object
	IISPControlPtr createISPControl(const ICameraPtr &cameraPtr);

	/// \~english
	/// \brief create ImageFormatControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return ImageFormatControl object
	IImageFormatControlPtr createImageFormatControl(const ICameraPtr &cameraPtr);


	/// \~english
	/// \brief create UserSetControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return UserSetControl object
	IUserSetControlPtr createUserSetControl(const ICameraPtr &cameraPtr);


	/// \~english
	/// \brief create DeviceControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return DeviceControl object
	IDeviceControlPtr createDeviceControl(const ICameraPtr &cameraPtr);
	
	/// \~english
	/// \brief create TransportLayerControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return TransportLayerControl object
	ITransportLayerControlPtr createTransportLayerControl(const ICameraPtr &cameraPtr);

	/// \~english
	/// \brief create DigitalIOControl object
	/// \param [in] cameraPtr smart pointer to Camera
	/// \return DigitalIOControl object
    IDigitalIOControlPtr createDigitalIOControl(const ICameraPtr &cameraPtr);

	/// \~english
	/// \brief get version information
	/// \return version information
	const char* getVersion() const;

private:

	/// \~english
	/// \brief constructor function
	CSystem();

	/// \~english
	/// \brief copy constructor function
	CSystem(const CSystem&); 

	/// \~english
	/// \brief assignment function
	CSystem& operator = (const CSystem&);


	/// \~english
	/// \brief destructor function
	~CSystem();
	
	class Impl;
	Impl *m_pImpl;
};

/// @}

GENICAM_NAMESPACE_END

#endif //__DAHUA_GENICAM_CSYSTEM_H__
