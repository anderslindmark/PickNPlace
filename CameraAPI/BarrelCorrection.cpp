#include "BarrelCorrection.h"
#include "log.h"

#define ABS(x) (x < 0 ? -x : x)

namespace camera 
{

BarrelCorrection::BarrelCorrection(float distortedX[8], float distortedY[8])
{
	LOG_TRACE("BarrelCorrection::BarrelCorrection()");
	
	m_outputWidth = 0;
	m_outputHeight = 0;
	m_pixelMapping = NULL;
	m_correctedImage = NULL;
	
	setDistortedCoordinates(distortedX, distortedY);
}

BarrelCorrection::~BarrelCorrection()
{
	LOG_TRACE("BarrelCorrection::~BarrelCorrection()");
}

Image *BarrelCorrection::apply(Image *image)
{
	LOG_TRACE("BarrelCorrection::apply()");
	
	if(m_outputWidth <= 0 || m_outputHeight <= 0)
	{
		setOutputSize(image->getWidth(), image->getHeight());
	}
	
	if(m_correctedImage == NULL || m_pixelMapping == NULL)
		return image;
	
	if(image->getFormat() != Image::FORMAT_RGB32)
	{
		LOG_ERROR("");
		return image;
	}
	
	int numPixels                   = m_correctedImage->getWidth() * m_correctedImage->getHeight();
	int *mapping                    = m_pixelMapping;
	ImageBuffer *cBufferAddr		= m_correctedImage->getBufferAddress();
	ImageBuffer *dBufferBaseAddr	= image->getBufferAddress();
	ImageBuffer *dBufferAddr		= NULL;
	
	for(int i = 0; i < numPixels; i++)
	{
		// Calculate which pixel to use from the distorted image based on the pixel mapping
		dBufferAddr = dBufferBaseAddr + (*mapping) * 4; // 4 bytes per pixel (BGRX)
		
		// Copy the pixel color from the distorted to the corrected image.
		*(cBufferAddr++) = *(dBufferAddr++); // B (Blue)
		*(cBufferAddr++) = *(dBufferAddr++); // G (Green)
		*(cBufferAddr++) = *(dBufferAddr++); // R (Red)
		*(cBufferAddr++) = *(dBufferAddr++); // X (Not used)
		
		mapping++;
	}
	
	return m_correctedImage;
}

void BarrelCorrection::setDistortedCoordinates(float distortedX[8], float distortedY[8])
{	
	LOG_TRACE("BarrelCorrection::setDistortedCoordinates()");
	
	memcpy(m_distortedX, distortedX, sizeof(float) * 8);
	memcpy(m_distortedY, distortedY, sizeof(float) * 8);
	/*for(int i = 0; i < 8; i++)
	{
		m_distortedX[i] = distortedX[i];
		m_distortedY[i] = distordetY[i];
	}*/
	
	calculatePixelMapping();
}

void BarrelCorrection::setOutputSize(int width, int height)
{
	LOG_TRACE("BarrelCorrection::setOutputSize()");
	// TODO: Need mutex lock so the corrected image or pixel mapping array isn't used in another thread when they are reallocated
	
	if(m_outputWidth == width && m_outputHeight == height)
		return;
	
	m_outputWidth = width;
	m_outputHeight = height;
	
	if(m_outputWidth <= 0 || m_outputHeight <= 0)
		return;
	
	// TODO: Check if reallocateing corrected image and pixel mapping array takes to much time.
	
	// Reallocate the corrected image
	if(m_correctedImage != NULL)
	{
		delete m_correctedImage;
	}
	m_correctedImage = new Image(m_outputWidth, m_outputHeight, Image::FORMAT_RGB32);
	
	// Reallocate pixel mapping array
	if(m_pixelMapping != NULL)
	{
		delete m_pixelMapping;
	}
	m_pixelMapping = new int[m_outputWidth * m_outputHeight];
	
	calculatePixelMapping();
}


void BarrelCorrection::calculatePixelMapping()
{
	LOG_TRACE("BarrelCorrection::calculatePixelMapping()");
	
	if(m_outputWidth <= 0 || m_outputHeight <= 0)
		return;
	
	int correctedX[8] = {0, m_outputWidth / 2, m_outputWidth - 1, 0, m_outputWidth - 1, 0, m_outputWidth / 2, m_outputWidth - 1};
	int correctedY[8] = {0, 0, 0, m_outputHeight / 2, m_outputHeight / 2, m_outputHeight - 1, m_outputHeight - 1, m_outputHeight - 1};
	float M[8][9];
	float correctionVectorA[8];
	float correctionVectorB[8];
	
	// Calculate correctionVectorA
	for (int r = 0; r < 8; r++)
	{
		M[r][0] = (float) (correctedY[r]*correctedY[r]*correctedX[r]);
		M[r][1] = (float) (correctedY[r]*correctedX[r]*correctedX[r]);
		M[r][2] = (float) (correctedY[r]*correctedY[r]);
		M[r][3] = (float) (correctedX[r]*correctedX[r]);
		M[r][4] = (float) (correctedY[r]*correctedX[r]);
		M[r][5] = (float) (correctedY[r]);
		M[r][6] = (float) (correctedX[r]);
		M[r][7] = 1;
		M[r][8] = (float) (m_distortedY[r]);
	}
	solveLinearEquation(M);
	for (int r = 0; r < 8; r++)
	{
		correctionVectorA[r] = M[r][8];
	}
	
	// Calculate correctionVectorB
	for (int r = 0; r < 8; r++)
	{
		M[r][0] = (float) (correctedY[r]*correctedY[r]*correctedX[r]);
		M[r][1] = (float) (correctedY[r]*correctedX[r]*correctedX[r]);
		M[r][2] = (float) (correctedY[r]*correctedY[r]);
		M[r][3] = (float) (correctedX[r]*correctedX[r]);
		M[r][4] = (float) (correctedY[r]*correctedX[r]);
		M[r][5] = (float) (correctedY[r]);
		M[r][6] = (float) (correctedX[r]);
		M[r][7] = 1;
		M[r][8] = (float) (m_distortedX[r]);
	}
	solveLinearEquation(M);
	for (int r = 0; r < 8; r++)
	{
		correctionVectorB[r] = M[r][8];
	}
	
	// Calculate pixel mapping
	int dx, dy;
	int *mapping = m_pixelMapping;
	for (int y = 0; y < m_outputHeight; y++)
	{
		for (int x = 0; x < m_outputWidth; x++)
		{
			dy = (int) (correctionVectorA[0]*x*y*y +
				correctionVectorA[1]*x*x*y +
				correctionVectorA[2]*y*y +
				correctionVectorA[3]*x*x +
				correctionVectorA[4]*x*y +
				correctionVectorA[5]*y +
				correctionVectorA[6]*x +
				correctionVectorA[7]);
			
			dx = (int) (correctionVectorB[0]*x*y*y +
				correctionVectorB[1]*x*x*y +
				correctionVectorB[2]*y*y +
				correctionVectorB[3]*x*x +
				correctionVectorB[4]*x*y +
				correctionVectorB[5]*y +
				correctionVectorB[6]*x +
				correctionVectorB[7]);
			
			*mapping = dy * m_outputWidth + dx;
			mapping++;
		}
	}
}

void BarrelCorrection::solveLinearEquation(float M[8][9])
{
	LOG_TRACE("BarrelCorrection::solveLinearEquation()");
	
	int rowCount = 8;
	int columnCount = 9;
	int r, c, r2, c2;
	float tmp;
	
	// Do Gaussian elimination
	r = 0;
	c = 0;
	while(r < rowCount && c < columnCount)
	{
		// Find row with largest number in column c
		int maxR = r;
		for(r2 = r + 1; r2 < rowCount; r2++)
		{
			if(ABS(M[r2][c]) > ABS(M[maxR][c]))
			{
				maxR = r2;
			}
		}
		
		if(M[maxR][c] != 0)
		{
			// Swap row r and maxR
			for(c2 = 0; c2 < columnCount; c2++)
			{
				tmp = M[r][c2];
				M[r][c2] = M[maxR][c2];
				M[maxR][c2] = tmp;
			}
			
			// Devide row r with the value in M[r][c]
			tmp = M[r][c];
			for(c2 = 0; c2 < columnCount; c2++)
			{
				M[r][c2] /= tmp;
			}
			
			// Subtract A[r2][c] * row r from row r2
			for(r2 = r + 1; r2 < rowCount; r2++)
			{
				tmp = M[r2][c];
				for(c2 = 0; c2 < columnCount; c2++)
				{
					M[r2][c2] -= M[r][c2] * tmp;
				}
			}
			// Next row
			r++;
		}
		
		// Next column
		c++;
	}
	
	// Do back-substitution.
	for(r = rowCount - 1; r >= 0; r--)
	{
		for(r2 = 0; r2 < r; r2++)
		{
			tmp = M[r2][r];
			for(c = r; c < columnCount; c++)
			{
				M[r2][c] -= M[r][c] * tmp;
			}
		}
	}
}

} // namespace camera
