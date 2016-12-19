#ifndef FILESTUFF_H
#define FILESTUFF_H
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <iterator>
#include "../json.hpp"
#include <fstream>
#include <sstream>
#include <string>
using json = nlohmann::json;
namespace EasyGIF{
  namespace IO{
    size_t write_data(void *ptr,size_t size,size_t nmemb,void *stream);
    std::string readTextFile(const char*);
    std::string readTextFile(std::string);
    std::vector<std::string> readCookies(const char*);
    std::vector<std::string> readCookies(std::string);

    std::string getTempFile();

    bool fileExists(std::string filename);

    bool deleteFile(std::string filename);

    void parseJSONData(std::string json_data,json* json_point);
    void parseJSONFile(const char* file_path,json* point);
    void parseJSONFile(std::string file_path,json* point);
  }
}
#endif
