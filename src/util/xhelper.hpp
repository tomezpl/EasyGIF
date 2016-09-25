// xhelper.hpp
// Author: Tomasz Zajac
// The XHelper class provides utility functions to make it easier when dealing with Xlib/XCB stuff.

#ifndef EZGIF_UTIL_XHELPER
#define EZGIF_UTIL_XHELPER

#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include <xcb/xcb_image.h>
#include <xcb/xproto.h>
#include <xcb/xcb_util.h>
#include <cstdlib>

namespace EasyGIF {
	namespace Utility {
		struct Rectangle {
			short x, y;
			short width, height;
		};

		static const Rectangle EmptyRect = {0, 0, 0, 0};

		static bool operator==(const Rectangle& lR, const Rectangle& rR)
		{
			if(lR.x == rR.x && lR.y == rR.y && lR.width == rR.width && lR.height == rR.height)
				return true;
			else
				return false;
		}

		class XHelper {
		private:
			xcb_connection_t** m_XConn; // connection to X display
		public:
			XHelper(xcb_connection_t** connection);
			Rectangle GetRect(xcb_window_t window); // returns a rectangle structure of a window, not to be confused with "get rekt"
			~XHelper();
		};
	}
}

#endif
