#ifndef GYAZO_H
#define GYAZO_H
#include "image_upload.hpp"
#include <string>
#include <vector>
#include <curl/curl.h>
#include <cstdlib>
#include "../create_header.hpp"
namespace EasyGIF{
	namespace Uploaders{
		namespace Gyazo{
			#ifdef IMAGE_SPLIT_SETTINGS
				namespace Values{
					static bool DEFAULT_GYAZO_USE_HTTPS=true;
					static std::string DEFAULT_GYAZO_AGENT="";
					static std::string DEFAULT_GYAZO_PROXY="";
				}
			#endif
			std::string GetUploadURL(bool use_https);
			std::string GetUploadURL();
			std::string GetMD5Page(bool use_https,std::string md5_digest);
			std::string GetMD5Page(std::string md5_digest);
			std::string GetImagePage(std::string md5_digest,std::string file_extension,bool https);
			std::string GetImagePage(bool use_https);
			std::string GetImageIndexPage(bool use_https);
			std::string GetIndexPage(bool use_https);
			std::string GetIndexPage();
			std::string GetDefaultUserAgent();
			std::string GetDefaultProxySettings();
			bool GetDefaultUseHTTPS();
			struct GyazoUploadSettings{
				EasyGIF::Uploaders::CurlUploadSettings upload_settings;
				std::string gyazo_id;
				bool use_https;
			};
			struct GyazoCompletedUpload{
				std::string md5_digest;
				std::string page_url;
				std::string image_url;
				EasyGIF::Uploaders::Gyazo::GyazoUploadSettings upload_settings;
				bool upload_successful;
				CURLcode curl_response;
			};
			class GyazoImageUploader : public ImageUploader{
				private:
					std::string gyazo_id;
					bool use_https;
					GyazoCompletedUpload* last_upload_info;
				public:
					//gyazo id,proxy settings,user agent
					GyazoImageUploader();
					GyazoImageUploader(std::string gid,std::string prx,std::string ua);
					GyazoImageUploader(std::string gyazo_id,std::string proxy_settings,std::string user_agent,bool use_https);
					std::string GetGyazoID();
					bool GetUseHTTPS();
					GyazoImageUploader* SetGyazoID(std::string new_id);
					GyazoImageUploader* SetGyazoID(std::string new_id,bool parse);
					GyazoImageUploader* SetUseHTTPS(bool use_https);
					GyazoCompletedUpload* GetLastUpload();
					int UploadFile(GyazoUploadSettings upload_settings,GyazoCompletedUpload* uploaded_info);
					int UploadFile(std::string file,GyazoCompletedUpload* uploaded_info);
					int UploadFile(std::string file);
			};
			std::string GetRandomID(int);
			std::string ParseGID(std::string);

			//void SetUploadSettings(GyazoUploadSettings* upload_settings,std::string file_path,std::string file_name,std::string extension,)
		}
		int UploadFileToGyazo(std::string file,EasyGIF::Uploaders::Gyazo::GyazoCompletedUpload* result);
		EasyGIF::Uploaders::Gyazo::GyazoCompletedUpload* UploadFileToGyazo(std::string file);
		//Bool parameters = https
		bool CanConnectToGyazo(bool use_https);
		bool CanConnectToGyazo(bool use_https,std::string);
		bool CanConnectToGyazo();
	}
}
#endif
