#include "../../net/uploaders/imgur_anon.hpp"
#include <iostream>
#include <string>
using namespace std;
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
  cout<<"Testing Imgur Upload"<<endl;
  
  cout<<"End of testing..."<<endl;
  return 0;
}
