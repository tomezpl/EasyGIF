#include "image_gif.hpp"
#include <iostream>

using namespace EasyGIF;

ImageGIF::ImageGIF()
{
	//m_Writer = new GifWriter();
}

void ImageGIF::AddFrame(ImageFrame frame)
{
	m_Frames.push_back(frame);
}

void ImageGIF::RemoveFrames()
{
	m_Frames.clear();
}

bool ImageGIF::SaveFile(const char* filename)
{
	std::cout << "Beginning to write a GIF..." << std::endl;
	if(!GifBegin(&m_Writer, filename, m_Frames[0].GetWidth(), m_Frames[0].GetHeight(), 10))
		return false;

	std::cout << "Starting writing frames" << std::endl;
	for(unsigned long i = 0; i < m_Frames.size(); i++)
	{
		std::cout << "Writing a frame..." << std::endl;
		if(!GifWriteFrame(&m_Writer, m_Frames[i].GetBuffer(), m_Frames[0].GetWidth(), m_Frames[0].GetHeight(), 10))
			return false;
		std::cout << "Frame written!" << std::endl;
	}

	std::cout << "Finishing writing a GIF..." << std::endl;
	if(!GifEnd(&m_Writer))
		return false;
	std::cout << "GIF writing finished!" << std::endl;
}

ImageGIF::~ImageGIF()
{
	//delete m_Writer;
}

