#ifndef GYAZO_H
#define GYAZO_H
#include "image_upload.hpp"
#include <string>
#include <vector>
#include <curl/curl.h>
#include "../sec/md5.hpp"
#include <cstdlib>
#include "create_header.hpp"
namespace EasyGIF{
	namespace Uploaders{
		namespace Gyazo{
			struct GyazoUploadSettings{
				EasyGIF::Uploaders::CurlUploadSettings upload_settings;
				std::string gyazo_id;
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
				public:
					//gyazo id,proxy settings,user agent
					GyazoImageUploader();
					GyazoImageUploader(std::string gid,std::string prx,std::string ua);
					std::string GetGyazoID();
					GyazoImageUploader* SetGyazoID(std::string new_id);
					GyazoImageUploader* SetGyazoID(std::string new_id,bool parse);
					int UploadFile(GyazoUploadSettings upload_settings,GyazoCompletedUpload* uploaded_info);
			};
			std::string GetRandomID(int);
			std::string ParseGID(std::string);
			#ifdef IMAGE_SPLIT_SETTINGS
				static bool DEFAULT_GYAZO_USE_HTTPS=true;
				static std::string DEFAULT_GYAZO_AGENT="";
				static std::string DEFAULT_GYAZO_PROXY="";
			#endif
			//void SetUploadSettings(GyazoUploadSettings* upload_settings,std::string file_path,std::string file_name,std::string extension,)
		}
	}
}
#endif
