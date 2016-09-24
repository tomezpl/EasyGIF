#include "image_upload.hpp"
namespace EasyGIF{
  namespace Uploaders{
    void CURL_init(){curl_global_init(CURL_GLOBAL_ALL);Values::CURL_INITIALISED=true;}
		void CURL_cleanup(){curl_global_cleanup();Values::CURL_CLEANEDUP=true;}
    bool CanConnectToGyazo(bool https){return TestGET(https?"https://gyazo.com":"http://gyazo.com");}
    bool CanConnectToGyazo(){return CanConnectToGyazo(true);}
    bool CanConnectToGyazo(bool https,std::string proxy){return TestProxy(https?"https://gyazo.com":"http://gyazo.com",proxy.c_str());}
    ImageUploader::ImageUploader(std::string url,std::string hostname,std::string proxy,std::string useragent,bool supports_gif,bool supports_still){
      this->upload_url=url;
      this->host_name=hostname;
      this->proxy_settings=proxy;
      this->user_agent=useragent;
      this->supports_gif_file=supports_gif;
      this->supports_still_file=supports_still;
    }
    //ImageUploader Methods
    std::string ImageUploader::GetUploadURL(){return this->upload_url;}
    std::string ImageUploader::GetHostname(){return this->host_name;}
    std::string ImageUploader::GetProxySettings(){return this->proxy_settings;}
    std::string ImageUploader::GetUserAgent(){return this->user_agent;}
    ImageUploader* ImageUploader::SetUploadURL(std::string new_url){this->upload_url=new_url;return this;}
    ImageUploader* ImageUploader::SetHostname(std::string new_hostname){this->host_name=new_hostname;return this;}
    ImageUploader* ImageUploader::SetProxySettings(std::string new_proxy){this->proxy_settings=new_proxy;return this;}
    ImageUploader* ImageUploader::SetUserAgent(std::string new_agent){this->user_agent=new_agent;return this;}
  }
}
