#include "net/gyazo.hpp"
#include <iostream>
#include <string>
int main(int argc,char *argv[]){
	//std::cout<<"IT WORKED AHMAGAWD"<<std::endl;
	EasyGIF::Uploaders::Gyazo gyazo;
	std::cout<<gyazo.GetUserAgent()<<std::endl;
	struct EasyGIF::Uploaders::ImageUpload to_upload;
	to_upload.proxy_settings="http://localhost:8000";
	to_upload.file_path="dc.png";
	to_upload.file_name="davidcameronontoast";
	struct EasyGIF::Uploaders::CompletedImageUpload up;
	up=gyazo.uploadFile(to_upload);
	std::cout<<up.successful<<std::endl;
	std::cout<<up.hex_digest<<std::endl;
	return 0;
}
