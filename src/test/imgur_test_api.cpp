#include <curl/curl.h>
#include <string.h>
#include <iostream>
using namespace std;
int main(){
  cout<<"Imgur API test built successfully"<<endl;
  curl_global_init(CURL_GLOBAL_ALL);
  cout<<"CURL global init success"<<endl;
  CURL *curl;
  curl=curl_easy_init();
  if(curl){
    cout<<"Successful curl instance init"<<endl;
    curl_easy_setopt(curl,CURLOPT_URL,"https://api.imgur.com/3/image");
    cout<<"Set upload URL"<<endl;
    curl_slist* headers=NULL;
    //Put your own client id here
    headers=curl_slist_append(headers,"Authorization: Client-ID ?");
    headers=curl_slist_append(headers,"User-Agent: EasyGIF/Imgur V0.1");
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
    cout<<"Set headers"<<endl;
    struct curl_httppost* post=NULL;
    struct curl_httppost* last=NULL;
    curl_formadd(&post,&last,CURLFORM_COPYNAME,"image",CURLFORM_FILE,"/home/file_path/lel.png",CURLFORM_CONTENTTYPE,"image/*",CURLFORM_END);
    //curl_formadd(&post,&last,CURLFORM_COPYNAME,"new_album_id",CURLFORM_PTRCONTENTS,album_id.c_str(),CURLFORM_END);
    curl_formadd(&post,&last,CURLFORM_COPYNAME,"title",CURLFORM_COPYCONTENTS,"omgsost00pid",CURLFORM_END);
    curl_easy_setopt(curl,CURLOPT_HTTPPOST,post);
    CURLcode res;
    res=curl_easy_perform(curl);
    cout<<"Got response"<<endl;
    curl_easy_strerror(res);
    curl_easy_cleanup(curl);
  }else{
    cout<<"Failed to init curl instance"<<endl;
    return 1;
  }
  curl_global_cleanup();
  return 0;
}
