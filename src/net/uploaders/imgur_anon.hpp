#ifndef IMGUR_ANON_H
#define IMGUR_ANON_H
#include <stdio.h>
#include "image_upload.hpp"
#include "../create_header.hpp"
#include "../../json.hpp"
#include "../filestuff.hpp"
#ifdef IMAGE_SPLIT_SETTINGS
  #define DEFAULT_IMGUR_ANON_USE_HTTPS 1
  #define DEFAULT_IMGUR_ANON_PROXY ""
  #define DEFAULT_IMGUR_ANON_AGENT ""
#endif
namepsace EasyGIF{
  namespace Uploaders{
    namespace Imgur{
      int UploadAnonImage(ImgurUploadSettings upload_settings,ImgurCompletedUpload* completed);
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
    }
  }
}
#endif
