#include "../net/create_header.hpp"
#include <iostream>
#include <curl/curl.h>
using namespace std;
int main(){
  EasyGIF::Uploaders::HeaderCreator creator;
  cout<<"Created header creator"<<endl;
  creator.AddHeader("Connection","close")->AddHeader("Server","fukinwot");
  curl_slist* list=NULL;
  //list=creator.GetHeaderList();
  list=curl_slist_append(list,"HIDERE: WAZZUP");
  cout<<creator.CopyHeaderList(list)<<endl;
  curl_global_init(CURL_GLOBAL_ALL);
  CURL *c;
  c=curl_easy_init();
  if(c){
    cout<<"Curl initialised"<<endl;
    CURLcode res;
    curl_easy_setopt(c,CURLOPT_URL,"http://localhost:9119");
    cout<<"Set url"<<endl;
    curl_easy_setopt(c,CURLOPT_HTTPHEADER,list);
    res=curl_easy_perform(c);
    cout<<"Got response"<<endl;
    curl_easy_strerror(res);
  }
  curl_slist_free_all(list);
  curl_easy_cleanup(c);
  curl_global_cleanup();
  return 0;
}
