#include <curl/curl.h>
#include <vector>
#include <string>
#include <algorithm>
#include "../sec/stringmod.hpp"
namespace EasyGIF{
  namespace Uploaders{
    struct HeaderData{
			std::string header;
			std::string value;
		};
    std::string toLower(std::string toconvert);
    class HeaderCreator{
			private:
				std::vector<HeaderData> headers;
			public:
				HeaderCreator();
				//int allows vector to be allocated to that amount at creation
				HeaderCreator(int expected);
				//Add will just add the header to the list
				HeaderCreator* AddHeader(std::string head,std::string value);
				//Set will append only if it doesn't exist in the list, otherwise it will overwrite value
				HeaderCreator* SetHeader(std::string head,std::string value);
				HeaderCreator* SetHeader(std::string head,std::string value,bool ignore_case);
        bool HasHeader(std::string head);
        int IndexOf(std::string head,int startpos,bool ignore_case);
        int IndexOf(std::string head,int startpos);
        int IndexOf(std::string head,bool ignore_case);
        int IndexOf(std::string head);
        int GetHeaderCount();
				HeaderCreator* ClearHeaders();
        std::string GetHeaderString(int index);
        std::vector<std::string> GetHeaderStrings();
				std::vector<HeaderData> GetHeaders();
				curl_slist* GetHeaderList();
        void GetHeaderList(curl_slist* list);
		};
  }
}
