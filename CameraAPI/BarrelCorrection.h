#ifndef __BARRELCORRECTION_H__
#define __BARRELCORRECTION_H__

#include "Filter.h"

namespace camera 
{

class BarrelCorrection : public Filter
{
	public:
		BarrelCorrection(float distortedX[8], float distordetY[8]);
		virtual ~BarrelCorrection();
		
		virtual Image *apply(Image *image);
		
		void setDistortedCoordinates(float distortedX[8], float distordetY[8]);
		void setOutputSize(int width, int height);
		
	private:
		void calculatePixelMapping();
		void solveLinearEquation(float M[8][9]);
		
		float m_distortedX[8];
		float m_distortedY[8];
		int m_outputWidth;
		int m_outputHeight;
		int *m_pixelMapping;
		Image *m_correctedImage;
};


typedef std::vector<Filter *> FilterList;

} // namespace camera

#endif
