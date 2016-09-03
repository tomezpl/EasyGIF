#ifndef IMAGE_UPLOAD_H
#define IMAGE_UPLOAD_H
#include <string>
#include <curl/curl.h>
namespace EasyGIF{
	namespace Uploaders{
		struct ImageUpload{
			std::string file_path;
			std::string file_name;
			std::string proxy_settings;
			std::string user_agent;
		};
		struct CompletedImageUpload{
			ImageUpload upload_data;
			std::string hex_digest;
			bool successful;
			CURLcode response;
		};
	}
}
#endif
