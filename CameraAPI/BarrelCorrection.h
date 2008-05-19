#ifndef __BARRELCORRECTION_H__
#define __BARRELCORRECTION_H__

#include "Filter.h"

namespace camera 
{

///
/// \brief This filter corrects a barrel distortion. The correction of a m*n image is done in O(m*n) time.
///
class BarrelCorrection : public Filter
{
	public:
		///
		/// \brief Create a new barrel correction filter.
		/// \see BarrelCorrection::setDistortedCoordinates()
		///
		BarrelCorrection(unsigned int distortedX[8], unsigned int distordetY[8]);
		virtual ~BarrelCorrection();
		
		virtual Image *apply(Image *image);
		
		///
		/// \brief Set the coordinates that represents a rectangle on the distorted image. The following order of the coordinates is used: top-left, top-center, top-right, middle-left, middle-right, bottom-left, bottom-center, bottom-right
		/// \param distortedX The x coordinates of the distorted rectangle
		/// \param distortedY The y coordinates of the distorted rectangle
		///
		void setDistortedCoordinates(unsigned int distortedX[8], unsigned int distordetY[8]);
		
		///
		/// \brief Set the size of the output image.
		///
		void setOutputSize(unsigned int width, unsigned int height);
		
	private:
		void calculatePixelMapping();
		void solveLinearEquation(float M[8][9]);
		
		unsigned int m_distortedX[8];
		unsigned int m_distortedY[8];
		unsigned int m_outputWidth;
		unsigned int m_outputHeight;
		unsigned int *m_pixelMapping;
		Image *m_correctedImage;
};


typedef std::vector<Filter *> FilterList;

} // namespace camera

#endif
