#include "../screenshot.hpp"

#define EzApp EasyGIF::App
#define EzUI EasyGIF::UI

void EzApp::ScreenshotStatic::GetData()
{
	std::cout << m_Picker->GetRect().x << std::endl;
	std::cout << m_Picker->GetRect().y << std::endl;
	std::cout << m_Picker->GetRect().width << std::endl;
	std::cout << m_Picker->GetRect().height << std::endl;
	m_Frame = m_Grabber.Grab(m_Picker->GetRect());
	m_Saver.LoadData(m_Frame);
}

bool EzApp::ScreenshotStatic::Save(std::string filename)
{
	return m_Saver.Save(filename);
}
