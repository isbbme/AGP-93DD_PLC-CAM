#ifndef __DAHUA_GENICAM_ISPCONTROL_H__
#define __DAHUA_GENICAM_ISPCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IISPControl;

typedef Memory::TSharedPtr<IISPControl> IISPControlPtr;

/// \ingroup config
/// @{

/// \~english
/// \brief Class IISPControl ISPControl's property operation class
class GENICAM_API IISPControl
{
public:
	virtual ~IISPControl() {}

public:

	/// \~english
	/// \brief get Brightness property operation object, set brightness
	/// \return return property operation object	
	virtual CIntNode brightness() = 0;

	/// \~english
	/// \brief get Sharpness property operation object, set sharpness
	/// \return return property operation object	
	virtual CIntNode sharpness() = 0;

	/// \~english
	/// \brief get SharpnessAuto property operation object, set whether activate auto sharpness or not
	/// \return return property operation object		
	virtual CBoolNode sharpnessAuto() = 0;

	/// \~english 
	/// \brief get SharpnessEnable property operation object, set whether enable sharpness or not
	/// \return property operation object
	virtual CEnumNode sharpnessEnable() = 0;

	/// \~english 
	/// \brief get Contrast property operation object, set contrast
	/// \return property operation object	
	virtual CIntNode contrast() = 0;

	/// \~english 
	/// \brief get Hue property operation object, set hue
	/// \return property operation object		
	virtual CIntNode hue() = 0;


	/// \~english 
	/// \brief get Saturation property operation object, set saturation
	/// \return property operation object		
	virtual CIntNode saturation() = 0;


	/// \~english 
	/// \brief get DigitalShift property operation object, set DigitalShif
	/// \return property operation object	
	virtual CIntNode digitalshift() = 0;


	/// \~english 
	/// \brief get Denoising property operation object, set Denoising
	/// \return property operation object	
	virtual CIntNode denoising() = 0;

	/// \~english 
	/// \brief get DenoisingMode property operation object, set DenoisingMode
	/// \return property operation object		
	virtual CEnumNode denoisingMode() = 0;

	/// \~english 
	/// \brief get ContrastMode property operation object, set ContrastMode
	/// \return property operation object	
	virtual CEnumNode contrastMode() = 0;


	/// \~english 
	/// \brief get ContrastThreshold property operation object, set ContrastThreshold
	/// \return property operation object	
	virtual CIntNode contrastThreshold() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_ISPCONTROL_H__
