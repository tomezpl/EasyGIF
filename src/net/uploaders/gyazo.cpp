#include "gyazo.hpp"
namespace EasyGIF{
	namespace Uploaders{

		std::string GetLastExtension(std::string path){
			return path.substr(path.find_last_of(".")); //returns the dot with the extension
		}

		//void UploadFileToGyazo(Gyazo::GyazoCompletedUpload *ptr,std::string file_path){Gyazo g;g.UploadFile(ptr,file_path);}
		//void UploadFileToGyazo(Gyazo::GyazoCompletedUpload *ptr,std::string file_path,bool verbose){Gyazo g;g.SetVerbose(verbose);g.UploadFile(ptr,file_path);}
		bool CanConnectToGyazo(bool https){return TestGET(EasyGIF::Uploaders::Gyazo::GetIndexPage(https));}
    bool CanConnectToGyazo(){return CanConnectToGyazo(true);}
    bool CanConnectToGyazo(bool https,std::string proxy){return TestProxy(EasyGIF::Uploaders::Gyazo::GetIndexPage(https).c_str(),proxy.c_str());}
		int UploadFileToGyazo(std::string file_path,EasyGIF::Uploaders::Gyazo::GyazoCompletedUpload* result){
			EasyGIF::Uploaders::Gyazo::GyazoImageUploader uploader;
			return uploader.UploadFile(file_path,result);
		}
		namespace Gyazo{
			std::string GetUploadURL(bool use_https){std::string start=use_https?"https":"http";return start+std::string("://gyazo.com/upload.cgi");}
			std::string GetUploadURL(){return GetUploadURL(true);}
			std::string GetMD5Page(std::string md5_digest,bool https){std::string start=GetIndexPage(https);return start+md5_digest;}
			std::string GetImagePage(std::string md5_digest,std::string file_extension,bool https){std::string start=GetImageIndexPage(https);return start+md5_digest+file_extension;}
			std::string GetIndexPage(bool use_https){std::string start=use_https?"https":"http";return start+std::string("://gyazo.com");}
			std::string GetImageIndexPage(bool use_https){std::string start=use_https?"https":"http";return start+std::string("://i.gyazo.com/");}
			//Get Default Gyazo Settings
			std::string GetDefaultUserAgent(){
				#ifdef IMAGE_SPLIT_SETTINGS
					return Values::DEFAULT_GYAZO_AGENT.empty()?EasyGIF::Uploaders::Values::DEFAULT_AGENT:Values::DEFAULT_GYAZO_AGENT;
				#else
					return EasyGIF::Uploaders::Values::DEFAULT_AGENT;
				#endif
			}
			std::string GetDefaultProxySettings(){
				#ifdef IMAGE_SPLIT_SETTINGS
					return Values::DEFAULT_GYAZO_PROXY;
				#else
					return EasyGIF::Uploaders::Values::DEFAULT_PROXY;
				#endif
			}

			bool GetDefaultUseHTTPS(){
				#ifdef IMAGE_SPLIT_SETTINGS
					return Values::DEFAULT_GYAZO_USE_HTTPS;
				#else
					return EasyGIF::Uploaders::Values::DEFAULT_USE_HTTPS;
				#endif
			}

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

			void SetDefaultUploadSettings(GyazoUploadSettings* settings_struct,std::string file_path,std::string user_agent,std::string proxy_settings,std::string gyazo_id,bool use_https){
				settings_struct->upload_settings.upload_url=GetUploadURL(use_https);
				settings_struct->upload_settings.upload_file=file_path;
				settings_struct->upload_settings.upload_extension=""; //Not implemented
				settings_struct->upload_settings.upload_filename=""; //Not implemented
				settings_struct->upload_settings.user_agent=user_agent;
				settings_struct->upload_settings.proxy_settings=proxy_settings;
				settings_struct->gyazo_id=gyazo_id;
				settings_struct->use_https=use_https;
			}
			void SetUploadSettings(GyazoUploadSettings* settings_struct,std::string file_path){
				settings_struct->upload_settings.upload_url=GetUploadURL();
				settings_struct->upload_settings.upload_file=file_path;
				//settings_struct->upload_settings.upload_extension="";
				settings_struct->upload_settings.upload_extension=GetLastExtension(file_path);
				settings_struct->upload_settings.upload_filename="";
				settings_struct->upload_settings.user_agent=GetDefaultUserAgent();
				settings_struct->upload_settings.proxy_settings=GetDefaultProxySettings();
				settings_struct->gyazo_id=GetRandomID(32);
			}

			//GyazoImageUploader Constructors
			#ifdef IMAGE_SPLIT_SETTINGS
				GyazoImageUploader::GyazoImageUploader() : ImageUploader(EasyGIF::Uploaders::Gyazo::GetUploadURL(EasyGIF::Uploaders::Gyazo::Values::DEFAULT_GYAZO_USE_HTTPS),std::string("Gyazo"),EasyGIF::Uploaders::Gyazo::Values::DEFAULT_GYAZO_PROXY.empty()?EasyGIF::Uploaders::Values::DEFAULT_PROXY:EasyGIF::Uploaders::Gyazo::Values::DEFAULT_GYAZO_PROXY,EasyGIF::Uploaders::Gyazo::Values::DEFAULT_GYAZO_AGENT.empty()?EasyGIF::Uploaders::Values::DEFAULT_AGENT:EasyGIF::Uploaders::Gyazo::Values::DEFAULT_GYAZO_AGENT,true,true){this->gyazo_id=GetRandomID(32);this->last_upload_info=nullptr;}
			#else
				GyazoImageUploader::GyazoImageUploader() : ImageUploader(EasyGIF::Uploaders::Gyazo::GetUploadURL(EasyGIF::Uploaders::Gyazo::Values::DEFAULT_USE_HTTPS),std::string("Gyazo"),EasyGIF::Uploaders::Values::DEFAULT_PROXY,EasyGIF::Uploaders::Values::DEFAULT_AGENT,true,true){this->gyazo_id=GetRandomID(32);this->last_upload_info=nullptr;}
			#endif
			GyazoImageUploader::GyazoImageUploader(std::string id,std::string proxy,std::string user_agent,bool use_https) : ImageUploader(EasyGIF::Uploaders::Gyazo::GetUploadURL(use_https),std::string("Gyazo"),proxy,user_agent,true,true){this->use_https=use_https;this->last_upload_info=nullptr;}
			//GyazoImageUploader::GyazoImageUploader(std::string gid,std::string prx,std::string uag) : ImageUploader(DEFAULT_GYAZO_USE_HTTPS?"https://gyazo.com/upload.cgi":"http://gyazo.com/upload.cgi","Gyazo",prx,uag){this->gyazo_id=ParseGID(gid);}
			GyazoImageUploader* GyazoImageUploader::SetGyazoID(std::string new_id,bool parse){this->gyazo_id=(parse)?ParseGID(new_id):new_id;return this;}
			GyazoImageUploader* GyazoImageUploader::SetGyazoID(std::string new_id){this->gyazo_id=ParseGID(new_id);return this;}
			GyazoImageUploader* GyazoImageUploader::SetUseHTTPS(bool use_https){this->use_https=use_https;this->SetUploadURL(EasyGIF::Uploaders::Gyazo::GetUploadURL(use_https));return this;}
			std::string GyazoImageUploader::GetGyazoID(){return this->gyazo_id;}
			bool GyazoImageUploader::GetUseHTTPS(){return this->use_https;}
			void CloneGyazoUpload(GyazoCompletedUpload* a,GyazoCompletedUpload* b){
				b->upload_settings=a->upload_settings;
				b->md5_digest=a->md5_digest;
			}
			//Gyazo Upload
			//0 = CURL ok
			//1 = CURL not ok
			//2 = CURL not initialised
			int GyazoImageUploader::UploadFile(GyazoUploadSettings upload_settings,GyazoCompletedUpload* uploaded_info){
				uploaded_info->upload_settings=upload_settings;
				uploaded_info->md5_digest=EasyGIF::Hashing::GetFileMD5(upload_settings.upload_settings.upload_file,true);
				std::string page_url=upload_settings.use_https?"https":"http";page_url+="://gyazo.com/"+uploaded_info->md5_digest;
				uploaded_info->page_url=page_url;
				std::string image_url=upload_settings.use_https?"https":"http";image_url+="://i.gyazo.com/"+uploaded_info->md5_digest+upload_settings.upload_settings.upload_extension;
				uploaded_info->image_url=image_url;
				uploaded_info->upload_successful=false;
				CURL *curl;
				curl=curl_easy_init();
				if(curl){
					CURLcode res;
					curl_easy_setopt(curl,CURLOPT_URL,upload_settings.upload_settings.upload_url.c_str());
					if(!upload_settings.upload_settings.proxy_settings.empty()){curl_easy_setopt(curl,CURLOPT_PROXY,upload_settings.upload_settings.proxy_settings.c_str());}
					EasyGIF::Uploaders::HeaderCreator hedcreator;
					curl_slist* headers=hedcreator.AddHeader("Expect","")->AddHeader("User-Agent",upload_settings.upload_settings.user_agent)->AddHeader("Connection","close")->GetHeaderList();
					curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
					struct curl_httppost* post=NULL;
					struct curl_httppost* last=NULL;
					curl_formadd(&post,&last,CURLFORM_COPYNAME,"id",CURLFORM_COPYCONTENTS,upload_settings.gyazo_id.c_str(),CURLFORM_END);
					if(upload_settings.upload_settings.upload_filename.empty()){
						curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,upload_settings.upload_settings.upload_file.c_str(),CURLFORM_CONTENTTYPE,"image/*",CURLFORM_END);
					}else{
						curl_formadd(&post,&last,CURLFORM_COPYNAME,"imagedata",CURLFORM_FILE,upload_settings.upload_settings.upload_file.c_str(),CURLFORM_CONTENTTYPE,"image/*",CURLFORM_FILENAME,upload_settings.upload_settings.upload_filename.c_str(),CURLFORM_END);
					}
					curl_easy_setopt(curl,CURLOPT_HTTPPOST,post);

					// don't request body of the download,
					// prevents curl from printing to stdout:
					curl_easy_setopt(curl, CURLOPT_NOBODY, 1); 

					res=curl_easy_perform(curl);
					uploaded_info->upload_successful=res==CURLE_OK;
					uploaded_info->curl_response=res;
					curl_easy_cleanup(curl);
					curl_slist_free_all(headers);
					return (res==CURLE_OK)?0:1;
				}
				return 2;
			}
			int GyazoImageUploader::UploadFile(std::string file_path,EasyGIF::Uploaders::Gyazo::GyazoCompletedUpload* completed_upload){
				struct EasyGIF::Uploaders::Gyazo::GyazoUploadSettings settings;
				EasyGIF::Uploaders::Gyazo::SetUploadSettings(&settings,file_path);
				return UploadFile(settings,completed_upload);
			}
		}
	}
}
