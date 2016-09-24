// image_saver.cpp
// Author: Tomasz Zajac

#include "image_saver.hpp"

using namespace EasyGIF;

bool ImageSaver::Save(std::string fileName)
{
	#ifdef EZGIF_DEBUG
	std::cout << "Filename is " << fileName;
	#endif
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
