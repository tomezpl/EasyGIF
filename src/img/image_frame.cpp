#include "image_frame.hpp"

using namespace EasyGIF;

ImageFrame::ImageFrame()
{
	// I'll add something here... at some point.
}

ImageFrame::ImageFrame(std::vector<std::vector<uint8_t*>> data)
{
	this->CreateFromPixels(data);
}

unsigned short ImageFrame::GetHeight()
{
	return m_Data.size();
}

uint8_t* ImageFrame::GetIndices()
{
	//uint8_t* palette = this->GetPalette();
	uint8_t* ret = new uint8_t[this->GetHeight() * this->GetWidth()];

	return ret;
}

uint8_t* ImageFrame::GetBuffer()
{
	uint8_t* ret = new uint8_t[4 * this->GetHeight() * this->GetWidth()];

	for(unsigned short y = 0; y < this->GetHeight(); y++)
	{
		for(unsigned short x = 0; x < this->GetWidth(); x += 1)
		{
			uint8_t r = m_Data[y][x][0], g = m_Data[y][x][1], b = m_Data[y][x][2];
			//unsigned long hex = (r << 16) | (g << 8) | b;
			ret[(x * 4) + (this->GetWidth() * y)] = r;
			ret[(x * 4) + (this->GetWidth() * y) + 1] = g;
			ret[(x * 4) + (this->GetWidth() * y) + 2] = b;
			ret[(x * 4) + (this->GetWidth() * y) + 3] = 0;
		}
	}

	/*sf::Image tImg;
	tImg.create(this->GetWidth(), this->GetHeight());

	for(unsigned short y = 0; y < this->GetHeight(); y++)
	{
		for(unsigned short x = 0; x < this->GetWidth(); x++)
		{
			uint8_t* currPix = this->GetPixel(x, y);
			tImg.setPixel(x, y, sf::Color((int)(currPix[0]), (int)(currPix[1]), (int)(currPix[2]), 255));
		}
	}

	const uint8_t* tempPixels = tImg.getPixelsPtr();
	uint8_t* ret = new uint8_t[sizeof(tempPixels)];
	for(unsigned long long i = 0; i < sizeof(tempPixels); i++)
	{
		ret[i] = tempPixels[i];
	}*/
	
	return ret;
}

uint8_t* ImageFrame::GetPixel(unsigned short x, unsigned short y)
{
	return m_Data[y][x];
}

unsigned short ImageFrame::GetWidth()
{
	return m_Data[0].size();
}

void ImageFrame::SetPixel(unsigned short x, unsigned short y, uint8_t* pixel)
{
	m_Data[y][x] = pixel;
}

void ImageFrame::CreateFromPixels(std::vector<std::vector<uint8_t*>> data)
{
	m_Data = data;
}

ImageFrame::~ImageFrame()
{
	/*for(unsigned short y = 0; y < m_Data.size(); y++)
	{
		for(unsigned short x = 0; x < m_Data[y].size(); x++)
		{
			delete[] m_Data[y][x]; // delete the pixel
		}
		m_Data[y].clear(); // remove the current line from the vector
	}
	m_Data.clear(); // remove everything from the vector*/
}
