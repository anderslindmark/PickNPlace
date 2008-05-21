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
		/// \see BarrelCorrection::setDistortedRectangle()
		///
		BarrelCorrection(int distortedRectangle[8][2]);
		virtual ~BarrelCorrection();
		
		virtual Image *apply(Image *image);
		
		///
		/// \brief Set the coordinates that represents a rectangle on the distorted image. This distorted rectangle will be the border of the corrected image. The coordinates is in the following order: Each of the eight coordinates has first the x then the y value. The eight coordinates are ordered top-left, top-center, top-right, middle-left, middle-right, bottom-left, bottom-center, bottom-right.
		/// \param distortedRectangle The x and y coordinates of each corner and the center of each edge on the distorted rectangle.
		///
		void setDistortedRectangle(int distortedRectangle[8][2]);
		
		///
		/// \brief Set the size of the output image. If no output size is set or if the output size is (0, 0) the next image the filter is applied to will decide the output size.
		///
		void setOutputSize(int width, int height);
		
	private:
		void calculatePixelMapping();
		void solveLinearEquation(float M[8][9]);
		
		int m_distortedRectangle[8][2];
		int m_outputWidth;
		int m_outputHeight;
		int *m_pixelMapping;
		int m_pixelMappingMin;
		int m_pixelMappingMax;
		Image *m_correctedImage;
};

} // namespace camera

#endif
