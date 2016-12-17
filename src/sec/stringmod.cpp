#include "stringmod.hpp"
namespace EasyGIF{
  namespace Mod{
    std::string toLower(std::string toconvert){
      std::string lower(toconvert);
      std::transform(lower.begin(),lower.end(),lower.begin(),::tolower);
      return lower;
    }
    std::string toUpper(std::string toconvert){
      std::string upper(toconvert);
      std::transform(upper.begin(),upper.end(),upper.begin(),::toupper);
      return upper;
    }
    std::string rfindExtension(std::string path){size_t rfind=path.rfind(".");return rfind==std::string::npos?path:path.substr(rfind);}
    //creates copy of string to return
    inline std::string trim(const std::string &s)
    {
      auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
      auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
      return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
    }
  }
}
