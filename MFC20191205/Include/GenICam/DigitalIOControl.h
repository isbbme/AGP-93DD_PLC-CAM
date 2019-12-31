#ifndef __DAHUA_GENICAM_DIGITALIOCONTROL_H__
#define __DAHUA_GENICAM_DIGITALIOCONTROL_H__

#include "Defs.h"
#include "GenICam/ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IDigitalIOControl;

typedef Memory::TSharedPtr<IDigitalIOControl> IDigitalIOControlPtr;

/// \ingroup config


/// \~english
/// \brief Class IDigitalIOControl DigitalIOControl's property operation class

class GENICAM_API IDigitalIOControl
{
public:

	/// \~english
	/// \brief destructor
    virtual ~IDigitalIOControl() {}

public:

	/// \~english
	/// \brief get LineSelector's property operation object which can be read and written 
	/// \return property operation object
    virtual CEnumNode lineSelector() = 0;


	/// \~english
	/// \brief get LineDebouncerTimeAbs's property operation object which can be read and written 
	/// \return roperty operation object
	virtual CDoubleNode lineDebouncerTimeAbs() = 0;


	/// \~english
	/// \brief get LineSource's property operation object which can be read and written  
	/// \return property operation object	
	virtual CEnumNode LineSource() = 0;


	/// \~english
	/// \brief get UserOutputSelector's property operation object which can be read and written  
	/// \return property operation object	
	virtual CEnumNode userOutputSelector() = 0;

	/// \~english
	/// \brief get UserOutputValue's property operation object which can be read and written 
	/// \return property operation object	
	virtual CBoolNode userOutputValue() = 0;

};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_DIGITALIOCONTROL_H__
