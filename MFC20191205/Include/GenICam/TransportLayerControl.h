#ifndef __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__
#define __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class ITransportLayerControl;

typedef Memory::TSharedPtr<ITransportLayerControl> ITransportLayerControlPtr;

/// \ingroup config
/// @{

/// \~english
/// \brief Class ITransportLayerControl TransportLayerControl property's operation class 
class GENICAM_API ITransportLayerControl
{
public:
	virtual ~ITransportLayerControl() {}

public:

	/// \~english
	/// \brief get GevSCPD property operation object, set packet sending interval 
	/// \return property operation object
	virtual CIntNode gevSCPD() = 0;

	/// \~english
	/// \brief get GevCurrentIPConfigurationDHCP property operation object, check whether activate DHCP or not
	/// \return property operation object
	virtual CBoolNode gevCurrentIPConfigurationDHCP() = 0;


	/// \~english
	/// \brief get GevCurrentIPConfigurationPersistentIP property operation object, check whether activate static IP or not
	/// \return property operation object
	virtual CBoolNode gevCurrentIPConfigurationPersistentIP() = 0;

	/// \~english
	/// \brief get GevPersistentIPAddress property operation object, set static IP
	/// \return property operation object
	virtual CStringNode gevPersistentIPAddress() = 0;

	
	/// \~english
	/// \brief get GevPersistentSubnetMask property operation object, set static IP subnet mask
	/// \return property operation object
	virtual CStringNode gevPersistentSubnetMask() = 0;

	/// \~english
	/// \brief get GevPersistentDefaultGateway property operation object, set static IP gateway
	/// \return property operation object
	virtual CStringNode gevPersistentDefaultGateway() = 0;

	/// \~english
	/// \brief get GevGVCPHeartbeatDisable property operation object, check whether disable GVCP Heartbeat or not
	/// \return property operation object
    virtual CBoolNode gevGVCPHeartbeatDisable() = 0;


	/// \~english
	/// \brief get GevGVSPExtendedIDMode property operation object, check whether disable GVCP ChunkData or not
	/// \return property operation object
	virtual CEnumNode gevGVSPExtendedIDMode() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_TRANSPORTLAYERCONTROL_H__

