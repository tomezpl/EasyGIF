#include "../../net/uploaders/imgur_anon.hpp"
#include <iostream>
#include <string>
using namespace std;
namespace imgur=EasyGIF::Uploaders::Imgur;
int main(){
  cout<<"Imgur upload test. Successfully built."<<endl;
  std::string tempfile=EasyGIF::IO::getTempFile();
  cout<<"Created temporary file "<<tempfile<<endl;
  bool exists=EasyGIF::IO::fileExists(tempfile);
  cout<<(exists?"Temporary file exists":"Temporary file does not exist")<<endl;
  if(exists){
    cout<<"Testing removal of "<<tempfile<<endl;
    bool success=EasyGIF::IO::deleteFile(tempfile);
    cout<<(success?"Deleted successfully":"Returned non zero, failed to delete tempfile")<<endl;
    cout<<"Testing exists"<<endl;
    cout<<tempfile<<" exists = "<<EasyGIF::IO::fileExists(tempfile)<<endl;
  }
  cout<<"Testing Imgur Upload"<<endl<<endl;
  cout<<"Enter Imgur Client ID: ";
  string client_id;
  getline(cin,client_id);
  string file_path;
  cout<<"Enter file path to upload: ";
  getline(cin,file_path);
  string filename;
  cout<<"Enter filename: ";
  getline(cin,filename);
  struct imgur::ImgurUploadSettings upl_settings;
  imgur::SetUploadSettings(&upl_settings,client_id,file_path,filename);
  cout<<"Set Upload Settings, beginning upload"<<endl;
  struct imgur::ImgurCompletedUpload upl_completed;
  int upl_res=imgur::UploadAnonImage(upl_settings,&upl_completed);
  cout<<"Upload response = "<<upl_res<<endl;
  if(upl_res==0){
    cout<<"No errors while uploading..."<<endl;
    cout<<"Imgur response success: "<<upl_completed.success<<endl;
    cout<<"Imgur response status: "<<upl_completed.status_code<<endl;
    if(upl_completed.success){
      cout<<"Imgur Upload ID: "<<upl_completed.upload_id<<endl;
      cout<<"Imgur Upload URL: https://imgur.com/"<<upl_completed.upload_id<<endl;
    }else{
      cout<<"Failed to upload image to imgur"<<endl;
    }
  }
  EasyGIF::Uploaders::CURL_cleanup();
  cout<<"CURL cleaned up"<<endl;
  cout<<"End of testing..."<<endl;
  return 0;
}
