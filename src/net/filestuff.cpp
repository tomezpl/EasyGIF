#include "filestuff.hpp"
namespace EasyGIF{
  namespace IO{
    static std::string readTextFile(const char* fp){
      std::ifstream input(fp);
      std::stringstream sstr;
      while(input>>sstr.rdbuf());
      input.close();
      return sstr.str();
    }
    static std::string readTextFile(std::string fp){return readTextFile(fp.c_str());}
    static std::vector<std::string> getCookies(const char* fp){
      std::vector<std::string> cookeez;
      std::string text_data=readTextFile(fp);
      size_t pos=0;
      while((pos=text_data.find("Set-Cookie",pos))>0 && pos<text_data.length()){
        size_t end=text_data.find("\r\n",pos);
        if(end>0&&end<text_data.length()){
          std::string cookie=text_data.substr(pos+12,end-(pos+11));
          cookeez.push_back(cookie);
        }
        pos++;
      }
      return cookeez;
    }
    static std::vector<std::string> getCookies(std::string fp){return getCookies(fp.c_str());}
  }
}
