#ifndef IMAGE_UPLOAD_H
#define IMAGE_UPLOAD_H
#include <string>
#include <curl/curl.h>
namespace EasyGIF{
	namespace Uploaders{
		struct GyazoCompletedUpload{
			std::string upload_url;
			std::string upload_file;
			std::string upload_filename;
			std::string gyazo_id;
			std::string user_agent;
			std::string proxy_settings;
			std::string md5_digest;
			bool curl_successful;
			CURLcode curl_response;
		};
	}
}
#endif
