#ifndef __DAHUA_GENICAM_DEVICECONTROL_H__
#define __DAHUA_GENICAM_DEVICECONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IDeviceControl;

typedef Memory::TSharedPtr<IDeviceControl> IDeviceControlPtr;

/// \ingroup config
/// @{


/// \~english
/// \brief Class IDeviceControl DeviceControl operation class
class GENICAM_API IDeviceControl
{
public:

	/// \~english
	/// \brief  destruct function 
	virtual ~IDeviceControl() {}

public:

	/// \~english
	/// \brief get DeviceUserID property operation object, it can be written and read.
	/// \return  property operation object
	virtual CStringNode deviceUserID() = 0;

	/// \~english
	/// \brief get DeviceVersion property operation object, it always can be read.
	/// \return  property operation object
	virtual CStringNode DeviceVersion() = 0;
};

/// @}
GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_DEVICECONTROL_H__
