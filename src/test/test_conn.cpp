#include "../net/image_upload.hpp"
#include <iostream>
#include <curl/curl.h>
using namespace std;
int main(){
  EasyGIF::Uploaders::CURL_init();
  CURLcode res;
  std::string url="https://gyazo.com";
  bool success=EasyGIF::Uploaders::TestGET(url.c_str(),&res);
  if(success){
    cout<<"Request was successful"<<endl;
  }else{
    cout<<"Request was unsuccessful"<<endl;
  }
  //cout<<res<<endl;
  EasyGIF::Uploaders::CURL_cleanup();
  return 0;
}
