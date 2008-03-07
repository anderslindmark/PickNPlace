#ifndef __IMAGE_H__
#define __IMAGE_H__

namespace camera {

typedef unsigned char ImageBuffer;

class Image {
	public:
		static enum Format {
			FORMAT_Y8,
			FORMAT_RGB32,
			FORMAT_RGB24,
			FORMAT_RGB16,
			FORMAT_RGB15,
			FORMAT_UNKNOWN = 1000
		};
		
		Image(int width, int height, Format format);
		Image(int width, int height, int bytesPerPixel);
		~Image();
		
		ImageBuffer *getBufferAddress() const;
		int getBufferSize() const;
		Format getFormat() const;
		int getWidth() const;
		int getHeight() const;
		int getBytesPerPixel() const;
		static int formatBytesPerPixel(Format format);
		
	private:
		void init(int width, int height, Format format, int bytesPerPixel);
		int _width;
		int _height;
		int _bytesPerPixel;
		Format _format;
		int _bufferSize;
		ImageBuffer *_buffer;
};

} // namespace camera

#endif
