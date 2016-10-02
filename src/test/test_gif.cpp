#include "../img/image_frame.hpp"
#include "../img/image_gif.hpp"
#include "../img/image_grabber.hpp"
#include <iostream>

int main()
{
	EasyGIF::ImageFrame imgFrame;
	EasyGIF::ImageGIF imgGIF;
	EasyGIF::ImageGrabber imgGrab;

	for(unsigned short i = 0; i < 10; i++)
	{
		imgFrame.CreateFromPixels(imgGrab.Grab());
		imgGIF.AddFrame(imgFrame);
	}

	if(imgGIF.SaveFile("./output.gif"))
		std::cout << "GIF saved successfully!" << std::endl;
	else
		std::cout << "There was an error saving the GIF file." << std::endl;

	return 0;
}
