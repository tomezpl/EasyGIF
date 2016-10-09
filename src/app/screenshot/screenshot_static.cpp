#include "../screenshot.hpp"

#define EzApp EasyGIF::App
#define EzUI EasyGIF::UI

void EzApp::ScreenshotStatic::GetData()
{
	m_Frame = m_Grabber.Grab(m_Picker->GetRect());
	m_Saver.LoadData(m_Frame);
}

bool EzApp::ScreenshotStatic::Save(std::string filename)
{
	return m_Saver.Save(filename);
}
