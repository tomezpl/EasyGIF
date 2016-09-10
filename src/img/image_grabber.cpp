// image_grabber.cpp
// Author: Tomasz Zajac

#include "image_grabber.hpp"
#include <iostream>

using namespace EasyGIF;

ImageGrabber::ImageGrabber(char* display)
{
	m_XConnection = xcb_connect(display, &m_XScreenNumber); // Connect to an X display
	m_XSetup = xcb_get_setup(m_XConnection); // Get setup from the X display
	m_XScreen = nullptr; // I don't know why I'm doing this, but I prefer to initialise it like this.
	m_XScreenIter = xcb_setup_roots_iterator(m_XSetup);
	m_XScreen = m_XScreenIter.data; // Get screen from the X display based on the iterator
					// TODO: add support for multi-monitor setups

	m_Img = nullptr; // Initialise the image

	// Check if the screen is initialised
	if(m_XScreen)
	{
		std::cout << "Screen " << m_XScreenNumber << " open successfully!" << std::endl;
		std::cout << "Copying root window" << std::endl;
		m_XWindow = m_XScreen->root; // Copy the root window (ie. the whole screen)
		if(m_XWindow)
			std::cout << "Root window copied successfully" << std::endl;
		else
			std::cout << "Root window is null" << std::endl;
	}
	else
	{
		std::cout << "Screen is null!" << std::endl;
	}
}

std::vector<std::vector<uint8_t*>> ImageGrabber::Grab()
{
	// Get an image from the root window using the open X display connection
	m_Img = xcb_image_get(m_XConnection, m_XWindow, 0, 0, 1920, 1080, ~0, XCB_IMAGE_FORMAT_Z_PIXMAP);

	// Vector to be returned
	std::vector<std::vector<uint8_t*>> ret;

	// Check if the image is null, and return an empty vector if so.
	if(!m_Img)
	{
		std::cout << "Failed to grab image" << std::endl;
		return ret;
	}

	// Iterate through the image and get each pixel
	for(unsigned short y = 0; y < m_Img->height; y++)
	{
		std::vector<uint8_t*> currentLine;

		for(unsigned short x = 0; x < m_Img->width; x++)
		{
			unsigned long currentPixel = xcb_image_get_pixel(m_Img, x, y);
			uint8_t* convertedPixel = new uint8_t[4]; // This will store values for each of R, G, B and A channels

			// Extracting bits for each channel:
			// I do realise it's in weird order,
			// however, X seems to return pixels in BGRA format,
			// and we need it in RGBA,
			// that's why the blue channel is first to be extracted.
			convertedPixel[2] = (currentPixel & 0x000000ff);
			convertedPixel[1] = (currentPixel & 0x0000ff00) >> 8;
			convertedPixel[0] = (currentPixel & 0x00ff0000) >> 16;
			convertedPixel[3] = (currentPixel & 0xff000000) >> 24;

			/*std::cout << "Pixel (" << x+1 << ", " << y+1 << ") has colour (" 
				  << (int)convertedPixel[0] << ", "
				  << (int)convertedPixel[1] << ", "
				  << (int)convertedPixel[2] << ", "
				  << (int)convertedPixel[3] << ")"
				  << std::endl;*/

			currentLine.push_back(convertedPixel); // add pixel to the current line
			//delete[] convertedPixel;
		}

		ret.push_back(currentLine); // add current line to the final return value
	}


	return ret;
}

ImageGrabber::~ImageGrabber()
{
	xcb_disconnect(m_XConnection);
	delete m_Img;
}
