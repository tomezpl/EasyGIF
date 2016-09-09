// image_frame.hpp
// Author: Tomasz Zajac
// The ImageFrame class stores data about a captured image (pixels, size, etc.)
// It also provides an interface to retrieve data from it (e.g. an RGBA8 buffer)
// and allows to manipulate it (e.g. modifying pixels)

#ifndef EZGIF_IMAGE_FRAME
#define EZGIF_IMAGE_FRAME

#include <stdint.h>
#include <vector>
#include <iostream>
#include <SFML/Graphics/Image.hpp>

namespace EasyGIF {
	class ImageFrame {
	private:
		std::vector<std::vector<uint8_t*>> m_Data; // pixel data
	public:
		// Default constructor
		// Does nothing
		ImageFrame();

		// Constructor
		// Calls CreateFromPixels()
		ImageFrame(std::vector<std::vector<uint8_t*>> data);

		// Loads pixel data into a vector
		void CreateFromPixels(std::vector<std::vector<uint8_t*>> data);

		unsigned short GetHeight();

		// Returns an array of unsigned chars (numbers in range 0-255) representing each pixel
		// This is more of a "raw" representation of the pixel data,
		// values for R, G, B and A are stored adjacently,
		// so each pixel takes 4 elements of the array
		// (and so the size is width * height * 4)
		// Needed for the GIF encoder
		uint8_t* GetBuffer();

		// Gets a single pixel from the specified coordinates
		uint8_t* GetPixel(unsigned short x, unsigned short y);

		unsigned short GetWidth();

		// Modifies the RGBA values of a pixel at specified coordinates
		void SetPixel(unsigned short x, unsigned short y, uint8_t* pixel);

		// Destructor
		// Does nothing
		~ImageFrame();
	};
}

#endif
