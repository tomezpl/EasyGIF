#include "ImageGrabber.hpp"
#include "ImageSaver.hpp"

using namespace EasyGIF;

int main()
{
	ImageGrabber imgGrab;
	ImageSaver imgSave;
	imgSave.LoadData(imgGrab.Grab());
	imgSave.Save("./output.bmp");

	return 0;
}
