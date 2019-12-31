#ifndef __DAHUA_GENICAM_GENERAL_PARAMETERS_H__
#define __DAHUA_GENICAM_GENERAL_PARAMETERS_H__

#include "Defs.h"
#include "Camera.h"
#include "Infra/CString.h"

GENICAM_NAMESPACE_BEGIN

class CIntNode;
class CDoubleNode;
class CEnumNode;
class CBoolNode;
class CCmdNode;
class CStringNode;

typedef Memory::TSharedPtr<CIntNode> CIntNodePtr;
typedef Memory::TSharedPtr<CDoubleNode> CDoubleNodePtr;
typedef Memory::TSharedPtr<CEnumNode> CEnumNodePtr;
typedef Memory::TSharedPtr<CBoolNode> CBoolNodePtr;
typedef Memory::TSharedPtr<CCmdNode> CCmdNodePtr;
typedef Memory::TSharedPtr<CStringNode> CStringNodePtr;


/// \~english
/// \brief common parameter object interface
/// \defgroup config Property Operation interface
/// @{

/// \~english
/// \brief Class CNodeBase property operation base class interface
class GENICAM_API CNodeBase
{
public:
	virtual ~CNodeBase();

public:

	/// \~english
	/// \brief check the property is available or not
	/// \return available:true, not available:false
	bool isAvailable() const;


	/// \~english
	/// \brief check the property is readable or not
	/// \return readable:true, not readable:false
	bool isReadable() const;


	/// \~english
	/// \brief check the property is writeable or not
	/// \return writeable:true, not writeable:false
	bool isWriteable() const;

	/// \~english
	/// \brief check the property is streamable or not
	/// \return streamable:true, not streamable:false
	bool isStreamable() const;


	/// \~english
	/// \brief check the property is valid or not
	/// \return valid:true, invalid:false
	bool isValid() const;

protected:
	CNodeBase(const ICameraPtr& ptrCamera, const char* pParamName);
	CNodeBase(const CNodeBase& other);
	CNodeBase& operator= (const CNodeBase& other);

protected:
	class	Impl;
	Impl*	m_pImpl;
};


/// \~english
/// \brief Class IIntNode integer property operation class
class GENICAM_API CIntNode : public CNodeBase
{
public:
	CIntNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CIntNode();

public:

	/// \~english
	/// \brief get property's value
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValue(int64_t& val) const;


	/// \~english
	/// \brief set the property's value
	/// \param [in] val the value to be set for this property
	/// \return success:true, fail:false
	bool setValue(int64_t val);


	/// \~english
	/// \brief get the property's minimum value that can be set
	/// \param [out] val the property's minimum value
	/// \return success:true, fail:false
	bool getMinVal(int64_t& val) const;


	/// \~english
	/// \brief get the property's maximum value that can be set
	/// \param [out] val the property's maximum value
	/// \return success:true, fail:false
	bool getMaxVal(int64_t& val) const;


	/// \~english
	/// \brief get property's increment
	/// \param [out] val the property's increment
	/// \return success:true, fail:false
	bool getIncrement(int64_t& val) const;
};


/// \~english
/// \brief Class IDoubleNode float property operation class
class GENICAM_API CDoubleNode : public CNodeBase
{
public:
	CDoubleNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CDoubleNode();

public:

	/// \~english
	/// \brief get property's value
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValue(double& val) const;


	/// \~english
	/// \brief set property's value
	/// \param [in] val the value to be set for this property
	/// \return success:true, fail:false
	bool setValue(double val);


	/// \~english
	/// \brief get the property's minimum value that can be set
	/// \param [out] val the property's minimum value
	/// \return success:true, fail:false
	bool getMinVal(double& val) const;


	/// \~english
	/// \brief get the property's maximum value that can be set
	/// \param [out] val the property's maximum value
	/// \return success:true, fail:false
	bool getMaxVal(double& val) const;
};


/// \~english
/// \brief  Class IEnumNode EnumNode property operation class
class GENICAM_API CEnumNode : public CNodeBase
{
public:
	CEnumNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CEnumNode();

public:

	/// \~english
	/// \brief get symbol value of enum property
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValueSymbol(Infra::CString& val) const;


	/// \~english
	/// \brief set symbol value of enum property 
	/// \param [in] strSymbolName the value waiting to be set for this property
	/// \return success:true, fail:false
	bool setValueBySymbol(const Infra::CString& strSymbolName);


	/// \~english
	/// \brief Get the list of Enum property symbol value which can be set
	/// \return Return the list of Enum property symbol value which can be set now
	Infra::TVector<Infra::CString> getEnumSymbolList() const;


	/// \~english
	/// \brief set symbol value of enum property 
	/// \param [in] val the value waiting to be set for this property
	/// \return success:true, fail:false
	bool setValue(uint64_t val);


	/// \~english
	/// \brief get symbol value of enum property
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValue(uint64_t &val) const;


	/// \~english
	/// \brief get symbol value of enum property by symbol string
	/// \param [in] strSymbolName the property's string
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValueBySymbol(Infra::CString strSymbolName, uint64_t &val) const;


	/// \~english
	/// \brief get symbol of enum property by value
	/// \param [in]  val the property's value
	/// \param [out] strSymbolName the property's string
	/// \return success:true, fail:false
	bool getSymbolByValue(uint64_t val, Infra::CString &strSymbolName) const;
};

/// \~english
/// \brief Class IBoolNode BoolNode property operation class
class GENICAM_API CBoolNode : public CNodeBase
{
public:
	CBoolNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CBoolNode();

public:

	/// \~english
	/// \brief get property's value
	/// \param [out] val the property's value
	/// \return success:true, fail:false
	bool getValue(bool& val) const;


	/// \~english
	/// \brief set property's value
	/// \param [in] val the value to be set for this property
	/// \return success:true, fail:false
	bool setValue(bool val);
};


/// \~english
/// \brief Class ICmdNode CmdNode property operation class
class GENICAM_API CCmdNode : public CNodeBase
{
public:
	CCmdNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CCmdNode();

public:

	/// \~english
	/// \brief execute command property
	/// \return success:true, fail:false
	bool execute();
};


/// \~english
/// \brief Class IStringNode StringNode property operation class
class GENICAM_API CStringNode : public CNodeBase
{
public:
	CStringNode(const ICameraPtr& ptrCamera, const char* pParamName);
	~CStringNode();

public:

	/// \~english
	/// \brief get property's value
	/// \param [out] outStr the property's value
	/// \return success:true, fail:false
	bool getValue(Infra::CString &outStr);


	/// \~english
	/// \brief set the property's value
	/// \param [in] inStr the value to be set for this property
	/// \return success:true, fail:false
	bool setValue(const Infra::CString &inStr);
};

/// @}
GENICAM_NAMESPACE_END

#endif // __DAHUA_GENICAM_GENERAL_PARAMETERS_H__
