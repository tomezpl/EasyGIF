// image_gif.hpp
// Author: Tomasz Zajac
// The ImageGIF class allows to construct GIF animations from multiple ImageFrames,
// store them in memory and then save them to a GIF file.

#ifndef EZGIF_IMAGE_GIF
#define ifndef EZGIF_IMAGE_GIF

#include <vector>
#include "image_frame.hpp"
#ifndef gif_h
#include "../gifenc/gif.hpp"
#endif

namespace EasyGIF {
	class ImageGIF {
	private:
		std::vector<ImageFrame> m_Frames; // This vector stores all frames for the current GIF
		GifWriter m_Writer; // A GifWriter struct used by the GIF encoder
	public:
		// Default constructor
		// As of now, it does nothing
		ImageGIF();

		// Adds an ImageFrame to the vector
		void AddFrame(ImageFrame frame);

		// Clears the whole vector
		// Useful if you want to reuse the object
		void RemoveFrames();

		// Initialises the GifWriter struct,
		// passes all frames for writing,
		// and saves them to a GIF file under the specified name.
		bool SaveFile(const char* filename);

		// Destructor
		// Currently, it does nothing
		~ImageGIF();
	};
}

#endif
