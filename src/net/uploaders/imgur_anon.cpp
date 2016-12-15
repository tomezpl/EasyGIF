#include "imgur_anon.hpp"
namespace EasyGIF{
  namespace Uploaders{
    namespace Imgur{
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
          //std::string tempfile=EasyGIF::IO::getTempFile();
          std::string tempfile("body.out");
          bodyfile=fopen(tempfile.c_str(),"wb");
          if(!bodyfile){curl_easy_cleanup(curl_obj);return -1;}
          curl_easy_setopt(curl_obj,CURLOPT_WRITEDATA,bodyfile);
          curl_easy_setopt(curl_obj,CURLOPT_WRITEFUNCTION,EasyGIF::IO::write_data);
          CURLcode res;
          res=curl_easy_perform(curl_obj);
          fclose(bodyfile);
          if(res==CURLE_OK){
            json json_response;
            EasyGIF::IO::parseJSONFile(tempfile,&json_response);
            //remove(bodyfile);
            return 0;
          }else{
            //remove(bodyfile);
            return 1;
          }
        }
        return 2;
      }
    }
  }
}
