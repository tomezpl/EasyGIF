#include "img/image_grabber.hpp"
#include "img/image_saver.hpp"

using namespace EasyGIF;

int main()
{
	ImageGrabber imgGrab;
	ImageSaver imgSave;
	imgSave.LoadData(imgGrab.Grab());
	imgSave.Save("./output.bmp");

	return 0;
}
