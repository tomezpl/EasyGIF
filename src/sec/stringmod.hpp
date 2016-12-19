#ifndef STRINGMOD_H
#define STRINGMOD_H
#include <string>
#include <algorithm>
#include <cctype>
namespace EasyGIF{
  namespace Mod{
    std::string toLower(std::string toconvert);
    std::string toUpper(std::string toconvert);
    std::string rfindExtension(std::string path);
    //copy pasta'd from here http://stackoverflow.com/a/17976541
    inline std::string trim(const std::string &s);
  }
}
#endif
