#ifndef __IMAGEBUFFER_H__
#define __IMAGEBUFFER_H__

namespace camera 
{

typedef unsigned char Buffer;

class ImageBuffer 
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
		
		ImageBuffer(int width, int height, Format format, int bytesPerPixel = -1);
		~ImageBuffer();
		
		Buffer *getBufferAddress() const;
		int getBufferSize() const;
		Format getFormat() const;
		int getWidth() const;
		int getHeight() const;
		int getBytesPerPixel() const;
		static int formatBytesPerPixel(Format format);
		
	private:
		int _width;
		int _height;
		int _bytesPerPixel;
		Format _format;
		int _bufferSize;
		Buffer *_buffer;
};

} // namespace camera

#endif
