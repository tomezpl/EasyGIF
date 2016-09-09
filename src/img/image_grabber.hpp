// image_grabber.hpp
// Author: Tomasz Zajac
// The ImageGrabber class allows to take a "screenshot" from an X display.

#ifndef EZGIF_IMAGE_GRABBER
#define EZGIF_IMAGE_GRABBER

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <xcb/xcb_image.h>
#include <xcb/xcb_util.h>
#include <cstdint>
#include <vector>
#include <cmath>

namespace EasyGIF {
	class ImageGrabber {
	private:
		xcb_connection_t* m_XConnection; // Connection to X display
		xcb_screen_t* m_XScreen; // Screen from X display to grab root window from
		xcb_screen_iterator_t m_XScreenIter;
		xcb_window_t m_XWindow; // Window from X screen to grab image from
		const xcb_setup_t* m_XSetup; // X display setup
		int m_XScreenNumber; // X screen number, if necessary
		xcb_image_t* m_Img; // Current XImage
	public:
		// Default constructor
		// A null pointer will work in most cases where there is only one X display (not to be confused with X screen)
		ImageGrabber(char* display = nullptr);

		// Takes a screenshot and returns pixels from it
		// The vector contains another vector inside it for each line/row
		// Inside each line, pixels are stored as arrays of 4 elements (RGBA channels)
		std::vector<std::vector<uint8_t*>> Grab();

		// Destructor
		// Deallocates memory, disconnects from the X server
		~ImageGrabber();
	};
}

#endif
