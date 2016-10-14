#include "../screenshot.hpp"

#define EzApp EasyGIF::App
#define EzUI EasyGIF::UI

EzApp::Screenshot::Screenshot()
{
	// create a new RegionPicker but do not activate yet
	m_Picker = new EzUI::RegionPicker(false);
}

void EzApp::Screenshot::RunUI()
{
	m_Picker->Activate();
	while(m_Picker->IsRunning() && !(m_Picker->IsConfirmed()))
	{
		m_Picker->ProcessInput();
		m_Picker->UpdateEvents();
		m_Picker->Draw();
	}

	if(m_Picker->IsConfirmed())
	{
		m_Picker->Shutdown();
		this->GetData();
	}
}

EzApp::Screenshot::~Screenshot()
{
	if(m_Picker->IsRunning())
		m_Picker->Shutdown();
	delete m_Picker;
}
