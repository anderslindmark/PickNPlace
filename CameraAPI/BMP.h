#include "Image.h"

namespace camera 
{
namespace util 
{

Image *loadBMP(const char *filename);
void saveBMP(const char *filename, const Image *image);

} // namespace util
} // namespace camera