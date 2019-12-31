#ifndef __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__
#define __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IImageFormatControl;

typedef Memory::TSharedPtr<IImageFormatControl> IImageFormatControlPtr;

/// \ingroup config
/// @{


/// \~english
/// \brief Class ImageFormatControl's property operation class
class GENICAM_API IImageFormatControl
{
public:

	/// \~english
	/// \brief destructor
	virtual ~IImageFormatControl() {}

public:

	/// \~english
	/// \brief get Height property operation object
	/// \return property's object
	virtual CIntNode height() = 0;


	/// \~english
	/// \brief get Width property operation object
	/// \return property's object	
	virtual CIntNode width() = 0;


	/// \~english
	/// \brief get offsetX property operation object
	/// \return property's object	
	virtual CIntNode offsetX() = 0;


	/// \~english
	/// \brief get OffsetY property operation object
	/// \return property's object	
	virtual CIntNode offsetY() = 0;


	/// \~english
	/// \brief get PixelFormat property operation object
	/// \return property's object	
	virtual CEnumNode pixelFormat() = 0;


	/// \~english
	/// \brief get PixelSize property operation object
	/// \return property's object	
	virtual CEnumNode PixelSize() = 0;


	/// \~english
	/// \brief get ReverseX property operation object
	/// \return property's object	
	virtual CBoolNode reverseX() = 0;


	/// \~english
	/// \brief get ReverseY property operation object
	/// \return property's object		
	virtual CBoolNode reverseY() = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_IMAGEFORMATCONTROL_H__
