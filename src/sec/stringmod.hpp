#ifndef STRINGMOD_H
#define STRINGMOD_H
#include <string>
#include <algorithm>
namespace EasyGIF{
  namespace Mod{
    std::string toLower(std::string toconvert);
    std::string toUpper(std::string toconvert);
    std::string rfindExtension(std::string path);
  }
}
#endif
