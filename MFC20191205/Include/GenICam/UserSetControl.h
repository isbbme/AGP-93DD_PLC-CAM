#ifndef __DAHUA_GENICAM_USERSETCONTROL_H__
#define __DAHUA_GENICAM_USERSETCONTROL_H__

#include "Defs.h"
#include "ParameterNode.h"

GENICAM_NAMESPACE_BEGIN

class IUserSetControl;

typedef Memory::TSharedPtr<IUserSetControl> IUserSetControlPtr;

/// \ingroup config
/// @{

/// \~english
/// \brief IUserSetControl's property operation class
class GENICAM_API IUserSetControl
{
public:
	virtual ~IUserSetControl() {}

public:
	enum EConfigSet
	{
		userSetDefault = 0,		///< \~chinese          ///< \~english camera default set
		userSet1 = 1,			///< \~chinese     ///< \~english camera user set 1 ( Can be read and written )
		userSet2 = 2,			///< \~chinese     ///< \~english camera user set 2 ( Can be read and written )
		userSetInvalid
	};

public:

	/// \~english
	/// \brief restore camera's default configuration
	/// \return success:true, fail:false
	virtual bool restoreDefault() = 0;


	/// \~english
	/// \brief set current camera configuration, these configurations will take effect immediately and load this userset on next time when start camera
	/// \param [in] configSet configuration sets 
	/// \return success:true, fail:false
	virtual bool setCurrentUserSet(EConfigSet configSet = userSet1) = 0;


	/// \~english
	/// \brief save current configuration into certain userset, for example, userSet1
	/// \param [in] configSet save the configuration sets
	/// \return success:true, fail:false
	virtual bool saveUserSet(EConfigSet configSet = userSet1) = 0;


	/// \~english
	/// \brief get current user set
	/// \return return enumeration value of configuration set 
	virtual EConfigSet getCurrentUserSet() = 0;

	/// \~english
	/// \brief get status of current user set and check whether it is available or not
	/// \return available:true, not available:false
	virtual bool isAvailable() const = 0;
};

/// @}

GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_USERSETCONTROL_H__
