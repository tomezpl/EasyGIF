#ifndef EZGIF_IMAGE_FRAME
#define EZGIF_IMAGE_FRAME

#include <stdint.h>
#include <vector>
#include <SFML/Graphics/Image.hpp>

namespace EasyGIF {
	class ImageFrame {
	private:
		std::vector<std::vector<uint8_t*>> m_Data; // pixel data
	public:
		ImageFrame();
		ImageFrame(std::vector<std::vector<uint8_t*>> data);
		void CreateFromPixels(std::vector<std::vector<uint8_t*>> data);
		unsigned short GetHeight();
		uint8_t* GetIndices(); // returns an array of indices to palette entries for all pixels - DO NOT USE
		uint8_t* GetBuffer(); // returns an array of RGB colours for each pixel for the GIF encoder
		uint8_t* GetPixel(unsigned short x, unsigned short y);
		unsigned short GetWidth();
		void SetPixel(unsigned short x, unsigned short y, uint8_t* pixel);
		~ImageFrame();
	};
}

#endif
