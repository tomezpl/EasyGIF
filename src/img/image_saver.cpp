#include "image_saver.hpp"

using namespace EasyGIF;

void ImageSaver::LoadData(ImageFrame frame)
{
	m_Image.create(frame.GetWidth(), frame.GetHeight(), sf::Color::White);

	//if(data.size() == 0)
	//{
		//std::cout << "Wrong pixel data" << std::endl;
		//return;
	//}
	uint8_t* buf = frame.GetBuffer();

	for(unsigned long y = 0; y < frame.GetHeight(); y++)
	{
		unsigned long realX = 0;
		for(unsigned long x = y * 4 * frame.GetWidth(); x < (y + 1) * frame.GetWidth() * 4; x += 4)
		{
			uint8_t currR = buf[x];
			uint8_t currG = buf[x + 1];
			uint8_t currB = buf[x + 2];
			m_Image.setPixel(realX, y, sf::Color((int)(currR), (int)(currG), (int)(currB), 255));

			/*std::cout << "Pixel (" << x+1 << ", " << y+1 << ") has colour (" 
				  << (int)(m_Image.getPixel(x, y).r) << ", "
				  << (int)(m_Image.getPixel(x, y).g) << ", "
				  << (int)(m_Image.getPixel(x, y).b) << ", "
				  << (int)(m_Image.getPixel(x, y).a) << ")"
				  << std::endl;*/
			realX++;
		}
	}
}

bool ImageSaver::Save(std::string fileName)
{
	if(m_Image.saveToFile(fileName))
	{
		std::cout << "File saved successfully" << std::endl;
		return true;
	}
	else
	{
		std::cout << "There was an error saving the file" << std::endl;
		return false;
	}
}
