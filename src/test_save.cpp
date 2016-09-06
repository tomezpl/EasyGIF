#include "img/image_grabber.hpp"
#include "img/image_saver.hpp"
#include "img/image_frame.hpp"

using namespace EasyGIF;

int main()
{
	ImageGrabber imgGrab;
	ImageFrame imgFrame;
	ImageSaver imgSave;
	imgFrame.CreateFromPixels(imgGrab.Grab());
	imgSave.LoadData(imgFrame);
	imgSave.Save("./output.bmp");

	return 0;
}
