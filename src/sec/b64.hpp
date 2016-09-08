#include <string>
namespace EasyGIF{
	namespace Conversion{
		int Base64_StringLength(int);
		int Base64_StringLength(std::string);
		int Base64_PaddingLength(int);
		int Base64_DataLength(int,int);
		int Base64_ConvertCharToInt(char);
		std::string Base64_Encode(const char*,int);
		std::string Base64_Encode(std::string,bool);
		std::string Base64_Encode_File(std::string);
		char* Base64_Decode(std::string,int*,bool);
		char* Base64_Decode(std::string,int*);
		std::string Base64_DecodeString(std::string);
	}
}
