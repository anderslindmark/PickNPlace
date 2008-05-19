#include "Image.h"

namespace camera 
{
namespace util 
{

///
/// \brief Not implemented!
///
Image *loadBMP(const char *filename);

///
/// \brief Saves a image to a file in BMP format. The image have to be in the pixelformat RGB32
/// \param filename The path to where the image is to be saved
/// \param image The image (with format RGB32) to be saved.
///
void saveBMP(const char *filename, const Image *image);

} // namespace util
} // namespace camera