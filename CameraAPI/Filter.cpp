#include "Filter.h"
#include "log.h"

namespace camera 
{

Filter::Filter()
{
	LOG_TRACE("Filter::Filter()");
	enabled = true;
}

Filter::~Filter()
{
	LOG_TRACE("Filter::~Filter()");
}

} // namespace camera
