#ifndef GYAZO_H
#define GYAZO_H
#include <string>
#include <vector>
#include <curl/curl.h>
#include "image_upload.hpp"
#include "../sec/md5.hpp"
namespace EasyGIF{
	namespace Uploaders{
		void CURL_init();
		void CURL_cleanup();
		class Gyazo{
			private:
				std::string upload_url;
				std::string user_agent;
				//Blank proxy settings mean that no proxy will be used
				std::string proxy_settings;
			public:
				Gyazo();
				Gyazo(std::string,std::string,std::string);
				bool UsingProxy();
				std::string GetProxy();
				std::string GetUserAgent();
				std::string GetUploadURL();
				void SetProxy(std::string);
				void SetUserAgent(std::string);
				void SetUploadURL(std::string);
				void UseHTTPS(bool);
				void initCurl(CURL*,bool,std::string,std::string,std::string);
				void createUploadForm(curl_httppost*,curl_httppost*,std::string,std::string,std::string);
				CompletedImageUpload uploadFile(ImageUpload);
		};
	}
}
#endif
