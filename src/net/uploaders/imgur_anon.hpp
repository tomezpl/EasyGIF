#ifndef IMGUR_ANON_H
#define IMGUR_ANON_H
#include "image_upload.hpp"
#include <stdio.h>
#include "../create_header.hpp"
#include "../../json.hpp"
#include "../filestuff.hpp"
#include <string>
namespace EasyGIF{
  namespace Uploaders{
    namespace Imgur{
      //Imgur API endpoints are all accessed via HTTPS
      //Image Uploader constructor methods
      std::string GetDefaultUploadURL();
      std::string GetDefaultHostname();
      std::string GetDefaultAnonHostname();
      std::string GetDefaultAnonProxy();
      std::string GetDefaultAnonUserAgent();
      bool GetDefaultAnonUseHTTPS();

      #ifdef IMAGE_SPLIT_SETTINGS
      namespace AnonValues{
        const std::string DEFAULT_IMGUR_ANON_PROXY="";
        const std::string DEFAULT_IMGUR_ANON_AGENT="EasyGIF/Imgur";
      }
      #endif
      struct ImgurUploadSettings{
        EasyGIF::Uploaders::CurlUploadSettings upload_settings;
        std::string client_id;
        //All are optional
        std::string album_id;
        std::string upload_type; //for now will just be "file"
        std::string name;
        std::string title;
        std::string description;
      };
      void SetUploadSettings(ImgurUploadSettings* upload_settings,std::string client_id,std::string upload_file,std::string filename);
      struct ImgurCompletedUpload{
        //data
        std::string upload_id;
        std::string title;
        std::string description;
        unsigned long datetime;
        std::string type;
        bool animated;
        int width;
        int height;
        unsigned long size;
        int views;
        int bandwidth;
        std::string vote;
        bool favourite;
        std::string nsfw;
        std::string section;
        std::string account_url;
        unsigned long account_id;
        bool is_ad;
        bool in_gallery;
        std::string delete_hash;
        std::string name;
        std::string link;
        //other
        bool success;
        int status_code;
        ImgurUploadSettings upload_settings;
      };
      int UploadAnonImage(ImgurUploadSettings upload_settings,ImgurCompletedUpload* completed);
      class ImgurAnonUploader : public ImageUploader{
        private:
          std::string client_id;
          //I think that all calls to the Imgur api must be done over HTTPS, will check at some point
          //bool use_https;
          ImgurCompletedUpload* last_upload_info;
        public:
          ImgurAnonUploader();
          ~ImgurAnonUploader();
          ImgurAnonUploader(std::string client_id);
          ImgurAnonUploader(std::string client_id,std::string proxy_settings);
          ImgurAnonUploader(std::string client_id,std::string proxy_settings,std::string user_agent);
          ImgurCompletedUpload* GetLastUpload();
          //copies data from one to the other
          ImgurAnonUploader* SetLastUpload(ImgurCompletedUpload* last_upload);
          bool HasLastUpload();
          bool GetUseHTTPS();
      };
    }
  }
}
#endif
