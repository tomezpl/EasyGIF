// region_picker.hpp
// Author: Tomasz Zajac
// The RegionPicker class provides a UI component that lets the user select the region for the screen capture.

#ifndef EZGIF_UI_REGIONPICKER
#define EZGIF_UI_REGIONPICKER

#include "../img/image_container.hpp"
#include "../img/image_frame.hpp"
#include "../img/image_grabber.hpp"
#include "../util/converter.hpp"
#include "../util/xhelper.hpp"
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//#include "rect_overlay.hpp"

namespace EasyGIF {
	namespace UI {
		class RegionPicker : public ImageContainer {
		private:
			bool m_IsPicking; // is the user picking the region? (ie. is left mouse button pressed)
			::EasyGIF::Utility::Rectangle m_Region; // selected region
			sf::RenderWindow m_Window; // Window to draw UI
			::EasyGIF::ImageGrabber m_Grabber; // desktop grabber
			sf::Sprite m_Desktop; // desktop sprite to draw in the UI
			sf::Texture m_DesktopTexture; // texture for the desktop sprite
			void getDesktopSprite(); // initialise the desktop sprite
			unsigned short m_WinWidth, m_WinHeight; // window size
			::EasyGIF::Utility::Converter m_Converter; // utility converter class
			bool m_IsRunning; // is the region picker running?
			bool m_XInverted, m_YInverted; // is the selection "inverted"?
			bool m_IsConfirmed; // did the user confirm the region?
			//RectOverlay* m_Overlay; // rectangular overlay
		public:
			// Default constructor
			// Also activates/initialises/launches (you name it) the region picker
			// (unless activate is set to false, of course)
			RegionPicker(bool activate = true);

			// Creates and initialises the UI, launches the region picker
			void Activate();

			// Returns the region rectangle
			::EasyGIF::Utility::Rectangle GetRect();

			// Returns whether the region picker has finished or not
			bool IsConfirmed();

			// Returns whether the region picker is running or not
			bool IsRunning();

			// Process mouse input in order to update the region rectangle
			void ProcessInput();

			// Update window events
			void UpdateEvents();

			// Draw the UI
			void Draw();

			// Shutdown the RegionPicker
			void Shutdown();
		};
	}
}

#endif
