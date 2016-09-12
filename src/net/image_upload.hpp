#ifndef IMAGE_UPLOAD_H
#define IMAGE_UPLOAD_H
//This allows for ImageUpload settings to be split from main defaults
//Meaning that each upload service can have its own default settings
#define IMAGE_SPLIT_SETTINGS
#include <string>
#include <curl/curl.h>
#include "../sec/md5.hpp"
#include "../sec/b64.hpp"
#include "conncheck.hpp"
namespace EasyGIF{
	namespace Uploaders{
		namespace Values{
			static bool CURL_INITIALISED=false;
			static bool CURL_CLEANEDUP=false;
			static bool DEFAULT_USE_HTTPS=true;
			static std::string DEFAULT_AGENT="Mozilla/420";
			static std::string DEFAULT_PROXY="";
			static int MULTIPART_FILE=0;
			static int MULTIPART_STRING=1;
			static int MULTIPART_NAME=2;
			static int MULTIPART_END=3;
		};
		void CURL_init();
		void CURL_cleanup();
		//Bool parameters = https
		bool CanConnectToGyazo(bool);
		bool CanConnectToGyazo(bool,std::string);
		bool CanConnectToGyazo();
		bool CanConnectToImgur(bool);
		bool CanConectToImgur();
		bool UploadFileToGyazo(std::string);
		bool UploadFileToImgur(std::string);
		struct MultipartData{
			int type;
			std::string value;
		};

		class MultipartCreator{
			private:
				struct curl_httppost* post;
				struct curl_httppost* last;
				std::vector<MultipartData> form_data;
			public:
				MultipartCreator();
				//Initialises vector to this size
				MultipartCreator(int expected);
		};

		class ImageUploader{
			protected:
					std::string upload_url;
					std::string host_name;
					std::string proxy_settings;
					std::string user_agent;
					bool supports_gif_file;
					bool supports_still_file;
			public:
				//upload url,host name,proxy settings,user agent
				ImageUploader(std::string url,std::string hostname,std::string proxy,std::string useragent,bool supports_gif,bool supports_still);
				//Getters and Setters
				std::string GetUploadURL();
				std::string GetHostname();
				std::string GetProxySettings();
				std::string GetUserAgent();
				bool UsingProxy();
				bool GetSupportsGIF();
				bool GetSupportsStill();
				ImageUploader* SetUploadURL(std::string);
				ImageUploader* SetHostname(std::string);
				ImageUploader* SetProxySettings(std::string);
				ImageUploader* SetUserAgent(std::string);
				/*
				//File,filename,custom_url,custom_proxy,custom_agent
				virtual int UploadFile(std::string,std::string,std::string,std::string,std::string)=0;
				//File,filename,custom_proxy,custom_agent
				virtual int UploadFile(std::string,std::string,std::string,std::string);
				//File,filename
				virtual int UploadFile(std::string,std::string);
				//File
				virtual int UploadFile(std::string);
				*/
		};
		struct CurlUploadSettings{
			std::string upload_url;
			std::string upload_file;
			std::string upload_extension;
			std::string upload_filename;
			std::string user_agent;
			std::string proxy_settings;
			bool using_https;
		};
		namespace Imgur{
			#ifdef IMAGE_SPLIT_SETTINGS
			static bool DEFAULT_IMGUR_USE_HTTPS=true;
			//If these strings are empty, they will use the main default settings
			static std::string DEFAULT_IMGUR_AGENT="";
			static std::string DEFAULT_GYAZO_PROXY="";
			#endif
		}
	}
}
#endif
