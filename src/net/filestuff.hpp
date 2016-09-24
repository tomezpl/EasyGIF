#include <iostream>
#include <stdio.h>
#include <iterator>
#include "../json.hpp"
#include <fstream>
#include <sstream>
#include <string>
namespace EasyGIF{
  namespace IO{
    static std::string readTextFile(const char*);
    static std::string readTextFile(std::string);
    static std::vector<std::string> readCookies(const char*);
    static std::vector<std::string> readCookies(std::string);
  }
}
