#ifndef __BARRELCORRECTION_H__
#define __BARRELCORRECTION_H__

#include "Filter.h"

namespace camera 
{

class BarrelCorrection : public Filter
{
	public:
		BarrelCorrection(unsigned int distortedX[8], unsigned int distordetY[8]);
		virtual ~BarrelCorrection();
		
		virtual Image *apply(Image *image);
		
		void setDistortedCoordinates(unsigned int distortedX[8], unsigned int distordetY[8]);
		void setOutputSize(unsigned int width, unsigned int height);
		
	private:
		void calculatePixelMapping();
		void solveLinearEquation(float M[8][9]);
		
		float m_distortedX[8];
		float m_distortedY[8];
		unsigned int m_outputWidth;
		unsigned int m_outputHeight;
		unsigned int *m_pixelMapping;
		Image *m_correctedImage;
};


typedef std::vector<Filter *> FilterList;

} // namespace camera

#endif
