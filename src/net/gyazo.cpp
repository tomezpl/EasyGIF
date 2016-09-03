#include "gyazo.hpp"
namespace EasyGIF{
	namespace Uploaders{
		void CURL_init(){curl_global_init(CURL_GLOBAL_ALL);}
		void CURL_cleanup(){curl_global_cleanup();}
		Gyazo::Gyazo(){
			this->upload_url="https://gyazo.com/upload.cgi";
			this->user_agent="Mozilla/420";
			this->proxy_settings="";
		}
		Gyazo::Gyazo(std::string upload_url,std::string user_agent,std::string proxy_settings){
			this->upload_url=upload_url;
			this->user_agent=user_agent;
			this->proxy_settings=proxy_settings;
		}
		//Getters+Setters
		bool Gyazo::UsingProxy(){return !proxy_settings.empty();}
		std::string Gyazo::GetProxy(){return proxy_settings;}
		std::string Gyazo::GetUserAgent(){return user_agent;}
		std::string Gyazo::GetUploadURL(){return upload_url;}
		void Gyazo::SetProxy(std::string proxy_settings){this->proxy_settings=proxy_settings;}
		void Gyazo::SetUserAgent(std::string user_agent){this->user_agent=user_agent;}
		void Gyazo::SetUploadURL(std::string upload_url){this->upload_url=upload_url;}
		void Gyazo::UseHTTPS(bool yeno){upload_url=(yeno)?"https://gyazo.com/upload.cgi":"http://gyazo.com/upload.cgi";}
		void Gyazo::createUploadForm(curl_httppost* post,curl_httppost* last,std::string id,std::string file_path,std::string custom_filename){
			curl_formadd(&post,&last,CURLFORM_COPYNAME,"id",CURLFORM_PTRCONTENTS,id.c_str(),CURLFORM_END);
			if(custom_filename.empty()){
				curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,file_path.c_str(),CURLFORM_CONTENTTYPE,"image/*",CURLFORM_END);
			}else{
				curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,file_path.c_str(),CURLFORM_CONTENTTYPE,"image/*",CURLFORM_FILENAME,custom_filename.c_str(),CURLFORM_END);
			}
		}
		//Upload
		CompletedImageUpload Gyazo::uploadFile(ImageUpload image_data){
			struct CompletedImageUpload uploaded;
			uploaded.hex_digest=EasyGIF::Hashing::GetFileMD5(image_data.file_path);
			uploaded.upload_data=image_data;
			//INIT CURL
			CURL *curl;
			curl=curl_easy_init();
			//Set verbose
			curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
			//Set Proxy Settings
			//if(!image_data.proxy_settings.empty()){curl_easy_setopt(curl,CURLOPT_PROXY,"http://localhost:8000");}
			//Set upload url
			curl_easy_setopt(curl,CURLOPT_URL,"https://gyazo.com/upload.cgi");
			//Set custom Headers
			struct curl_slist *list=NULL;
			std::string uag="User-Agent: "+user_agent;
			list=curl_slist_append(list,uag.c_str());
			list=curl_slist_append(list,"Expect: ");
			list=curl_slist_append(list,"Connection: close");
			curl_easy_setopt(curl,CURLOPT_HTTPHEADER,list);
			//initCurl(curl,true,this->upload_url,image_data.user_agent,image_data.proxy_settings);
			//Create forms
			struct curl_httppost* post=NULL;
			struct curl_httppost* last=NULL;
			//Form creation
			char random_id[]="12345678912345678912345678912345";
			curl_formadd(&post,&last,CURLFORM_COPYNAME,"id",CURLFORM_PTRCONTENTS,random_id,CURLFORM_END);
			if(image_data.file_name.empty()){curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,image_data.file_path.c_str(),CURLFORM_CONTENTTYPE,"image/*",CURLFORM_END);}
			else{curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,image_data.file_path.c_str(),CURLFORM_CONTENTTYPE,"image/*",CURLFORM_FILENAME,image_data.file_name.c_str(),CURLFORM_END);}
			curl_easy_setopt(curl,CURLOPT_HTTPPOST,post);
			CURLcode res=curl_easy_perform(curl);
			curl_easy_strerror(res);
			uploaded.successful=(res==CURLE_OK);
			uploaded.response=res;
			curl_easy_cleanup(curl);
			return uploaded;
		}
	}
}
