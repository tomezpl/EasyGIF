// virtual_desktop.hpp
// Author: Tomasz Zajac
// The VirtualDesktop class can be used to get a bitmap consisting of all windows on the desktop,
// but ignores the EasyGIF window in order to allow drawing a UI at the same time.
// A lot of stuff is inherited from ImageGrabber.

#ifndef EZGIF_UI_VDESKTOP
#define EZGIF_UI_VDESKTOP

#include "../img/image_grabber.hpp"
#include <iostream>
#include <cstdlib>

namespace EasyGIF {
	namespace UI {
		class VirtualDesktop : protected ::EasyGIF::ImageGrabber {
		private:
			xcb_window_t* m_Windows; // non-free software
		public:
			VirtualDesktop(char* display = nullptr);
			~VirtualDesktop();
		};
	}
}

#endif
