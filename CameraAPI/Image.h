#ifndef __IMAGE_H__
#define __IMAGE_H__

namespace camera
{

typedef unsigned char ImageBuffer;

class Image
{
	public:
		static enum Format
		{
			FORMAT_Y8,
			FORMAT_RGB32,
			FORMAT_RGB24,
			FORMAT_RGB16,
			FORMAT_RGB15,
			FORMAT_UNKNOWN = 1000
		};
		static int formatBytesPerPixel(Format format);
		
		Image(int width, int height, Format format);
		Image(int width, int height, int bytesPerPixel);
		~Image();
		
		void reallocate(int width, int height);
		void reallocate(int width, int height, Format format);
		void reallocate(int width, int height, int bytesPerPixel);
		
		ImageBuffer *getBufferAddress() const;
		int getBufferSize() const;
		Format getFormat() const;
		int getWidth() const;
		int getHeight() const;
		int getBytesPerPixel() const;
		
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
