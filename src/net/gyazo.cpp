#include "gyazo.hpp"
#include <iostream>
namespace EasyGIF{
	namespace Uploaders{
		//Methods n shit in namespace
		void UploadFileToGyazo(GyazoCompletedUpload *ptr,std::string file_path){Gyazo g;g.UploadFile(ptr,file_path);}
		void UploadFileToGyazo(GyazoCompletedUpload *ptr,std::string file_path,bool verbose){Gyazo g;g.SetVerbose(verbose);g.UploadFile(ptr,file_path);}
		std::string GetImagePage(std::string md5_digest,bool https){std::string start=https?"https://gyazo.com/":"http://gyazo.com";return start+md5_digest;}
		void CURL_init(){curl_global_init(CURL_GLOBAL_ALL);}
		void CURL_cleanup(){curl_global_cleanup();}
		//GYAZO CLASS STUFF
		Gyazo::Gyazo(){
			this->upload_url="https://gyazo.com/upload.cgi";
			this->user_agent="Mozilla/420";
			this->proxy_settings="";
			this->gyazo_id=GetRandomID(32);
			this->verbose=false;
		}
		Gyazo::Gyazo(std::string upload_url,std::string user_agent,std::string proxy_settings,std::string gyazo_id,bool verbose){
			this->upload_url=upload_url;
			this->user_agent=user_agent;
			this->proxy_settings=proxy_settings;
			this->gyazo_id=ParseGID(gyazo_id);
			this->verbose=verbose;
		}
		//Getters+Setters
		bool Gyazo::UsingProxy(){return !proxy_settings.empty();}
		std::string Gyazo::GetProxy(){return proxy_settings;}
		std::string Gyazo::GetUserAgent(){return user_agent;}
		std::string Gyazo::GetUploadURL(){return upload_url;}
		std::string Gyazo::GetID(){return gyazo_id;}
		bool Gyazo::GetVerbose(){return verbose;}
		void Gyazo::SetProxy(std::string new_proxy_settings){proxy_settings=new_proxy_settings;}
		void Gyazo::SetUserAgent(std::string new_user_agent){user_agent=new_user_agent;}
		void Gyazo::SetUploadURL(std::string new_upload_url){upload_url=new_upload_url;}
		void Gyazo::SetID(std::string new_gyazo_id){gyazo_id=ParseGID(new_gyazo_id);}
		void Gyazo::SetVerbose(bool new_verbose){verbose=new_verbose;}
		void Gyazo::UseHTTPS(bool yeno){upload_url=(yeno)?"https://gyazo.com/upload.cgi":"http://gyazo.com/upload.cgi";}
		std::string Gyazo::GetRandomID(int len){
			static const char idalpha[]="0123456789abcdef"; //I believe it is only 32 hex digits, might not be. Don't think it matters
			char s[len+1];
			for(int i=0;i<len;i++){s[i]=idalpha[rand()%16];}
			s[len]=0;
			std::string s2(s);
			return s2;
		}
		std::string Gyazo::ParseGID(std::string gyid){
			if(gyid.length()==32){return gyid;}
			if(gyid.length()>32){return gyid.substr(0,32);}
			return gyid+GetRandomID(32-gyid.length());
		}
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
			//Creating and setting GyazoCompletedUpload
				gy_upload->upload_url=(uurl.empty())?this->upload_url:uurl;
				gy_upload->upload_file=fp;
				gy_upload->upload_filename=fn;
				gy_upload->gyazo_id=ParseGID(gyid);
				gy_upload->user_agent=(ua.empty())?this->user_agent:ua;
				gy_upload->proxy_settings=(prx.empty()&&us_prx)?this->proxy_settings:prx;
				gy_upload->md5_digest=EasyGIF::Hashing::GetFileMD5(fp);
			//Initialise CURL object
			CURL *curl;
			curl=curl_easy_init();
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
}
