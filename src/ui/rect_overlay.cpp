#include "rect_overlay.hpp"
#include <iostream>

using namespace EasyGIF::UI;

RectOverlay::RectOverlay() : Overlay()
{
	m_Rect = ::EasyGIF::Utility::EmptyRect; // initialise an empty rectangle
}

void RectOverlay::Draw()
{
	// TODO: the code contains hard-coded colour values

	cairo_set_source_rgba(m_Context, 0.25, 0.25, 0.25, 0.01);
	std::cout << "RectX: " << m_Rect.x << ", RectY: " << m_Rect.y << ", RectWidth: " << m_Rect.width << ", RectHeight: " << m_Rect.height << std::endl;
	cairo_rectangle(m_Context, m_Rect.x, m_Rect.y, m_Rect.width, m_Rect.height);
	cairo_fill(m_Context);
	//std::cout << "Cairo is drawing" << std::endl;
}

::EasyGIF::Utility::Rectangle* RectOverlay::GetRectPtr()
{
	return &m_Rect;
}
