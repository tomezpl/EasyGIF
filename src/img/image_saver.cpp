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

	for(unsigned short y = 0; y < frame.GetHeight(); y++)
	{
		for(unsigned short x = 0; x < frame.GetWidth(); x++)
		{
			uint8_t currR = buf[(x * 4) + (frame.GetWidth() * y)];
			uint8_t currG = buf[(x * 4) + (frame.GetWidth() * y) + 1];
			uint8_t currB = buf[(x * 4) + (frame.GetWidth() * y) + 2];
			m_Image.setPixel(x, y, sf::Color((int)(currR), (int)(currG), (int)(currB), 255));

			/*std::cout << "Pixel (" << x+1 << ", " << y+1 << ") has colour (" 
				  << (int)(m_Image.getPixel(x, y).r) << ", "
				  << (int)(m_Image.getPixel(x, y).g) << ", "
				  << (int)(m_Image.getPixel(x, y).b) << ", "
				  << (int)(m_Image.getPixel(x, y).a) << ")"
				  << std::endl;*/
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
