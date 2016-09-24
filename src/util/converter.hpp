// converter.hpp
// Author: Tomasz Zajac
// The Converter class provides an interface to convert from one datatype to another

#ifndef EZGIF_UTIL_CONVERTER
#define EZGIF_UTIL_CONVERTER

#include "../img/image_frame.hpp"
#include <SFML/Graphics/Image.hpp>

namespace EasyGIF {
	namespace Utility {
		class Converter {
		public:
			sf::Image ImgFrameToSFImage(::EasyGIF::ImageFrame frame);
		};
	}
}

#endif
