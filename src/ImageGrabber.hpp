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
		//Display* m_XDisplay;
		xcb_connection_t* m_XConnection;
		xcb_screen_t* m_XScreen;
		xcb_screen_iterator_t m_XScreenIter;
		xcb_window_t m_XWindow;
		//Window m_XWindow;
		const xcb_setup_t* m_XSetup;
		int m_XScreenNumber;
		//uint8_t* m_ImageData;
		//XImage* m_Img;
		xcb_image_t* m_Img;
		//size_t m_ImageDataLength;
		//xcb_screen_t* screen_of_display (//xcb_connection_t *c, int screen);
	public:
		ImageGrabber(char* display = nullptr);
		std::vector<std::vector<uint8_t*>> Grab();
		~ImageGrabber();
	};
}

#endif
