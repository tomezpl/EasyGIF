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
  }
}
