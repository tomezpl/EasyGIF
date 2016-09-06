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
		std::vector<ImageFrame> m_Frames;
		GifWriter m_Writer;
	public:
		ImageGIF();
		void AddFrame(ImageFrame frame);
		void RemoveFrames();
		bool SaveFile(const char* filename);
		~ImageGIF();
	};
}

#endif
