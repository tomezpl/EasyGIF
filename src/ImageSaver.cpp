#include "ImageSaver.hpp"

using namespace EasyGIF;

void ImageSaver::LoadData(std::vector<std::vector<uint8_t*>> data)
{
	m_Image.create(1920, 1080, sf::Color::White);

	if(data.size() == 0)
	{
		std::cout << "Wrong pixel data" << std::endl;
		return;
	}

	for(unsigned short y = 0; y < data.size(); y++)
	{
		for(unsigned short x = 0; x < data[y].size(); x++)
		{
			m_Image.setPixel(x, y, sf::Color(data[y][x][0], data[y][x][1], data[y][x][2], data[y][x][3]));
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
