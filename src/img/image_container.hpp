// image_container.hpp
// Author: Tomasz Zajac
// The ImageContainer class simply holds an sf::Image object.

#ifndef EZGIF_IMAGE_CONTAINER
#define EZGIF_IMAGE_CONTAINER

#include "image_frame.hpp"
#include "../util/converter.hpp"
#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <vector>

namespace EasyGIF {
	class ImageContainer {
	protected:
		::EasyGIF::Utility::Converter m_Converter; // Utility converter object
		sf::Image m_Image; // Image object
	public:
		sf::Image GetImage(); // Returns the Image object

		// This method loads pixels from the ImageFrame into the image object.
		// The ImageFrame will contain a vector of vectors of pixels,
		// returned from ImageGrabber::Grab(), for example.
		// Although it was previously possible to only pass a vector of vectors of pixels,
		// this is a more "elegant" way of doing it.
		void LoadData(ImageFrame frame);

		// Alternatively, you can pass an sf::Image if you already have it
		void LoadData(sf::Image image);
	};
}

#endif
