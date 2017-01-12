#include "imgur_anon.hpp"
namespace Image_Upload_Values=EasyGIF::Uploaders::Values;
namespace EasyGIF{
  namespace Uploaders{
    namespace Imgur{
      std::string GetDefaultUploadURL(){return "https://api.imgur.com/3/image";}
      std::string GetDefaultAnonUserAgent(){
        #ifdef IMAGE_SPLIT_SETTINGS
          return AnonValues::DEFAULT_IMGUR_ANON_AGENT.empty()?Image_Upload_Values::DEFAULT_AGENT:AnonValues::DEFAULT_IMGUR_ANON_AGENT;
        #else
          return Image_Upload_Values::DEFAULT_AGENT;
        #endif
      }
      std::string GetDefaultAnonProxy(){
        #ifdef IMAGE_SPLIT_SETTINGS
          return AnonValues::DEFAULT_IMGUR_ANON_PROXY.empty()?Image_Upload_Values::DEFAULT_PROXY:AnonValues::DEFAULT_IMGUR_ANON_PROXY;
        #else
          return Image_Upload_Values::DEFAULT_PROXY;
        #endif
      }
      void SetUploadSettings(ImgurUploadSettings* upload_settings,std::string client_id,std::string upload_file,std::string filename){
        //CURL specific stuff
        upload_settings->upload_settings.upload_url=GetDefaultUploadURL();
        upload_settings->upload_settings.upload_file=upload_file;
        upload_settings->upload_settings.upload_filename=filename;
        upload_settings->upload_settings.user_agent=GetDefaultAnonUserAgent();
        upload_settings->upload_settings.proxy_settings=GetDefaultAnonProxy();

        //Imgur specific stuff
        upload_settings->client_id=client_id;
      }
      std::string GetDefaultAnonHostname(){
        return "api.imgur.com";
      }
      void SetCompletedDefaultValues(ImgurCompletedUpload* comp){
        comp->upload_id="";
        comp->title="";
        comp->description="";
        comp->datetime=0;
        comp->type="";
        comp->animated=false;
        comp->width=0;
        comp->height=0;
        comp->size=0;
        comp->views=0;
        comp->bandwidth=0;
        comp->vote="";
        comp->favourite=false;
        comp->nsfw="";
        comp->section="";
        comp->account_url="";
        comp->account_id=0;
        comp->is_ad=false;
        comp->in_gallery=false;
        comp->delete_hash="";
        comp->name="";
        comp->link="";
        comp->success=false;
        comp->status_code=0;
        //Ignores upload_settings #yoyo on that one
      }
      void ParseImgurResponse(json j,ImgurCompletedUpload* comp){
        SetCompletedDefaultValues(comp);
        comp->success=j["success"];
        comp->status_code=j["status"];
        if(j["success"]){
          json d=j["data"];
          if(d.count("id")>0&&!d["id"].is_null()){comp->upload_id=d["id"];}
          if(d.count("title")>0&&!d["title"].is_null()){comp->title=d["title"];}
          if(d.count("description")>0&&!d["description"].is_null()){comp->description=d["description"];}
          if(d.count("datetime")>0&&!d["datetime"].is_null()){comp->datetime=d["datetime"];}
          if(d.count("type")>0&&!d["type"].is_null()){comp->type=d["type"];}
          if(d.count("animated")>0&&!d["animated"].is_null()){comp->animated=d["animated"];}
          if(d.count("width")>0&&!d["width"].is_null()){comp->width=d["width"];}
          if(d.count("height")>0&&!d["height"].is_null()){comp->height=d["height"];}
          if(d.count("size")>0&&!d["size"].is_null()){comp->size=d["size"];}
          if(d.count("views")>0&&!d["views"].is_null()){comp->views=d["views"];}
          if(d.count("bandwidth")>0&&!d["bandwidth"].is_null()){comp->bandwidth=d["bandwidth"];}
          if(d.count("vote")>0&&!d["vote"].is_null()){comp->vote=d["vote"];}
          if(d.count("favorite")>0&&!d["favorite"].is_null()){comp->favourite=d["favorite"];}
          if(d.count("nsfw")>0&&!d["nsfw"].is_null()){comp->nsfw=d["nsfw"];}
          if(d.count("section")>0&&!d["section"].is_null()){comp->section=d["section"];}
          if(d.count("account_url")>0&&!d["account_url"].is_null()){comp->account_url=d["account_url"];}
          if(d.count("account_id")>0&&!d["account_id"].is_null()){comp->account_id=d["account_id"];}
          if(d.count("is_ad")>0&&!d["is_ad"].is_null()){comp->is_ad=d["is_ad"];}
          if(d.count("in_gallery")>0&&!d["in_gallery"].is_null()){comp->in_gallery=d["in_gallery"];}
          if(d.count("deletehash")>0&&!d["deletehash"].is_null()){comp->delete_hash=d["deletehash"];}
          if(d.count("name")>0&&!d["name"].is_null()){comp->name=d["name"];}
          if(d.count("link")>0&&!d["link"].is_null()){comp->link=d["link"];}
        }
      }
      int UploadAnonImage(ImgurUploadSettings upload_settings,ImgurCompletedUpload* completed_upload){
        completed_upload->upload_settings=upload_settings;
        CURL* curl_obj;
        curl_obj=curl_easy_init();
        FILE* bodyfile;
        if(curl_obj){
          curl_easy_setopt(curl_obj,CURLOPT_URL,upload_settings.upload_settings.upload_url.c_str());
          //Creating and setting headers
          EasyGIF::Uploaders::HeaderCreator header_creator;
          std::string auth_header("Client-ID ");
          auth_header+=upload_settings.client_id;
          curl_slist* headers=header_creator.AddHeader("Authorization",auth_header)->AddHeader("User-Agent",upload_settings.upload_settings.user_agent)->GetHeaderList();
          curl_easy_setopt(curl_obj,CURLOPT_HTTPHEADER,headers);
          //Creating multipart/form-data form
          struct curl_httppost* post=NULL;
          struct curl_httppost* last=NULL;
          curl_formadd(&post,&last,CURLFORM_COPYNAME,"image",CURLFORM_FILE,upload_settings.upload_settings.upload_file.c_str(),CURLFORM_FILENAME,upload_settings.upload_settings.upload_filename.c_str(),CURLFORM_END);
          if(!upload_settings.album_id.empty()){curl_formadd(&post,&last,CURLFORM_COPYNAME,"album",CURLFORM_COPYCONTENTS,upload_settings.album_id.c_str(),CURLFORM_END);}
          curl_formadd(&post,&last,CURLFORM_COPYNAME,"type",CURLFORM_COPYCONTENTS,"file",CURLFORM_END);
          //automatically detected when using multipart/form-data
          //curl_formadd(&post,&last,CURLFORM_COPYNAME,"name",CURLFORM_COPYCONTENTS,upload_settings.name,CURLFORM_END);
          curl_formadd(&post,&last,CURLFORM_COPYNAME,"title",CURLFORM_COPYCONTENTS,upload_settings.title.c_str(),CURLFORM_END);
          curl_formadd(&post,&last,CURLFORM_COPYNAME,"description",CURLFORM_COPYCONTENTS,upload_settings.description.c_str(),CURLFORM_END);
          curl_easy_setopt(curl_obj,CURLOPT_HTTPPOST,post);
          //Doing upload and writing response to file
          std::string tempfile=EasyGIF::IO::getTempFile();
          //std::string tempfile("markout.out");
          bodyfile=fopen(tempfile.c_str(),"wb");

          //std::cout<<"Tempfile = "<<tempfile<<std::endl;

          if(!bodyfile){curl_easy_cleanup(curl_obj);return -1;}
          curl_easy_setopt(curl_obj,CURLOPT_WRITEDATA,bodyfile);
          curl_easy_setopt(curl_obj,CURLOPT_WRITEFUNCTION,EasyGIF::IO::write_data);
          CURLcode res;
          res=curl_easy_perform(curl_obj);
          fclose(bodyfile);
          if(res==CURLE_OK){
            json json_response;
            EasyGIF::IO::parseJSONFile(tempfile,&json_response);
            ParseImgurResponse(json_response,completed_upload);
            remove(tempfile.c_str());
            return 0;
          }else{
            remove(tempfile.c_str());
            return 1;
          }
        }
        return 2;
      }

      ImgurAnonUploader::~ImgurAnonUploader(){
        if(this->last_upload_info!=nullptr){delete this->last_upload_info;}
      }
      //Uploader Class
      ImgurAnonUploader::ImgurAnonUploader() : ImageUploader(GetDefaultUploadURL(),GetDefaultAnonHostname(),GetDefaultAnonProxy(),GetDefaultAnonUserAgent(),true,true){
        this->last_upload_info=nullptr;
      }
      bool ImgurAnonUploader::GetUseHTTPS(){return true;}
      bool ImgurAnonUploader::HasLastUpload(){return this->last_upload_info!=nullptr;}
    }
  }
}
