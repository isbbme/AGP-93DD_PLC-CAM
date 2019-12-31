#ifndef __DAHUA_GENICAM_FRAME_H__
#define __DAHUA_GENICAM_FRAME_H__

#include "Defs.h"
#include "Memory/Block.h"
#include "Infra/Vector.h"
#include "Infra/String.h"
#include "PixelType.h"


GENICAM_NAMESPACE_BEGIN

/// \~english 
/// \brief data frame object interface
/// \defgroup data Frame Buffer Operation interface
/// @{

/// \~english
/// \brief Class CFrame frame object interface
class GENICAM_API CFrame : public Memory::CBlock
{
public:	

	enum EPayloadType
	{
		payloadImage = 1,	            ///< \~chinese          \~english Image
		payloadRawdata,					///< \~chinese        \~english Raw Data
		payloadFile,					///< \~chinese          \~english File
		payloadChunkData,				///< \~chinese        \~english Chunk Data
		payloadExtChunkData,			///< \~chinese    \~english Extension Chunk Data
		payloadJpeg,					///< \~chinese      \~english jpeg Data
		payloadDevSpecBase = 0x8000,    ///< \~chinese      \~english Device specific payload type
		payloadUndefined				///< \~chinese 		\~english Undefined
	};
	

	/// \~english
	/// brief Empty Constructor function
	CFrame();
	

	/// \~english
	/// brief  Frame object constructor function
	/// \param [in] other raw data object used to contruct frame
	explicit CFrame(Memory::CBlock const& other);
	

	/// \~english
	/// \brief frame deep clone interface
	/// \return new frame object
	CFrame clone();
	


	/// \~english
	/// \brief It is required to call this interface to release the image related memory when it is not needed externally
	/// \return none	
	void reset();
	

	/// brief check frame valid or not
	/// \retval < 0 frame invalid
	/// \retval 0   frame valid	
	bool valid() const;
	

	/// \~english
	/// \brief Get the starting address of memory of this image data
	/// \return Return the starting address of memory of this image data  	
	const void * getImage() const;
			

	/// \~english
	/// \brief Get status of data frame
	/// \return Return status of data frame
	uint32_t getFrameStatus() const;


	/// \~english
	/// \brief get the width of image
	/// \return the width of image, return 0 when failed	
	uint32_t getImageWidth() const;

	/// \~english 
	/// \brief get the height of image
	/// \return the height of image, return 0 when failed	
	uint32_t getImageHeight() const;
			

	/// \~english
	/// \brief get the size of image
	/// \return the size of image, return 0 when failed	
	uint32_t getImageSize() const;
			

	/// \~english
	/// \brief get image pixel format
	/// \return image pixel format	
	EPixelType getImagePixelFormat() const;
			 

	/// \~english
	/// \brief get timestamp of image
	/// return image time stamp, return 0 when failed	
	uint64_t getImageTimeStamp() const;
			 

	/// \~english
	/// \brief get the block ID of image
	/// \return the image's block ID, return 0 when failed 	
	uint64_t getBlockId() const;
			

	/// \~english
	/// \brief get pay load type of current frame
	/// \param [out] payloadTypes Current frame data type set
	/// \retval false failure
	/// \retval true  success	
	bool getPayLoadTypes(Infra::TVector<EPayloadType>& payloadTypes) const;
			

	/// \~english
	/// \brief get the number of chunk in buffer
	/// \return the number of chunk	
	uint32_t getChunkCount() const;
	

	/// \~english
	/// \brief get chunk data
	/// \param [in] aIndex index ID
	/// \param [out] aID ChunkID
	/// \param [out] paramNames Corresponding property name of chunk data 
	/// \return success or fail	
	bool getChunkDataByIndex(uint32_t aIndex, uint32_t &aID, Infra::TVector<Infra::CString>& paramNames) const;


    /// \~english
    /// \brief get image paddingX
    /// \return paddingX	
    uint32_t getImagePadddingX() const;



    /// \~english
    /// \brief get image paddingY
    /// \return paddingY		
    uint32_t getImagePadddingY() const;
};

/// @}

GENICAM_NAMESPACE_END

#endif //__DAHUA_GENICAM_FRAME_H__

