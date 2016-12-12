#include <iostream>
#include <stdio.h>
#include <iterator>
#include "../json.hpp"
#include <fstream>
#include <sstream>
#include <string>
namespace EasyGIF{
  namespace IO{
    static size_t write_data(void *ptr,size_t size,size_t nmemb,void *stream);
    static std::string readTextFile(const char*);
    static std::string readTextFile(std::string);
    static std::vector<std::string> readCookies(const char*);
    static std::vector<std::string> readCookies(std::string);

    static void parseJSONData(std::string json_data,json* json_point);
    static void parseJSONFile(const char* file_path,json* point);
    static void parseJSONFile(std::string file_path,json* point);
  }
}
