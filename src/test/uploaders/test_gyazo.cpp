#include "../../../src/net/uploaders/gyazo.hpp"
#include <iostream>
#include <string>
using namespace std;
int main(){
  //the path is relative to however you're calling it
  //in the makefile it is being called from the root path in the repository
  std::string test_image_file="./build/bin/testimg.png";
  cout<<"Gyazo build successful, starting to upload"<<endl;

  //This calls the global curl init method
  //I'm assuming libcurl needs it but I haven't tried without doing this
  EasyGIF::Uploaders::CURL_init();
  cout<<"EasyGIF::Uploaders::CURL_init() successful"<<endl;

  cout<<"Testing can connect methods"<<endl;
  bool can_connect=EasyGIF::Uploaders::CanConnectToGyazo();
  cout<<"Can connect = "<<can_connect<<endl;

  //GyazoCompletedUpload contains the original request settings and some curl response info, still working on
  struct EasyGIF::Uploaders::Gyazo::GyazoCompletedUpload res;
  cout<<"Created EasyGIF::Uploaders::Gyazo::GyazoCompletedUpload struct"<<endl;
  //PRINTING URL WITHIN THIS METHOD
  int res2=EasyGIF::Uploaders::UploadFileToGyazo(test_image_file,&res);
  cout<<"Calculated md5 digest: "<<res.md5_digest<<endl;
  cout<<"Gyazo page url: "<<res.page_url<<endl;
  cout<<"Gyazo image url: "<<res.image_url<<endl;

  //Calls the libcurl global cleanup, make sure to cleanup your individual curl stuff
  EasyGIF::Uploaders::CURL_cleanup();
  cout<<"EasyGIF::Uploaders::CURL_cleanup() successful, exiting test now"<<endl;
  return 0;
}
