#ifndef __DAHUA_GENICAM_ISTREAMSOURCE_H__
#define __DAHUA_GENICAM_ISTREAMSOURCE_H__

#include "Defs.h"
#include "Frame.h"
#include "Infra/Signal.h"

GENICAM_NAMESPACE_BEGIN


class GENICAM_API IStreamSource
{
protected:

	virtual ~IStreamSource(){}
	
public:	

	enum EGrabStrategy
	{
		grabStrartegySequential  = 0,	 	///< \~english The images are processed in the order of their arrival
		grabStrartegyLatestImage = 1,   		///< \~english get the latest image
		grabStrartegyUndefined   				///< \~english undefined
	};


	/// \~english
	/// \brief Callback function declaration of stream: Send out one frame at each time use callback function
	/// CFrame The frame which will be active pushed out during the callback
	typedef Infra::TSignal1<const CFrame&> Signal;
	typedef Signal::Proc Proc;

    /// \~english
    /// \brief Callback function declaration of stream: Send out one frame and user data at each time use callback function
    /// CFrame The frame which will be active pushed out during the callback
    /// void* The user data which will be active pushed out during the callback
    typedef Infra::TSignal2<const CFrame&, const void*> SignalEx;
    typedef SignalEx::Proc ProcEx;

	/// \~english
	/// \brief Start grabbing
	/// \param [in] maxImagesGrabbed Maximum images allowed to grab, once it reaches the limit then stop grabbing; If it is 0, then ignore this parameter and start grabbing continuously
	/// \param [in] strategy Image grabbing strategy; Image grabbing according to the order in buffer queue is default
	/// \return success:true, fail:false
	virtual bool startGrabbing(uint64_t maxImagesGrabbed = 0,EGrabStrategy strategy = grabStrartegySequential) = 0;
					

	/// \~english
	/// \brief Stop grabbing
	/// \return success:true, fail:false
	virtual bool stopGrabbing() = 0;
							

	/// \~english 
	/// \brief Check whether it is grabbing or not
	/// \return grabbing or not grabbing, true means it is grabbing, false means it is not grabbing
	virtual bool isGrabbing() = 0;
				

	/// \~english
	/// \brief get a frame image, and this interface does not support multi-threading
	/// \param [out] frame one frame
	/// \param [in]  timeoutMS The timeout value of getting one image, unit is MS; When the value is INFINITE which means infinite wait
	/// \return success:true, fail:false
	virtual bool getFrame(CFrame& frame, uint32_t timeoutMS = INFINITE) const = 0;
	
		

	/// \~english
	/// \brief Register data frame callback function; This asynchronous frame acquisition mechanism and synchronous frame acquisition mechanism are mutually exclusive, only one method can be choosed between these two in system
	/// \brief only callback one function 
	/// \param [in] proc Data frame callback function; It is advised to not put time-cosuming operation in this function, otherwise it will block follow-up data frames and affect real time performance
	/// \return success:true, fail:false
	virtual bool attachGrabbing(Proc proc) = 0;

	/// \~english
	/// \brief Unregister data frame callback function
	/// \param [in] proc Unregister data frame callback function
	/// \return success:true, fail:false
	virtual bool detachGrabbing(Proc proc) = 0;
	

	/// \~english
	/// \brief Set buffer count, this cannot be set during frame grabbing
	/// \param [in]  nSize the buffer count, max size is 200.
	/// \return success:true, fail:false
    virtual bool setBufferCount(uint32_t nSize) = 0;


    /// \~english
    /// \brief Register data frame callback function(include user defined data); 
    /// \param [in] proc Data frame callback function; It is advised to not put time-cosuming operation in this function, otherwise it will block follow-up data frames and affect real time performance
    /// \param [in] pUser user defined data
    /// \return success:true, fail:false
    virtual bool attachGrabbingEx(ProcEx proc, void* pUser) = 0;


    /// \~english
    /// \brief	Unregister data frame callback function(include user defined data)
    /// \param [in] proc Unregister data frame callback function(the same pUser of the attachGrabbingEx)
    /// \param [in] pUser user defined data
    /// \return success:true, fail:false
    virtual bool detachGrabbingEx(ProcEx proc, void* pUser) = 0;


    /// \~english
    /// \brief	set packet timeout(ms), just for GigE devices
    /// \param [in] the value of timeout
    /// \return success:true, fail:false
    virtual bool setInterPacketTimeout(uint32_t nTimeout) = 0;
};

typedef Memory::TSharedPtr<IStreamSource> IStreamSourcePtr;


GENICAM_NAMESPACE_END

#endif //__DAHUA_GENICAM_ISTREAMSOURCE_H__