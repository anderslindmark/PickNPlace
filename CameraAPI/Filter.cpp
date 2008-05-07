#include "Filter.h"
#include "log.h"

namespace camera 
{

Filter::Filter()
{
	LOG_TRACE("Filter::Filter()");
	m_enabled = true;
}

Filter::~Filter()
{
	LOG_TRACE("Filter::~Filter()");
}

void Filter::setEnabled(bool enabled)
{
	m_enabled = enabled;
}

bool Filter::getEnabled()
{
	return m_enabled;
}

} // namespace camera
