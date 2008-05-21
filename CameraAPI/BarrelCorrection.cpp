#include "BarrelCorrection.h"
#include "CameraException.h"
#include "log.h"

#define ABS(x) (((x) < 0) ? -(x) : (x))

namespace camera 
{

BarrelCorrection::BarrelCorrection(int distortedRectangle[8][2])
{
	LOG_TRACE("BarrelCorrection::BarrelCorrection()");
	
	m_outputWidth = 0;
	m_outputHeight = 0;
	m_pixelMapping = NULL;
	m_correctedImage = NULL;

	setDistortedRectangle(distortedRectangle);
}

BarrelCorrection::~BarrelCorrection()
{
	LOG_TRACE("BarrelCorrection::~BarrelCorrection()");

	if(m_correctedImage != NULL)
	{
		delete m_correctedImage;
	}

	if(m_pixelMapping != NULL)
	{
		delete m_pixelMapping;
	}
}

Image *BarrelCorrection::apply(Image *image)
{
	LOG_TRACE("BarrelCorrection::apply()");
	
	if(m_outputWidth == 0 || m_outputHeight == 0)
	{
		setOutputSize(image->getWidth(), image->getHeight());
	}
	
	if(m_correctedImage == NULL || m_pixelMapping == NULL)
	{
		LOG_ERROR("BarrelCorrection::apply(): Output image or pixel mapping array is not set. The filter is not ready to be applied");
		throw CameraException("Output image or pixel mapping array is not set. The filter is not ready to be applied");
	}
	
	if(image->getFormat() != Image::FORMAT_RGB32)
	{
		LOG_ERROR("BarrelCorrection::apply(): Input image is not in RGB32 format");
		throw CameraException("Input image is not in RGB32 format");
	}
	
	int numPixels                   = m_correctedImage->getWidth() * m_correctedImage->getHeight();
	int *mapping                    = m_pixelMapping;
	ImageBuffer *cBufferAddr		= m_correctedImage->getBufferAddress();
	ImageBuffer *dBufferBaseAddr	= image->getBufferAddress();
	ImageBuffer *dBufferAddr		= NULL;
	
	if(m_pixelMappingMin < 0 || m_pixelMappingMax * 4 > image->getBufferSize())
	{
		LOG_ERROR("BarrelCorrection::apply(): Input image is not too small to contain the specified distorted rectangle");
		throw CameraException("Input image is not too small to contain the specified distorted rectangle");
	}
	
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
		
		//memcpy(cBufferAddr, dBufferAddr, 4);
		//mapping += 4;
	}
	
	return m_correctedImage;
}

void BarrelCorrection::setDistortedRectangle(int distortedRectangle[8][2])
{	
	LOG_TRACE("BarrelCorrection::setDistortedRectangle()");
	
	for(int i = 0; i < 8; i++)
	{
		m_distortedRectangle[i][0] = distortedRectangle[i][0];
		m_distortedRectangle[i][1] = distortedRectangle[i][1];
	}
	
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
	
	if(m_outputWidth == 0 || m_outputHeight == 0)
		return;
	
	// TODO: Check if reallocateing corrected image and pixel mapping array takes to much time.
	
	// Reallocate the corrected image
	if(m_correctedImage == NULL)
	{
		m_correctedImage = new Image(m_outputWidth, m_outputHeight, Image::FORMAT_RGB32);
	}
	else
	{
		m_correctedImage->reallocate(m_outputWidth, m_outputHeight);
	}
	
	// Reallocate pixel mapping array
	m_pixelMapping = (int *) realloc(m_pixelMapping, m_outputWidth * m_outputHeight * sizeof(int));
	
	calculatePixelMapping();
}


void BarrelCorrection::calculatePixelMapping()
{
	LOG_TRACE("BarrelCorrection::calculatePixelMapping()");
	
	if(m_outputWidth <= 0 || m_outputHeight <= 0)
		return;
	
	int correctedRectangle[8][2] = {
		{0,                   0},
		{m_outputWidth / 2,   0},
		{m_outputWidth - 1,   0},
		{0,                   m_outputHeight / 2},
		{m_outputWidth - 1,   m_outputHeight / 2},
		{0,                   m_outputHeight - 1},
		{m_outputWidth / 2,   m_outputHeight - 1},
		{m_outputWidth - 1,   m_outputHeight - 1}
	};
	
	float M[8][9];
	float correctionVectorA[8];
	float correctionVectorB[8];
	
	// Calculate correctionVectorA
	for (int r = 0; r < 8; r++)
	{
		M[r][0] = (float) (correctedRectangle[r][1]*correctedRectangle[r][1]*correctedRectangle[r][0]);
		M[r][1] = (float) (correctedRectangle[r][1]*correctedRectangle[r][0]*correctedRectangle[r][0]);
		M[r][2] = (float) (correctedRectangle[r][1]*correctedRectangle[r][1]);
		M[r][3] = (float) (correctedRectangle[r][0]*correctedRectangle[r][0]);
		M[r][4] = (float) (correctedRectangle[r][1]*correctedRectangle[r][0]);
		M[r][5] = (float) (correctedRectangle[r][1]);
		M[r][6] = (float) (correctedRectangle[r][0]);
		M[r][7] = 1;
		M[r][8] = (float) (m_distortedRectangle[r][1]);
	}
	solveLinearEquation(M);
	for (int r = 0; r < 8; r++)
	{
		correctionVectorA[r] = M[r][8];
	}
	
	// Calculate correctionVectorB
	for (int r = 0; r < 8; r++)
	{
		M[r][0] = (float) (correctedRectangle[r][1]*correctedRectangle[r][1]*correctedRectangle[r][0]);
		M[r][1] = (float) (correctedRectangle[r][1]*correctedRectangle[r][0]*correctedRectangle[r][0]);
		M[r][2] = (float) (correctedRectangle[r][1]*correctedRectangle[r][1]);
		M[r][3] = (float) (correctedRectangle[r][0]*correctedRectangle[r][0]);
		M[r][4] = (float) (correctedRectangle[r][1]*correctedRectangle[r][0]);
		M[r][5] = (float) (correctedRectangle[r][1]);
		M[r][6] = (float) (correctedRectangle[r][0]);
		M[r][7] = 1;
		M[r][8] = (float) (m_distortedRectangle[r][0]);
	}
	solveLinearEquation(M);
	for (int r = 0; r < 8; r++)
	{
		correctionVectorB[r] = M[r][8];
	}
	
	// Calculate pixel mapping
	int dx, dy;
	int *mapping = m_pixelMapping;
	m_pixelMappingMin = 0;
	m_pixelMappingMax = 0;
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
			
			// TODO: Fix this bug!
			// BUG: m_outputWidth should be the with of the input image. Only output with the same width as the input is supported now!
			*mapping = dy * m_outputWidth + dx;
			m_pixelMappingMin = (*mapping) < m_pixelMappingMin ? (*mapping) : m_pixelMappingMin;
			m_pixelMappingMax = (*mapping) > m_pixelMappingMax ? (*mapping) : m_pixelMappingMax;
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
