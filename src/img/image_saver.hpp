#ifndef EZGIF_IMAGE_SAVER
#define EZGIF_IMAGE_SAVER

#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <vector>
#include "image_frame.hpp"

namespace EasyGIF {
	class ImageSaver {
	private:
		sf::Image m_Image;
	public:
		void LoadData(ImageFrame frame);
		bool Save(std::string fileName);
	};
}

#endif
