#include "../net/gyazo.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;
int main(){
  EasyGIF::Uploaders::CURL_init();
  //Change this to whatever path you desire
  std::string file_to_upload="shrek.jpg";
  cout<<"Performing image upload tests for \""<<file_to_upload<<"\""<<endl;
  EasyGIF::Uploaders::Gyazo::GyazoImageUploader uploader;
  EasyGIF::Uploaders::Gyazo::GyazoUploadSettings upload_settings;
  upload_settings.upload_settings.upload_url="http://gyazo.com/upload.cgi";
  upload_settings.upload_settings.upload_file=file_to_upload;
  upload_settings.upload_settings.upload_filename="";
  upload_settings.upload_settings.upload_extension=".jpg";
  upload_settings.upload_settings.user_agent="Mozilla/420";
  upload_settings.upload_settings.proxy_settings="";
  upload_settings.upload_settings.using_https=true;
  upload_settings.gyazo_id=EasyGIF::Uploaders::Gyazo::GetRandomID(32);
  struct EasyGIF::Uploaders::Gyazo::GyazoCompletedUpload upload_response;
  int res=uploader.UploadFile(upload_settings,&upload_response);
  cout<<"Upload Response = "<<res<<endl;
  cout<<(upload_response.upload_successful?"Upload was successful":"Upload failed")<<endl;
  if(upload_response.upload_successful){
    cout<<"Image Digest = "<<upload_response.md5_digest<<endl;
    cout<<"Page URL = "<<upload_response.page_url<<endl;
    cout<<"Image URL = "<<upload_response.image_url<<endl;
  }
  EasyGIF::Uploaders::CURL_cleanup();
  return 0;
}
