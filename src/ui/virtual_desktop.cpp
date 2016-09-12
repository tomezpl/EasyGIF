// virtual_desktop.cpp
// Author: Tomasz Zajac

#include "virtual_desktop.hpp"

using namespace EasyGIF::UI;

VirtualDesktop::VirtualDesktop(char* display) : ImageGrabber(display)
{
	xcb_query_tree_cookie_t cookie;
	xcb_query_tree_reply_t* reply;

	cookie = xcb_query_tree(m_XConnection, m_XWindow);
	reply = xcb_query_tree_reply(m_XConnection, cookie, nullptr);
	if(reply)
	{
		m_Windows = xcb_query_tree_children(reply);
		for(unsigned short i = 0; i < xcb_query_tree_children_length(reply); i++)
		{
			xcb_get_property_cookie_t propertyCookie;
			xcb_get_property_reply_t* propertyReply;
			xcb_atom_t property = XCB_ATOM_WM_NAME;
			xcb_atom_t type = XCB_ATOM_STRING;
			propertyCookie = xcb_get_property(m_XConnection, false, m_Windows[i], property, type, 0, 0);
			propertyReply = xcb_get_property_reply(m_XConnection, propertyCookie, nullptr);
			if(propertyReply)
			{
				int len = xcb_get_property_value_length(propertyReply);
				std::cout << i << ": ";
				if(len == 0)
				{
					std::cout << "NULL LENGTH" << std::endl;
					free(propertyReply);
					continue;
				}
				std::cout << "Found window \"" << (char*)xcb_get_property_value(propertyReply) << "\"" << std::endl;
			}
			free(propertyReply);
		}
	}
	free(reply);
}

VirtualDesktop::~VirtualDesktop()
{

}
