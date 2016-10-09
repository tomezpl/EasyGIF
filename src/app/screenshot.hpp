// screenshot.hpp
// Author: Tomasz Zajac
// The Screenshot classes provide a screenshot taker app that incorporates RegionPicker, ImageGrabber, ImageFrame, ImageSaver and other objects.

#ifndef EZGIF_APP_SCREENSHOT
#define EZGIF_APP_SCREENSHOT

#include "../ui/region_picker.hpp"
#include "../img/image_frame.hpp"
#include "../img/image_gif.hpp"
#include "../img/image_grabber.hpp"
#include "../img/image_saver.hpp"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

namespace EasyGIF {
	namespace App {
		// Abstract base class
		class Screenshot {
		protected:
			::EasyGIF::UI::RegionPicker* m_Picker;
			::EasyGIF::ImageGrabber m_Grabber;
			::EasyGIF::ImageFrame m_Frame;
			virtual void GetData() = 0;
		public:
			Screenshot();
			void RunUI();
			virtual bool Save(std::string filename) = 0;
			~Screenshot();
		};

		// Static pictures (one frame, e.g. JPEG, PNG, BMP etc.)
		class ScreenshotStatic : public Screenshot {
		private:
			::EasyGIF::ImageSaver m_Saver;
		protected:
			void GetData();
		public:
			ScreenshotStatic() = default;
			bool Save(std::string filename);
		};

		// Animated GIFs (multiple frames, need to be encoded and written using GIF-H)
		class ScreenshotGIF : public Screenshot {
		private:
			::EasyGIF::ImageGIF m_GIF;
		protected:
			void GetData();
		public:
			ScreenshotGIF() = default;
			bool Save(std::string filename);
		};
	}
}

#endif
