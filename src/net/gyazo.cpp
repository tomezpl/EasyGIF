#include "gyazo.hpp"
#include <iostream>
namespace EasyGIF{
	namespace Uploaders{
		//void UploadFileToGyazo(Gyazo::GyazoCompletedUpload *ptr,std::string file_path){Gyazo g;g.UploadFile(ptr,file_path);}
		//void UploadFileToGyazo(Gyazo::GyazoCompletedUpload *ptr,std::string file_path,bool verbose){Gyazo g;g.SetVerbose(verbose);g.UploadFile(ptr,file_path);}
		namespace Gyazo{
			std::string GetImagePage(std::string md5_digest,bool https){std::string start=https?"https://gyazo.com/":"http://gyazo.com";return start+md5_digest;}
			std::string GetRandomID(int len){
				static const char idalpha[]="0123456789abcdef"; //I believe it is only 32 hex digits, might not be. Don't think it matters
				char s[len+1];
				for(int i=0;i<len;i++){s[i]=idalpha[rand()%16];}
				s[len]=0;
				std::string s2(s);
				return s2;
			}
			std::string ParseGID(std::string gyid){
				if(gyid.length()==32){return gyid;}
				else if(gyid.length()>32){return gyid.substr(0,32);}
				else{return gyid+GetRandomID(32-gyid.length());}
			}
			//GyazoImageUploader Constructors
			#ifdef IMAGE_SPLIT_SETTINGS
				GyazoImageUploader::GyazoImageUploader() : ImageUploader(std::string(EasyGIF::Uploaders::Gyazo::DEFAULT_GYAZO_USE_HTTPS?"https://gyazo.com/upload.cgi":"http://gyazo.com/upload.cgi"),std::string("Gyazo"),EasyGIF::Uploaders::Gyazo::DEFAULT_GYAZO_PROXY.empty()?EasyGIF::Uploaders::Values::DEFAULT_PROXY:EasyGIF::Uploaders::Gyazo::DEFAULT_GYAZO_PROXY,EasyGIF::Uploaders::Gyazo::DEFAULT_GYAZO_AGENT.empty()?EasyGIF::Uploaders::Values::DEFAULT_AGENT:EasyGIF::Uploaders::Gyazo::DEFAULT_GYAZO_AGENT,true,true){this->gyazo_id=GetRandomID(32);}
			#else
				GyazoImageUploader::GyazoImageUploader() : ImageUploader(std::string(EasyGIF::Uploaders::Values::DEFAULT_USE_HTTPS?"https://gyazo.com/upload.cgi","http://gyazo.com/upload.cgi"),std::string("Gyazo"),EasyGIF::Uploaders::Values::DEFAULT_PROXY,EasyGIF::Uploaders::Values::DEFAULT_AGENT,true,true){this->gyazo_id=GetRandomID(32);}
			#endif
			//GyazoImageUploader::GyazoImageUploader(std::string gid,std::string prx,std::string uag) : ImageUploader(DEFAULT_GYAZO_USE_HTTPS?"https://gyazo.com/upload.cgi":"http://gyazo.com/upload.cgi","Gyazo",prx,uag){this->gyazo_id=ParseGID(gid);}
			GyazoImageUploader* GyazoImageUploader::SetGyazoID(std::string new_id,bool parse){this->gyazo_id=(parse)?ParseGID(new_id):new_id;return this;}
			GyazoImageUploader* GyazoImageUploader::SetGyazoID(std::string new_id){this->gyazo_id=ParseGID(new_id);return this;}

			//Gyazo Upload
			int GyazoImageUploader::UploadFile(GyazoUploadSettings upload_settings,GyazoCompletedUpload* uploaded_info){
				uploaded_info->upload_settings=upload_settings;
				uploaded_info->md5_digest=EasyGIF::Hashing::GetFileMD5(upload_settings.upload_settings.upload_file);
				std::string page_url=upload_settings.upload_settings.using_https?"https":"http";page_url+="://gyazo.com/"+uploaded_info->md5_digest;
				uploaded_info->page_url=page_url;
				std::string image_url=upload_settings.upload_settings.using_https?"https":"http";image_url+="://i.gyazo.com/"+uploaded_info->md5_digest+upload_settings.upload_settings.upload_extension;
				uploaded_info->image_url=image_url;
				CURL *curl;
				curl=curl_easy_init();
				if(curl){
					CURLcode res;
					curl_easy_setopt(curl,CURLOPT_URL,upload_settings.upload_settings.upload_url.c_str());
					if(!upload_settings.upload_settings.proxy_settings.empty()){curl_easy_setopt(curl,CURLOPT_PROXY,upload_settings.upload_settings.proxy_settings.c_str());}
					EasyGIF::Uploaders::HeaderCreator hedcreator;
					//curl_slist* headers=hedcreator.AddHeader("Expect","")->AddHeader("User-Agent",upload_settings.upload_settings.user_agent)->AddHeader("Connection","close")->GetHeaderList();
					curl_slist* headers=NULL;
					headers=curl_slist_append(headers,"Expect: ");
					curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
					struct curl_httppost* post=NULL;
					struct curl_httppost* last=NULL;
					curl_formadd(&post,&last,CURLFORM_COPYNAME,"id",CURLFORM_COPYCONTENTS,"bananaphones",CURLFORM_END);
					if(upload_settings.upload_settings.upload_filename.empty()){curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,upload_settings.upload_settings.upload_file.c_str(),CURLFORM_CONTENTTYPE,"image/*",CURLFORM_END);
					}else{curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,upload_settings.upload_settings.upload_file.c_str(),CURLFORM_CONTENTTYPE,"image/*",CURLFORM_FILENAME,upload_settings.upload_settings.upload_filename,CURLFORM_END);}
					curl_easy_setopt(curl,CURLOPT_HTTPPOST,post);
					res=curl_easy_perform(curl);
					uploaded_info->upload_successful=res==CURLE_OK;
					uploaded_info->curl_response=res;
					curl_easy_cleanup(curl);
					return (res==CURLE_OK)?1:0;
				}
				uploaded_info->upload_successful=false;
				return 2;
			}
		}
			/*
			//Upload
			//File Path
			//File Name (if empty, will not set)
			//Upload URL (if empty, will use class upload url)
			//Gyazo ID (if not 32 digits, will force)
			//User Agent (if empty, will use class user agent)
			//Proxy Settings (if empty, will use class proxy settings, if that's empty then will not set proxy)
			//Use Proxy (if passed proxy settings are empty then will not set proxy settings (if us_prx is false). Even if class is not blank)
			//Verbose, self-explanatory
			void Gyazo::UploadFile(GyazoCompletedUpload *gy_upload,std::string fp,std::string fn,std::string uurl,std::string gyid,std::string ua,std::string prx,bool us_prx,bool v){
				//Set CURL upload url
				const char* cuurl=gy_upload->upload_url.c_str();
				curl_easy_setopt(curl,CURLOPT_URL,cuurl);
				//Set CURL verbose mode
				if(v){curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);}
				//Set CURL proxy settings
				if(!gy_upload->proxy_settings.empty()){const char* cprx=gy_upload->proxy_settings.c_str();curl_easy_setopt(curl,CURLOPT_PROXY,cprx);}
				//Set CURL HTTP Headers
				struct curl_slist *cheads=NULL;
					//Set CURL User Agent
					std::string cfull_agent="User-Agent: "+gy_upload->user_agent;
					cheads=curl_slist_append(cheads,cfull_agent.c_str());
					//Set CURL Expect (to blank so it isn't used)
					cheads=curl_slist_append(cheads,"Expect: ");
					//Set CURL Connection to close, idk how to keep it alive
					cheads=curl_slist_append(cheads,"Connection: close");
				//Set CURL Header Values
				curl_easy_setopt(curl,CURLOPT_HTTPHEADER,cheads);
				//Create the Multipart forms
				struct curl_httppost* post=NULL;
				struct curl_httppost* last=NULL;
				const char* cgyid=gy_upload->gyazo_id.c_str();
				//Add ID part
				curl_formadd(&post,&last,CURLFORM_COPYNAME,"id",CURLFORM_COPYCONTENTS,cgyid,CURLFORM_END);
				//Add Image data part
				const char* cufp=fp.c_str();
				if(fn.empty()){
					curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,cufp,CURLFORM_CONTENTTYPE,"image/*",CURLFORM_END);
				}else{
					const char* cufn=fn.c_str();
					curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,cufp,CURLFORM_CONTENTTYPE,"image/*",CURLFORM_FILENAME,cufn,CURLFORM_END);
				}
				curl_easy_setopt(curl,CURLOPT_HTTPPOST,post);
				CURLcode res=curl_easy_perform(curl);
				gy_upload->curl_successful=(res==CURLE_OK);
				gy_upload->curl_response=res;
				curl_easy_cleanup(curl);
			}
			void Gyazo::UploadFile(GyazoCompletedUpload *ptr,std::string file_path){UploadFile(ptr,file_path,"","",gyazo_id,"","",true,verbose);}
		}
		*/
	}
}
