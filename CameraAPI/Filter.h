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
		
		///
		/// \brief Set if this filter is enabled or not.
		/// \param enabled true if the filter is enabled and false if it's not.
		///
		void setEnabled(bool enabled);
		
		///
		/// \brief Check if the filter is enabled of not.
		///
		bool getEnabled();
		
		///
		/// \brief Apply the filter.
		/// \param image The image to apply the filter to
		/// \return The resulting image. This can be the same as the input image if the filter modifies the input image directly.
		///
		virtual Image *apply(Image *image) = 0;
		
	private:
		bool m_enabled;
};


typedef std::vector<Filter *> FilterList;

} // namespace camera

#endif
