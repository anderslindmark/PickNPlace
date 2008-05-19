#ifndef __IMAGE_H__
#define __IMAGE_H__

namespace camera
{

typedef unsigned char ImageBuffer;

class Image
{
	public:
		///
		/// \brief The different pixel format used
		///
		static enum Format
		{
			FORMAT_Y8,                   ///< 8 bit gray scale
			FORMAT_RGB32,                ///< 32 bit color (8 bit red, 8 bit green, 8 bit blue, 8 bit not used)
			FORMAT_RGB24,                ///< 24 bit color (8 bit red, 8 bit green, 8 bit blue)
			FORMAT_RGB16,                ///< 16 bit color (5 bit red, 6 bit green, 5 bit blue)
			FORMAT_RGB15,                ///< 16 bit color (5 bit red, 5 bit green, 5 bit blue)
			FORMAT_UNKNOWN = 1000        ///< Custom pixel format
		};
		
		///
		/// \brief Return the length (in bytes) used for each pixel with the specified pixel format
		/// \param format The pixel format
		///
		static int formatBytesPerPixel(Format format);
		
		///
		/// Create a new image with the specified width, height and format
		/// \param width The with of the image in pixels
		/// \param width The height of the image in pixels
		/// \param format The pixel format of the image
		///
		Image(int width, int height, Format format);
		
		///
		/// Create a new image with the specified width, height and with custom pixel format (Format::FORMAT_UNKNOWN)
		/// \param width The with of the image in pixels
		/// \param width The height of the image in pixels
		/// \param bytesPerPixel The length (in bytes) of each pixel
		///
		Image(int width, int height, int bytesPerPixel);
		
		///
		/// \brief The destructor. Deallocates the memory used by the image
		///
		~Image();
		
		///
		/// \brief Reallocate the image to a new size but keep the current pixel format.
		///
		void reallocate(int width, int height);
		
		///
		/// \brief Reallocate the image to a new size and pixel format.
		///
		void reallocate(int width, int height, Format format);
		
		///
		/// \brief Reallocate the image to a new size. Sets the format to FORMAT_UNKNOWN (Custom pixel format).
		///
		void reallocate(int width, int height, int bytesPerPixel);
		
		
		///
		/// \brief Returns a pointer to the memory containing the image data.
		///
		ImageBuffer *getBufferAddress() const;
		
		///
		/// \brief Returns the size (in bytes) of the image buffer returned by getBufferAddress.
		///
		int getBufferSize() const;
		
		///
		/// \brief Returns the format of the image.
		///
		Format getFormat() const;
		
		///
		/// \brief Returns the width of the image in pixels.
		///
		int getWidth() const;
		
		///
		/// \brief Returns the height of the image in pixels.
		///
		int getHeight() const;
		
		///
		/// \brief Returns the number of bytes each pixel needs. This depends on the pixel format.
		///
		int getBytesPerPixel() const;
		
		///
		/// \brief Custom user data that can be attached to the image.
		///
		void *userData;
		
	private:
		int m_width;
		int m_height;
		int m_bytesPerPixel;
		Format m_format;
		int m_bufferSize;
		ImageBuffer *m_buffer;
};

} // namespace camera

#endif
