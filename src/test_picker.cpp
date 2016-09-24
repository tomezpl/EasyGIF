#include "ui/region_picker.hpp"

int main()
{
	EasyGIF::UI::RegionPicker picker(false);
	picker.Activate();
	while(picker.IsRunning())
	{
		picker.UpdateEvents();
		picker.ProcessInput();
		picker.Draw();
	}

	return 0;
}
