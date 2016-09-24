#include "conncheck.hpp"
namespace EasyGIF{
  namespace Uploaders{
    size_t rm_response(void *buffer,size_t size,size_t nmemb,void *userp){return size*nmemb;}
    bool TestGET(const char* url,CURLcode *res){
      CURL *curl;
      curl=curl_easy_init();
      if(curl){
          curl_easy_setopt(curl,CURLOPT_URL,url);
          //This prevents the response from being written to stdout
          curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,rm_response);
          (*res)=curl_easy_perform(curl);
          return (*res)==CURLE_OK;
      }
      curl_easy_cleanup(curl);
      return false;
    }
    bool TestGET(const char* url){CURLcode res;return TestGET(url,&res);}
    bool TestGET(std::string url,CURLcode *res){return TestGET(url.c_str(),res);}
    bool TestGET(std::string url){CURLcode res;return TestGET(url.c_str(),&res);}
    //This tests that CURL can Resolve the host and can connect to it
    bool TestConnect(std::string url){
      CURLcode res;
      return (!TestGET(url,&res))?CanResolveHost(res)&&CanConnect(res):true;
    }
    bool TestProxy(const char* url,const char* proxy){return false;}
    //Couldn't resolve proxy. The given proxy host could not be resolved.
    bool CanResolveProxy(CURLcode res){return res!=CURLE_COULDNT_RESOLVE_PROXY;}
    //Couldn't resolve host. The given remote host was not resolved.
    bool CanResolveHost(CURLcode res){return res!=CURLE_COULDNT_RESOLVE_HOST;}
    //Failed to connect() to host or proxy
    bool CanConnect(CURLcode res){return res!=CURLE_COULDNT_CONNECT;}
  }
}
