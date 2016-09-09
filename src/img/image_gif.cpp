// image_gif.cpp
// Author: Tomasz Zajac

#include "image_gif.hpp"
#include <iostream>

using namespace EasyGIF;

ImageGIF::ImageGIF()
{

}

void ImageGIF::AddFrame(ImageFrame frame)
{
	m_Frames.push_back(frame); // Add a new ImageFrame at the end of the vector
}

void ImageGIF::RemoveFrames()
{
	m_Frames.clear(); // Clear the vector
}

bool ImageGIF::SaveFile(const char* filename)
{
	std::cout << "Beginning to write a GIF..." << std::endl;

	// Initialise the GifWriter struct
	// Usually, all animations will have the same width and height as the first frame, so that's what's being passed.
	// The delay should be up to the user (TODO)
	if(!GifBegin(&m_Writer, filename, m_Frames[0].GetWidth(), m_Frames[0].GetHeight(), 10))
		return false; // Return false if there is an error

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

}

