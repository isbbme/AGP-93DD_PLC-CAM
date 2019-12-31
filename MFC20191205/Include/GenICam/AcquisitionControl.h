#ifndef __DAHUA_GENICAM_ACQUISITIONCONTROL_H__
#define __DAHUA_GENICAM_ACQUISITIONCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IAcquisitionControl;

typedef Memory::TSharedPtr<IAcquisitionControl> IAcquisitionControlPtr;

/// \~english
/// \brief GENICAM_AcquisitionControl's property operation class
class GENICAM_API IAcquisitionControl
{
public:

	/// \~english
	/// \brief destructor function
	virtual ~IAcquisitionControl() {}

public:

	/// \~english
	/// \brief get AcquisitionFrameCount property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CIntNode acquisitionFrameCount() = 0;


	/// \~english
	/// \brief get AcquisitionFrameRate property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode acquisitionFrameRate() = 0;


	/// \~english
	/// \brief get AcquisitionFrameRate property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode acquisitionMode() = 0;


	/// \~english
	/// \brief get ExposureAuto property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode exposureAuto() = 0;


	/// \~english
	/// \brief get ExposureMode property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode exposureMode() = 0;


	/// \~english
	/// \brief get ExposureTime property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode exposureTime() = 0;


	/// \~english
	/// \brief get TriggerActivation property's operation object,set TriggerActivation in RisingEdge or FallingEdge
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode triggerActivation() = 0;


	/// \~english
	/// \brief get TriggerDelay property's operation object, set software trigger delay
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode triggerDelay() = 0;


	/// \~english
	/// \brief get TriggerMode property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode triggerMode() = 0;


	/// \~english
	/// \brief get TriggerSelector property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode triggerSelector() = 0;

	/// \~english
	/// \brief get TriggerSource property's operation object, set internal/external trigger
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode triggerSource() = 0;

	/// \~english
	/// \brief get TriggerSoftware property's operation object, execute internal software trigger
	/// \return success:return property operation object, fail:return NULL
	virtual CCmdNode triggerSoftware() = 0;

	/// \~english
	/// \brief get AcquisitionFrameRateEnable property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CBoolNode acquisitionFrameRateEnable() = 0;

	/// \~english
	/// \brief get acquisitionLineRate property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode acquisitionLineRate() = 0;

	/// \~english
	/// \brief get acquisitionLineRateEnable property's operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CBoolNode acquisitionLineRateEnable() = 0;
};


GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_ACQUISITIONCONTROL_H__
