	#ifndef __DAHUA_GENICAM_ANALOGCONTROL_H__
#define __DAHUA_GENICAM_ANALOGCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IAnalogControl;

typedef Memory::TSharedPtr<IAnalogControl> IAnalogControlPtr;

/// \ingroup config
/// @{


/// \~english
/// \brief GENICAM_AnalogControl's property operation class
class GENICAM_API IAnalogControl
{
public:

	/// \~english
	/// \brief destruct function
	virtual ~IAnalogControl() {}

public:

	/// \~english
	/// \brief get BlackLevelSelector property operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode blackLevelSelector() = 0;


	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode blackLevelAuto() = 0;

	/// \~english
	/// \brief get BlackLevel property operation object, set black level
	/// \return success:return property operation object, fail:return NULL
	virtual CIntNode blackLevel() = 0;

	/// \~english
	/// \brief get GainAuto property operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode gainAuto() = 0;

	/// \~english
	/// \brief get GainRaw operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode gainRaw() = 0;

	/// \~english
	/// \brief get Gamma operation object, set gamma
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode gamma() = 0;

	/// \~english
	/// \brief get BalanceRatioSelector property operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode balanceRatioSelector() = 0;

	/// \~english
	/// \brief get BalanceWhiteAuto property operation object, set auto white balance
	/// \return success:return property operation object, fail:return NULL
	virtual CEnumNode balanceWhiteAuto() = 0;


	/// \~english
	/// \brief get BalanceRatioSelector property operation object
	/// \return success:return property operation object, fail:return NULL
	virtual CDoubleNode balanceRatio() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_ANALOGCONTROL_H__

