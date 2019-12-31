#ifndef __DAHUA_GENICAM_IEVENTSUBSCRIBE_H__
#define __DAHUA_GENICAM_IEVENTSUBSCRIBE_H__

#include "Defs.h"
#include "Memory/SharedPtr.h"
#include "Infra/Function.h"
#include "Infra/Vector.h"
#include "Infra/String.h"

GENICAM_NAMESPACE_BEGIN

/// \~english
/// \brief Struct connection event parameters encapsulation
struct SConnectArg
{
	enum EVType
	{
		offLine,       ///< \~english device offline notification
		onLine       ///< \~english device online notification
	};
	EVType m_event;  		  ///< \~english event type
	uint32_t reserve[15];      ///< \~english reserved field
};


/// \brief Struct 
/// \~english
/// \brief Struct updating parameters event encapsulation
struct SParamUpdataArg
{
	bool isPoll; 					    ///< \~english update periodically or not. 1 : update periodically, 0 : not update periodically
	uint32_t reserve[10];		                    ///< \~english reserved field
	Infra::TVector<Infra::CString>  paramNames;  ///< \~english array of parameter's name which need to be updated. the maximum number of parameters is 1000. and the max length of strings of each parameter is 255.
};


/// \~english
/// enumeration:stream event status
enum EEventStatus
{
	streamEventNormal = 1,    		    ///< \~english normal stream event
	streamEventLostFrame = 2, 		    ///< \~english lost frame event
	streamEventLostPacket = 3, 		    ///< \~english lost packet event
	streamEventImageError = 4,     		///< \~english error image event
	streamEventStreamChannelError       		///< \~english stream channel error event
};

/// \~chinese
/// \brief Struct 
/// \~english
/// \brief Struct stream event parameters encapsulation
struct SStreamArg
{
	uint32_t     channel;                     ///< \~english stream channel no.
	uint64_t     blockID;                 ///< \~english block ID of stream data
	uint64_t     timestamp;                      ///< \~english event timestamp
	EEventStatus eStreamEventStatus;      ///< \~english stream event status code
	uint32_t	 status;			     ///< \~english status error code
	uint32_t reserve[9];			          ///< \~english reserved field
};

/// \~english
/// message channel event id list
#define MSG_EVENT_ID_EXPOSURE_END			0x9001
#define MSG_EVENT_ID_FRAME_TRIGGER			0x9002
#define MSG_EVENT_ID_FRAME_START			0x9003
#define MSG_EVENT_ID_ACQ_START				0x9004
#define MSG_EVENT_ID_ACQ_TRIGGER			0x9005
#define MSG_EVENT_ID_DATA_READ_OUT			0x9006

/// \~english
/// \brief Struct message channel event parameters encapsulation
struct SMsgChannelArg
{
	uint16_t  eventID;         // 			///< \~english event id
	uint16_t  channelID;       // 		///< \~english channel id
	uint64_t  blockID;		   /// 		///< \~english block ID of stream data
	uint64_t  timeStamp;       /// 			///< \~english event timestamp
	uint32_t    reserve[8];   ///          ///< \~english reserved field
	Infra::TVector<Infra::CString>  paramNames;    ///< \~english array of parameter's name which is related. the maximum number of parameters is 1000. and the max length of strings of each parameter is 255.
};

/// \~english
/// \brief call back function declaration of camera connection status event 
typedef Infra::TFunction1<void, const SConnectArg&> ConnectArgProc;

/// \~english
/// \brief call back function declaration of camera connection status event 
typedef Infra::TFunction2<void, const SConnectArg&, void*> ConnectArgProcEx;

/// \~english
/// \brief call back function declaration of camera parameter update event 
typedef Infra::TFunction1<void, const SParamUpdataArg&> ParamUpdataProc;


/// \~english
/// \brief call back function declaration of camera parameter update event 
typedef Infra::TFunction2<void, const SParamUpdataArg&, void*> ParamUpdataProcEx;

/// \~english
/// \brief call back function declaration of stream event 
typedef Infra::TFunction1<void, const SStreamArg&> StreamArgProc;

/// \~english
/// \brief call back function declaration of stream event 
typedef Infra::TFunction2<void, const SStreamArg&, void*> StreamArgProcEx;


/// \~english
/// \brief call back function declaration of message channel event 
typedef Infra::TFunction1<void, const SMsgChannelArg&> MsgChannelProc;


/// \~english
/// \brief call back function declaration of message channel event 
typedef Infra::TFunction2<void, const SMsgChannelArg&, void*> MsgChannelProcEx;


/// \~english
/// \brief event register callback function interface class
/// \defgroup Event Event Notification subscribe and unsubscribe interface
/// @{

/// \~english
/// \brief Class IEventSubscribe Event subscribe callback object interface class,including device status events, stream channel events and parameter update events

class GENICAM_API IEventSubscribe
{
public:

	/// \~english
	/// \brief destructor	
	virtual ~IEventSubscribe(){}

public:

	/// \~english
	/// \brief  regist call back function of camera connection status event. only one call back function is supported.
	/// \param [in] proc  call back function of camera connection status event
	/// \return the result of registration ( Success or fail )
	virtual bool subscribeConnectArgs(ConnectArgProc const& proc) = 0;

	/// \~english
	/// \brief  unregister call back function of camera connection status event.
	/// \param [in] proc  Unregister call back function of camera connection status event
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeConnectArgs(ConnectArgProc const& proc) = 0;


	/// \~english
	/// \brief  regist call back function of parameter update event. only one call back function is supported.
	/// \param [in] proc  call back function of parameter update event
	/// \return the result of registration	( Success or fail )
	virtual bool subscribeParamUpdate(ParamUpdataProc const& proc) = 0;

	/// \~english
	/// \brief  unregister call back function of parameter update event.
	/// \param [in] proc  unregister call back function of parameter update event
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeParamUpdate(ParamUpdataProc const& proc) = 0;

	/// \~english
	/// \brief  register call back function of stream channel event. only one call back function is supported.
	/// \param [in] proc  register call back function of stream channel event
	/// \return the result of registration ( Success or fail )	
	virtual bool subscribeStreamArg(StreamArgProc const& proc) = 0;


	/// \~english
	/// \brief  unregister call back function of stream channel event.
	/// \param [in] proc  unregister call back function of tream channel event
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeStreamArg(StreamArgProc const& proc) = 0;

    /// \~english
    /// \brief  regist call back function of camera connection status event. only one call back function is supported.
    /// \param [in] proc  call back function of camera connection status event
    /// \param [in] pUser  user data
    /// \return the result of registration ( Success or fail )
    virtual bool subscribeConnectArgsEx(ConnectArgProcEx const& proc, void* pUser) = 0;

    /// \~english
    /// \brief  unregister call back function of camera connection status event.
    /// \param [in] proc  Unregister call back function of camera connection status event
    /// \param [in] pUser  user data
    /// \return the result of unregistration ( Success or fail )	
    virtual bool unsubscribeConnectArgsEx(ConnectArgProcEx const& proc, void* pUser) = 0;

    /// \~english
    /// \brief  regist call back function of parameter update event. only one call back function is supported.
    /// \param [in] proc  call back function of parameter update event
    /// \param [in] pUser  user data
    /// \return the result of registration	( Success or fail )
    virtual bool subscribeParamUpdateEx(ParamUpdataProcEx const& proc, void* pUser) = 0;


    /// \~english
    /// \brief  unregister call back function of parameter update event.
    /// \param [in] proc  unregister call back function of parameter update event
    /// \param [in] pUser  user data
    /// \return the result of unregistration ( Success or fail )
    virtual bool unsubscribeParamUpdateEx(ParamUpdataProcEx const& proc, void* pUser) = 0;

    /// \~english
    /// \brief  register call back function of stream channel event. only one call back function is supported.
    /// \param [in] proc  register call back function of stream channel event
    /// \param [in] pUser  user data
    /// \return the result of registration ( Success or fail )	
    virtual bool subscribeStreamArgEx(StreamArgProcEx const& proc, void* pUser) = 0;

    /// \~english
    /// \brief  unregister call back function of stream channel event.
    /// \param [in] proc  unregister call back function of tream channel event
    /// \param [in] pUser  user data
    /// \return the result of unregistration ( Success or fail )
    virtual bool unsubscribeStreamArgEx(StreamArgProcEx const& proc, void* pUser) = 0;

	/// \~english
	/// \brief  register call back function of message channel event. only one call back function is supported.
	/// \param [in] proc  register call back function of message channel event
	/// \return the result of registration ( Success or fail )	
	virtual bool subscribeMsgChannel(MsgChannelProc const& proc) = 0;


	/// \~english
	/// \brief  unregister call back function of message channel event.
	/// \param [in] proc  unregister call back function of message channel event
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeMsgChannel(MsgChannelProc const& proc) = 0;

	/// \~english
	/// \brief  register call back function of message channel event. only one call back function is supported.
	/// \param [in] proc  register call back function of message channel event
	/// \param [in] pUser  user data
	/// \return the result of registration ( Success or fail )	
	virtual bool subscribeMsgChannelEx(MsgChannelProcEx const& proc, void* pUser) = 0;

	/// \~english
	/// \brief  unregister call back function of message channel event.
	/// \param [in] proc  unregister call back function of message channel event
	/// \param [in] pUser  user data
	/// \return the result of unregistration ( Success or fail )	
	virtual bool unsubscribeMsgChannelEx(MsgChannelProcEx const& proc, void* pUser) = 0;
};

typedef Memory::TSharedPtr<IEventSubscribe> IEventSubscribePtr;


GENICAM_NAMESPACE_END
#endif //__DAHUA_GENICAM_IEVENTSUBSCRIBE_H__