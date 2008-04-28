#ifndef __FILTER_H__
#define __FILTER_H__

#include <vector>
#include "Image.h"

namespace camera 
{

class Filter 
{
	public:
		Filter();
		virtual ~Filter();
		
		bool enabled;
		virtual Image *apply(Image *image) = 0;
};


typedef std::vector<Filter *> FilterList;

} // namespace camera

#endif
