// image_saver.hpp
// Author: Tomasz Zajac
// The ImageSaver class provides an interface to save an image (e.g. one captured with ImageGrabber) to a file using SFML.
// It is based on the ImageContainer class.

#ifndef EZGIF_IMAGE_SAVER
#define EZGIF_IMAGE_SAVER

#include "image_container.hpp"

namespace EasyGIF {
	class ImageSaver : public ImageContainer {
	public:
		
		// This function saves the previously constructed image (by using LoadData())
		// to a file, and returns true on success, and false on error.
		bool Save(std::string fileName);
	};
}

#endif
