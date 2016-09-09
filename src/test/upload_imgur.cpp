#include <curl/curl.h>
#include <iostream>
#include <stdio.h>
#include <iterator>
#include "../json.hpp"
#include <fstream>
#include <sstream>
#include <string>
using json=nlohmann::json;
using namespace std;
static size_t write_data(void *ptr,size_t size,size_t nmemb,void *stream){
  size_t written=fwrite(ptr,size,nmemb,(FILE *)stream);
  return written;
}
std::string readTextFile(const char* file_path){
  ifstream input(file_path);
  std::stringstream sstr;
  while(input >> sstr.rdbuf());
  input.close();
  return sstr.str();
}
std::string readTextFile(std::string file_path){return readTextFile(file_path.c_str());}
std::vector<std::string> getCookies(std::string file_path){
  vector<string> v;
  std::string text_data=readTextFile(file_path);
  size_t pos=0;
  while((pos=text_data.find("Set-Cookie",pos))>0 && pos<text_data.length()){
    size_t end=text_data.find("\r\n",pos);
    std::string cookie_data=text_data.substr(pos+12,end-(pos+11));
    v.push_back(cookie_data);
    pos++;
  }
  return v;
}
int main(){
  CURL *curl;
  CURLcode res;
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl=curl_easy_init();
  FILE *headerfile;
  FILE *bodyfile;
  if(curl){
    curl_easy_setopt(curl,CURLOPT_URL,"http://imgur.com/upload/checkcaptcha");
    curl_easy_setopt(curl,CURLOPT_POST,1L);
    curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"total_uploads=1&create_album=true");
    curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
    struct curl_slist *list=NULL;
    list=curl_slist_append(list,"Host: imgur.com");
    list=curl_slist_append(list,"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:48.0) Gecko/20100101 Firefox/48.0");
    list=curl_slist_append(list,"Accept: */*");
    list=curl_slist_append(list,"Accept-Language: en-US,en;q=0.5");
    list=curl_slist_append(list,"Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    list=curl_slist_append(list,"x-requested-with: XMLHttpRequest");
    list=curl_slist_append(list,"Referer: http://imgur.com/");
    list=curl_slist_append(list,"Expect: ");
    //list=curl_slist_append(list,"Cookie: fst-client-id=7204cede498c00677a683f991d9818ffa3e5cb2a48dbce2fe82bd752201e070f; retina=0; SESSIONDATA=%7B%22sessionCount%22%3A1%2C%22sessionTime%22%3A1473431772836%7D; IMGURUIDJAFO=b3e43915e04ce565b608a34395c102ad5a9b2c3b8f7335407a3ce41b6ce39bd6");
    //list=curl_slist_append(list,"Cookie: fst-client-id=7204cede498c00677a683f991d9818ffa3e5cb2a48dbce2fe82bd752201e070f;");
    list=curl_slist_append(list,"DNT: 1");
    list=curl_slist_append(list,"Connection: close");
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,list);
    curl_easy_setopt(curl,CURLOPT_NOPROGRESS,1L);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_data);
    headerfile=fopen("head.out","wb");
    if(!headerfile){
      curl_easy_cleanup(curl);
      return -1;
    }
    bodyfile=fopen("body.out","wb");
    if(!bodyfile){
      curl_easy_cleanup(curl);
      return -1;
    }
    curl_easy_setopt(curl,CURLOPT_HEADERDATA,headerfile);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,bodyfile);
    res=curl_easy_perform(curl);
    fclose(headerfile);
    fclose(bodyfile);
    if(res!=CURLE_OK){
      fprintf(stderr,"curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
    }else{
      cout<<"IT WAS A SUCCESS WOOO"<<endl;
      string jason_data=readTextFile("body.out");
      vector<string> cookies=getCookies("head.out");
      for(int i=0;i<cookies.size();i++){
          cout<<"COOKIE = "<<cookies[i]<<endl;
      }
      cout<<"JSON = "<<jason_data<<endl;
      json j = json::parse(jason_data);
      cout<<"Successful = "<<j["success"]<<endl;
      if(j["success"]){
        cout<<"captchacheck was successful"<<endl;
        std::string album_id=j["data"]["new_album_id"];
        cout<<"new album id = "<<album_id<<endl;
        CURL *curl2;
        CURLcode res2;
        curl2=curl_easy_init();
        if(curl2){
          curl_easy_setopt(curl2,CURLOPT_URL,"http://imgur.com/upload");
          //curl_easy_setopt(curl2,CURLOPT_URL,"http://localhost:8072");
          //curl_easy_setopt(curl2,CURLOPT_VERBOSE,1L);
          struct curl_slist *list2=NULL;
          list2=curl_slist_append(list2,"Expect: ");
          list2=curl_slist_append(list2,"Host: imgur.com");
          list2=curl_slist_append(list2,"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:48.0) Gecko/20100101 Firefox/48.0");
          list2=curl_slist_append(list2,"Accept: */*");
          list2=curl_slist_append(list2,"Referer: http://imgur.com");
          //list2=curl_slist_append(list2,"Cookie: fst-client-id=7204cede498c00677a683f991d9818ffa3e5cb2a48dbce2fe82bd752201e070f; retina=0; SESSIONDATA=%7B%22sessionCount%22%3A1%2C%22sessionTime%22%3A1473431772836%7D; IMGURUIDJAFO=b3e43915e04ce565b608a34395c102ad5a9b2c3b8f7335407a3ce41b6ce39bd6; IMGURSESSION=hidn6b01a6pscoj02dv8i9lf41; UPSERVERID=i-7f3aef67");
          std::string cookie_string="Cookie: "+cookies[0]+"; "+cookies[1]+"; "+cookies[2];
          list2=curl_slist_append(list2,cookie_string.c_str());
          list2=curl_slist_append(list2,"Connection: close");
          list2=curl_slist_append(list2,"DNT: 1");
          curl_easy_setopt(curl2,CURLOPT_HTTPHEADER,list2);
          //Forms
          struct curl_httppost* post=NULL;
          struct curl_httppost* last=NULL;
          curl_formadd(&post,&last,CURLFORM_COPYNAME,"new_album_id",CURLFORM_PTRCONTENTS,album_id.c_str(),CURLFORM_END);
          curl_formadd(&post,&last,CURLFORM_COPYNAME,"Filedata",CURLFORM_FILE,"/home/toor/Downloads/shiet/shiet.gif",CURLFORM_CONTENTTYPE,"image/gif",CURLFORM_END);
          curl_easy_setopt(curl2,CURLOPT_HTTPPOST,post);
          res2=curl_easy_perform(curl2);
          cout<<res2<<endl;
          if(res2!=CURLE_OK){curl_easy_strerror(res2);}
        }else{
          cout<<"curl2 failed to init"<<endl;
        }
        curl_easy_cleanup(curl2);
      }else{
        cout<<"captchacheck was unsuccessful"<<endl;
      }
    }
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  return 0;
}
