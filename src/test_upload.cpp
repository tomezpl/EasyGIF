#include "net/gyazo.hpp"
#include <iostream>
#include <string>
using namespace std;
int main(int argc,char *argv[]){
	//std::cout<<"IT WORKED AHMAGAWD"<<std::endl;
	EasyGIF::Uploaders::GyazoCompletedUpload ciu;
	cout<<"Uploading dc.png to Gyazo"<<endl;
	EasyGIF::Uploaders::UploadFileToGyazo(&ciu,"dc.png",true);
	cout<<"Upload process complete"<<endl;
	cout<<"Upload URL = "<<ciu.upload_url<<endl;
	cout<<"Upload file = "<<ciu.upload_file<<endl;
	cout<<"Upload filename = "<<ciu.upload_filename<<endl;
	cout<<"Upload GID = "<<ciu.gyazo_id<<endl;
	cout<<"Upload User Agent = "<<ciu.user_agent<<endl;
	cout<<"Upload proxy settings = "<<ciu.proxy_settings<<endl;
	cout<<"Upload MD5 Digest = "<<ciu.md5_digest<<endl;
	cout<<"Upload Successful = "<<ciu.curl_successful<<endl;
	if(!ciu.curl_successful){
		cout<<"CURL strerror"<<endl;
		curl_easy_strerror(ciu.curl_response);
	}
	return 0;
}
