#ifndef __BARRELCORRECTION_H__
#define __BARRELCORRECTION_H__

#include "Filter.h"

namespace camera 
{

class BarrelCorrection : public Filter
{
	public:
		BarrelCorrection(int distortedX[8], int distordetY[8]);
		virtual ~BarrelCorrection();
		
		virtual Image *apply(Image *image) = 0;
		
		void setDistortedCoordinates(int distortedX[8], int distordetY[8]);
		void setOutputSize(int width, int height);
		
	private:
		void calculatePixelMapping();
		void solveLinearEquation(float M[8][9]);
		
		int m_distortedX[8];
		int m_distortedY[8];
		int m_outputWidth;
		int m_outputHeight;
		int *m_pixelMapping;
		Image *m_correctedImage;
};


typedef std::vector<Filter *> FilterList;

} // namespace camera

#endif
