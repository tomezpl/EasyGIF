#ifndef EZGIF_UI_RECTOVERLAY
#define EZGIF_UI_RECTOVERLAY

#include "overlay.hpp"
#include "../util/xhelper.hpp"

namespace EasyGIF
{
	namespace UI
	{
		class RectOverlay : public Overlay
		{
		private:
			::EasyGIF::Utility::Rectangle m_Rect;
		public:
			RectOverlay();
			void Draw();
			::EasyGIF::Utility::Rectangle* GetRectPtr(); // returns a pointer to the rectangle
		};
	}
}

#endif
