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
		
		void setEnabled(bool enabled);
		bool getEnabled();
		
		virtual Image *apply(Image *image) = 0;
		
	private:
		bool m_enabled;
};


typedef std::vector<Filter *> FilterList;

} // namespace camera

#endif
