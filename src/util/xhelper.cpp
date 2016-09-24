// xhelper.cpp
// Author: Tomasz Zajac

#include "xhelper.hpp"

using namespace EasyGIF::Utility;

XHelper::XHelper(xcb_connection_t** connection)
{
	m_XConn = connection;
}

Rectangle XHelper::GetRect(xcb_window_t window)
{
	Rectangle ret = {0, 0, 0, 0};

	xcb_get_geometry_cookie_t cookie;
	xcb_get_geometry_reply_t* reply;

	cookie = xcb_get_geometry(*m_XConn, window);
	reply = xcb_get_geometry_reply(*m_XConn, cookie, nullptr);

	if(reply)
	{
		ret.x = reply->x;
		ret.y = reply->y;
		ret.width = reply->width;
		ret.height = reply->height;
	}
	free(reply);

	return ret;
}

XHelper::~XHelper()
{
	delete m_XConn;
}
