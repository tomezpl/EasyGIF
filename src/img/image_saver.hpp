#ifndef EZGIF_IMAGE_SAVER
#define EZGIF_IMAGE_SAVER

#include <SFML/Graphics/Image.hpp>
#include <iostream>
#include <vector>

namespace EasyGIF {
	class ImageSaver {
	private:
		sf::Image m_Image;
	public:
		void LoadData(std::vector<std::vector<uint8_t*>> data);
		bool Save(std::string fileName);
	};
}

#endif
