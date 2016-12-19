#ifndef EZGIF_UI_OVERLAY
#define EZGIF_UI_OVERLAY

#include <X11/Xlib.h>

#include <X11/extensions/Xcomposite.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/shape.h>

#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>

namespace EasyGIF
{
	namespace UI
	{
		class Overlay
		{
		private:
			int m_Screen;
			_XDisplay* m_Display;

			Window m_Overlay;
			Window m_RootWnd;

			unsigned short m_Width, m_Height;
		protected:
			cairo_surface_t* m_Surface;
			cairo_t* m_Context;
		public:
			// Default constructor
			Overlay();

			// Initialise Xlib and Cairo
			void Init();

			// Virtual function to allow multiple overlay types
			// DO NOT call this function manually, 
			// it is already called inside Display() (which is implemented)
			virtual void Draw();

			// Calls the drawing function and executes some X-specific code
			virtual void Display();

			// Performs cleanup and releasing (Cairo and X specific)
			void Shutdown();

			// Default destructor
			~Overlay();
		};
	}
}

#endif
