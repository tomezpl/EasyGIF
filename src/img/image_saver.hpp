// image_saver.hpp
// Author: Tomasz Zajac
// The ImageSaver class provides an interface to save an image (e.g. one captured with ImageGrabber) to a file using SFML.

#ifndef EZGIF_IMAGE_SAVER
#define EZGIF_IMAGE_SAVER

#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <vector>
#include "image_frame.hpp"

namespace EasyGIF {
	class ImageSaver {
	private:
		sf::Image m_Image; // Image object that will be used to save the image to a file
	public:
		// This method loads pixels from the ImageFrame into the image object.
		// The ImageFrame will contain a vector of vectors of pixels,
		// returned from ImageGrabber::Grab(), for example.
		// Although it was previously possible to only pass a vector of vectors of pixels,
		// this is a more "elegant" way of doing it.
		void LoadData(ImageFrame frame);

		// This function saves the previously constructed image (by using LoadData())
		// to a file, and returns true on success, and false on error.
		bool Save(std::string fileName);
	};
}

#endif
