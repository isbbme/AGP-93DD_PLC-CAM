#ifndef __DAHUA_GENICAM_IGIGEINTERFACE_H__
#define __DAHUA_GENICAM_IGIGEINTERFACE_H__

#include "GenICam/Defs.h"
#include "GenICam/Camera.h"
#include "Infra/String.h"
#include "Memory/SharedPtr.h"

GENICAM_NAMESPACE_BEGIN

class IGigEInterface;
typedef Memory::TSharedPtr<IGigEInterface> IGigEInterfacePtr;


/// \~english
/// \brief camera interface class
/// \defgroup IGigEInterface API for GigEVision interface Only
/// @{

/// \~english
/// \brief Class IGigEInterface interface class used to connect GigE Camera 
class GENICAM_API IGigEInterface
{
protected:
	virtual ~IGigEInterface(){}

public:

	/// \~english
	/// \brief GigE camera object access interface, same cameraPtr is correspond to same GigE camera object
	/// \param [in] cameraPtr GigE camera smart pointer object
	static IGigEInterfacePtr getInstance(const ICameraPtr &cameraPtr);
    

	/// \~english
	/// \brief get NIC description information
	/// \return success:return NIC description information, fail:return empty string
	virtual Infra::CString getDescription() const = 0;

	/// \~english
	/// \brief get NIC's IP Address
	/// \return success:return NIC's IP Address, fail:return empty string
	virtual Infra::CString getIpAddress() const = 0;
	

	/// \~english
	/// \brief get NIC's subnetMask
	/// \return success:return NIC's subnetMask, fail:return empty string
	virtual Infra::CString getSubnetMask() const = 0;

	/// \~english
	/// \brief get NIC's gateway
	/// \return success:return NIC's gateway, fail:return empty string
	virtual Infra::CString getGateway() const = 0;

	/// \~english
	/// \brief get NIC's MacAddress
	/// \return success:return NIC's MacAddress, fail:return empty string
	virtual Infra::CString getMacAddress() const = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif//__DAHUA_GENICAM_IGIGEINTERFACE_H__