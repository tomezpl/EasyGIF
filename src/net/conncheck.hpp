#ifndef CONNCHECK_H
#define CONNCHECK_H
#include <curl/curl.h>
#include <string>
namespace EasyGIF{
  namespace Uploaders{
    bool TestGET(const char*,CURLcode*);
    bool TestGET(const char*);
    bool TestGET(std::string,CURLcode*);
    bool TestGET(std::string);
    bool TestConnect(const char*,CURLcode*);
    bool TestConnect(const char*);
    bool TestProxy(const char*,const char*,CURLcode*);
    bool TestProxy(const char*,const char*);
    //Couldn't resolve proxy. The given proxy host could not be resolved.
    bool CanResolveProxy(CURLcode);
    //Couldn't resolve host. The given remote host was not resolved.
    bool CanResolveHost(CURLcode);
    //Failed to connect() to host or proxy
    bool CanConnect(CURLcode);
  }
}
#endif
