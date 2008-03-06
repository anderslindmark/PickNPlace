#include "ImageBuffer.h"

namespace camera 
{
namespace util 
{

ImageBuffer *loadBMP(const char *filename);
void saveBMP(const char *filename, const ImageBuffer *image);

} // namespace util
} // namespace camera