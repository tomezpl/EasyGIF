#include <iostream>
#include "../net/uploaders/gyazo.hpp"
using namespace std;
int main(int argc,char *argv[]){
  //This assumes that the program path is passed as an argument
  //Which on my systems, it does
  EasyGIF::Uploaders::CURL_init();
  if(argc<2){
    cout<<"Usage: "<<argv[0]<<" <filename> <filename2> <filename3 etc...>"<<endl;
  }else{
    for(int i=1;i<argc;i++){
      cout<<"Testing Gyazo upload with \""<<argv[i]<<"\""<<endl;
      struct EasyGIF::Uploaders::Gyazo::GyazoCompletedUpload res;
      int res2=EasyGIF::Uploaders::UploadFileToGyazo(argv[i],&res);
      cout<<"\tUpload response: "<<res2<<endl<<"\tURL: "<<res.page_url<<endl;
    }
  }
  EasyGIF::Uploaders::CURL_cleanup();
  return 0;
}
