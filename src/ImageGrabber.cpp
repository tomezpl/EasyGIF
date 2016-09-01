#include "ImageGrabber.hpp"
#include <iostream>

using namespace EasyGIF;

ImageGrabber::ImageGrabber(char* display)
{
	//m_XConnection = xcb_connect(display, &m_XScreenNumber);
	m_XDisplay = XOpenDisplay(nullptr);
	//m_XScreen = screen_of_display(m_XConnection, m_XScreenNumber);
	//m_XSetup = nullptr;
	//m_ImageData = nullptr;

	if(m_XDisplay)
	{
		std::cout << "Copying root window" << std::endl;
		m_XWindow = DefaultRootWindow(m_XDisplay);
		if(m_XWindow)
			std::cout << "Root window copied successfully" << std::endl;
		else
			std::cout << "Root window is null" << std::endl;
	}
	else
	{
		std::cout << "Display is null!" << std::endl;
	}
}

std::vector<std::vector<uint8_t*>> ImageGrabber::Grab()
{
	//xcb_get_image_reply_t* img = xcb_get_image_reply(m_XConnection, xcb_get_image(m_XConnection, XCB_IMAGE_FORMAT_Z_PIXMAP, m_XWindow, 0, 0, 1920, 1080, ~0), nullptr);

	m_Img = XGetImage(m_XDisplay, m_XWindow, 0, 0, 1920, 1080, 0xffffffff, ZPixmap);

	std::vector<std::vector<uint8_t*>> ret;

	if(!m_Img)
	{
		std::cout << "Failed to grab image" << std::endl;
		return ret;
	}

	for(unsigned short y = 0; y < m_Img->height; y++)
	{
		std::vector<uint8_t*> currentLine;

		for(unsigned short x = 0; x < m_Img->width; x++)
		{
			unsigned long currentPixel = XGetPixel(m_Img, x, y);
			uint8_t* convertedPixel = new uint8_t[4];

			convertedPixel[0] = (currentPixel & 0x000000ff);
			convertedPixel[1] = (currentPixel & 0x0000ff00) >> 8;
			convertedPixel[2] = (currentPixel & 0x00ff0000) >> 16;
			convertedPixel[3] = (currentPixel & 0xff000000) >> 24;

			std::cout << "Pixel (" << x+1 << ", " << y+1 << ") has colour (" 
				  << (int)convertedPixel[0] << ", "
				  << (int)convertedPixel[1] << ", "
				  << (int)convertedPixel[2] << ", "
				  << (int)convertedPixel[3] << ")"
				  << std::endl;

			currentLine.push_back(convertedPixel);
			delete[] convertedPixel;
		}

		ret.push_back(currentLine);
	}


	return ret;
}

/*std::vector<std::vector<uint8_t>> ImageGrabber::Grab()
{
	for(unsigned short i = 0; i < img->width; i++)
	{
		for(unsigned short i = 0; i< img->height; i++)
		{

		}
	}
}*/

/*size_t ImageGrabber::GetLastLength()
{
	return m_ImageDataLength;
}*/

ImageGrabber::~ImageGrabber()
{
	XDestroyImage(m_Img);
}
