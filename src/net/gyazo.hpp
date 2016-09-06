#ifndef GYAZO_H
#define GYAZO_H
#include "image_upload.hpp"
#include <string>
#include <vector>
#include <curl/curl.h>
#include "../sec/md5.hpp"
#include <cstdlib>
namespace EasyGIF{
	namespace Uploaders{
		void UploadFileToGyazo(GyazoCompletedUpload*,std::string);
		void UploadFileToGyazo(GyazoCompletedUpload*,std::string,bool);
		void CURL_init();
		void CURL_cleanup();
		class Gyazo{
			private:
				std::string upload_url;
				std::string user_agent;
				//Blank proxy settings mean that no proxy will be used
				std::string proxy_settings;
				std::string gyazo_id;
				bool verbose;
			public:
				Gyazo();
				Gyazo(std::string,std::string,std::string,std::string,bool);
				bool UsingProxy();
				std::string GetProxy();
				std::string GetUserAgent();
				std::string GetUploadURL();
				std::string GetID();
				bool GetVerbose();
				void SetProxy(std::string);
				void SetUserAgent(std::string);
				void SetUploadURL(std::string);
				void SetID(std::string);
				void SetVerbose(bool);
				void UseHTTPS(bool);
				std::string GetRandomID(int);
				std::string ParseGID(std::string);
				void UploadFile(GyazoCompletedUpload*,std::string,std::string,std::string,std::string,std::string,std::string,bool,bool);
				void UploadFile(GyazoCompletedUpload*,std::string);
		};
	}
}
#endif
