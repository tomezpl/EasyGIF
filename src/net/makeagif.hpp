#ifndef MAKEAGIF_H
#define MAKEAGIF_H
#include "image_upload.hpp"
#include <string>
#include <vector>
#include <curl/curl.h>
#include "../sec/b64.hpp"
namespace EasyGIF{
	namespace Uploaders{
		class MakeaGif{
			private:
				std::string def_upload_url;
				std::string def_user_agent;
				std::string def_proxy_settings;
				int def_category;
				int def_delay;
				bool def_nsfw;
				bool def_resize;
				std::string def_title;

		}
	}
}
#endif
