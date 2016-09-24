#include "image_container.hpp"

using namespace EasyGIF;

void ImageContainer::LoadData(ImageFrame frame)
{
	m_Image = m_Converter.ImgFrameToSFImage(frame);	
}

void ImageContainer::LoadData(sf::Image image)
{
	m_Image = image;
}

sf::Image ImageContainer::GetImage()
{
	return m_Image;
}
