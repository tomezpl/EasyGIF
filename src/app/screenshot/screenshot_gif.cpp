#include "../screenshot.hpp"

#define EzApp EasyGIF::App
#define EzUI EasyGIF::UI

void EzApp::ScreenshotGIF::GetData()
{
	sf::Clock clock;

	// below are hard-coded values for testing until ConfigEngine can provide settings
	const unsigned int captureDuration = 5; // capture duration (in seconds)
	const float frameInterval = 1 / 15; // 15 FPS
	const unsigned long framesLength = captureDuration * 15; // time * FPS

	unsigned long frameNum = 0; // current frame

	while(frameNum < framesLength)
	{
		float elapsedTime = clock.getElapsedTime().asSeconds();
		bool frameCaptured = false;

		if(elapsedTime >= frameInterval || frameNum == 0)
		{
			clock.restart();
			m_GIF.AddFrame(m_Grabber.Grab(m_Picker->GetRect()));
			frameCaptured = true;
		}

		if(frameCaptured)
		{
			frameNum++;
			clock.restart();
		}
	}
}

bool EzApp::ScreenshotGIF::Save(std::string filename)
{
	return m_GIF.SaveFile(filename.c_str());
}
