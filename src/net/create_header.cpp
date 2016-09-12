#include "create_header.hpp"
namespace EasyGIF{
  namespace Uploaders{
    HeaderCreator::HeaderCreator(){}
    HeaderCreator::HeaderCreator(int expected){headers.reserve(expected);}
    HeaderCreator* HeaderCreator::AddHeader(std::string head,std::string value){
      struct HeaderData new_data;
      new_data.header=head;
      new_data.value=value;
      headers.push_back(new_data);
      return this;
    }
    HeaderCreator* HeaderCreator::SetHeader(std::string head,std::string value,bool ignore_case){
      int ind=IndexOf(head);
      if(ind>-1){
        headers[ind].header=head;
        headers[ind].value=value;
      }else{
        struct HeaderData header_data;
        header_data.header=head;
        header_data.value=value;
        headers.push_back(header_data);
      }
      return this;
    }
    HeaderCreator* HeaderCreator::SetHeader(std::string head,std::string value){return SetHeader(head,value,true);}
    int HeaderCreator::IndexOf(std::string head,int startpos,bool ignore_case){
      for(int i=startpos;i<headers.size();i++){if(ignore_case?(EasyGIF::Mod::toLower(head).compare(EasyGIF::Mod::toLower(headers[i].header))==0):(head.compare(headers[i].header)==0)){return i;}}
      return -1;
    }
    int HeaderCreator::IndexOf(std::string head,int startpos){return IndexOf(head,startpos,true);}
    int HeaderCreator::IndexOf(std::string head,bool ignore_case){return IndexOf(head,0,ignore_case);}
    int HeaderCreator::IndexOf(std::string head){return IndexOf(head,0);}
    int HeaderCreator::GetHeaderCount(){return headers.size();}
    HeaderCreator* HeaderCreator::ClearHeaders(){headers.clear();return this;}
    std::vector<HeaderData> HeaderCreator::GetHeaders(){return headers;}
    std::string HeaderCreator::GetHeaderString(int header_index){
      if(header_index>=0&&header_index<headers.size()){std::string headerstr=headers[header_index].header+": "+headers[header_index].value;return headerstr;}
      return "";
    }
    std::vector<std::string> HeaderCreator::GetHeaderStrings(){
      std::vector<std::string> header_strs;
      header_strs.reserve(headers.size());
      for(int i=0;i<headers.size();i++){header_strs.push_back(GetHeaderString(i));}
      return header_strs;
    }
    curl_slist* HeaderCreator::GetHeaderList(){
      curl_slist* heds=NULL;
      GetHeaderList(heds);
      return heds;
    }
    void HeaderCreator::GetHeaderList(curl_slist* list){
      list=NULL;
      for(int i=0;i<headers.size();i++){curl_slist_append(list,GetHeaderString(i).c_str());}
    }
  }
}
