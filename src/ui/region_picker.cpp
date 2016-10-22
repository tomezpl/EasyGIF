// region_picker.cpp
// Author: Tomasz Zajac

#include "region_picker.hpp"

using namespace EasyGIF::UI;

RegionPicker::RegionPicker(bool activate)
{
	m_IsConfirmed = false;
	m_IsPicking = false;
	m_IsRunning = false;
	m_Region = {0, 0, 0, 0};
	m_XInverted = false;
	m_YInverted = false;

	if(activate)
		this->Activate();
}

void RegionPicker::getDesktopSprite()
{
	::EasyGIF::ImageFrame desktopScreenshot(m_Grabber.Grab());
	m_WinWidth = desktopScreenshot.GetWidth();
	m_WinHeight = desktopScreenshot.GetHeight();
	m_DesktopTexture.create(m_WinWidth, m_WinHeight);
	m_DesktopTexture.loadFromImage(m_Converter.ImgFrameToSFImage(desktopScreenshot));
	m_Desktop.setTexture(m_DesktopTexture);
	m_Desktop.setPosition(0, 0);
}

void RegionPicker::Activate()
{
	this->getDesktopSprite();
	#ifdef EZGIF_DEBUG
	std::cout << "RegionPicker " << std::to_string(m_WinWidth) << "x" << std::to_string(m_WinHeight) << std::endl;
	#endif
	m_Window.create(sf::VideoMode(m_WinWidth, m_WinHeight), "EasyGIF RegionPicker", sf::Style::Fullscreen);
	m_IsRunning = true;
}

::EasyGIF::Utility::Rectangle RegionPicker::GetRect()
{
	return m_Region;
}

bool RegionPicker::IsConfirmed()
{
	return m_IsConfirmed;
}

bool RegionPicker::IsRunning()
{
	return m_IsRunning;
}

void RegionPicker::ProcessInput()
{
	bool isPicking = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	sf::Vector2i mousePos = sf::Mouse::getPosition(m_Window);

	if(isPicking)
	{
		if(m_IsPicking)
		{
			if(m_Region.x > mousePos.x)
				m_XInverted = true;
			else
				m_XInverted = false;

			if(m_Region.y > mousePos.y)
				m_YInverted = true;
			else
				m_YInverted = false;

			m_Region.width = mousePos.x - m_Region.x;
			m_Region.height = mousePos.y - m_Region.y;
		}
		else
		{
			m_Region.x = mousePos.x;
			m_Region.y = mousePos.y;
			m_Region.width = 0;
			m_Region.height = 0;
		}
	}

	m_IsPicking = isPicking;
}

void RegionPicker::UpdateEvents()
{
	if(m_Window.isOpen())
	{
		sf::Event event;
		while(m_Window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				m_Window.close();
				m_IsRunning = false;
			}
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Return)
					m_IsConfirmed = true;
			}
		}
	}
}

void RegionPicker::Draw()
{
	if(m_Window.isOpen())
	{
		sf::Texture selectionTexture;
		sf::Image selectionTextureImg;
		sf::Sprite selection;

		if(m_Region.width != 0 && m_Region.height != 0 && m_Region.width < m_WinWidth && m_Region.height < m_WinHeight)
		{
			selectionTextureImg.create(std::abs(m_Region.width), std::abs(m_Region.height));
			selectionTexture.create(std::abs(m_Region.width), std::abs(m_Region.height));

			for(unsigned short x = 0; x < std::abs(m_Region.width); x++)
			{
				for(unsigned short y = 0; y < std::abs(m_Region.height); y++)
					selectionTextureImg.setPixel(x, y, sf::Color::White);
			}

			selectionTexture.loadFromImage(selectionTextureImg);

			selection.setTexture(selectionTexture);
			selection.setColor(sf::Color(64, 64, 64, 64));

			unsigned short xPos = 0, yPos = 0;
			if(m_XInverted)
				xPos = m_Region.x + m_Region.width;
			else
				xPos = m_Region.x;

			if(m_YInverted)
				yPos = m_Region.y + m_Region.height;
			else
				yPos = m_Region.y;

			selection.setPosition(xPos, yPos);
		}

		m_Window.clear();
		m_Window.draw(m_Desktop);
		if(m_Region.width != 0 && m_Region.height != 0 && m_Region.width < m_WinWidth && m_Region.height < m_WinHeight)
			m_Window.draw(selection);
		m_Window.display();
	}
}

void RegionPicker::Shutdown()
{
	m_IsRunning = false;

	m_Window.clear();
	m_Window.draw(m_Desktop);
	m_Window.display();

	m_Window.close();
}
