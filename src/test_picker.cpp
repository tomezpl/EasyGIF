#include "img/image_frame.hpp"
#include "img/image_grabber.hpp"
#include "img/image_saver.hpp"
#include "ui/region_picker.hpp"
#include <unistd.h>

int main()
{
	EasyGIF::UI::RegionPicker picker(false);
	EasyGIF::ImageFrame frame;
	EasyGIF::ImageGrabber grabber;
	EasyGIF::ImageSaver saver;
	picker.Activate();
	while(picker.IsRunning())
	{
		picker.UpdateEvents();
		if(picker.IsConfirmed())
		{
			::EasyGIF::Utility::Rectangle rect = picker.GetRect();
			picker.Shutdown();
			sleep(5); // let X close the window
			frame = grabber.Grab(rect);
			saver.LoadData(frame);
			saver.Save("./test_picker.png");
		}
		else
		{
			picker.ProcessInput();
			picker.Draw();
		}
	}

	return 0;
}
