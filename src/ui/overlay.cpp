#include "overlay.hpp"
#include <iostream>

using namespace EasyGIF::UI;

// Big thanks to user.dz for their answer here http://stackoverflow.com/questions/21780789/x11-draw-on-overlay-window
// A huge portion of the code below has been based on theirs.

Overlay::Overlay()
{
	this->Init();
}

void Overlay::Init()
{
	m_Display = XOpenDisplay(nullptr);

	m_Screen = DefaultScreen(m_Display);
	m_RootWnd = RootWindow(m_Display, m_Screen);

	/*XCompositeRedirectSubwindows(m_Display, m_RootWnd, CompositeRedirectAutomatic);
	XSelectInput(m_Display, m_RootWnd, SubstructureNotifyMask);*/

	m_Width = DisplayWidth(m_Display, m_Screen);
	m_Height = DisplayHeight(m_Display, m_Screen);

	//m_Overlay = XCompositeGetOverlayWindow(m_Display, m_RootWnd);

	/*XserverRegion region = XFixesCreateRegion(m_Display, nullptr, 0);
	XFixesSetWindowShapeRegion(m_Display, m_Overlay, ShapeBounding, 0, 0, 0);
	XFixesSetWindowShapeRegion(m_Display, m_Overlay, ShapeInput, 0, 0, region);
	XFixesDestroyRegion(m_Display, region);*/

	m_Surface = cairo_xlib_surface_create(m_Display, m_RootWnd, DefaultVisual(m_Display, m_Screen), m_Width, m_Height);
	m_Context = cairo_create(m_Surface);
	XSelectInput(m_Display, m_RootWnd, ExposureMask);
}

void Overlay::Draw()
{
	// Not implemented
	// Yeah, I do realise this should be a pure virtual function.
	return;
}

void Overlay::Display()
{
	//m_Overlay = XCompositeGetOverlayWindow(m_Display, m_RootWnd);
	std::cout << "OverlayWnd: " << m_Overlay << std::endl << "RootWnd: " << m_RootWnd << std::endl;
	this->Draw();
	//XCompositeReleaseOverlayWindow(m_Display, m_RootWnd);
}

void Overlay::Shutdown()
{
	cairo_destroy(m_Context);
	cairo_surface_destroy(m_Surface);
	XCloseDisplay(m_Display);
}

Overlay::~Overlay()
{
	this->Shutdown();
}
