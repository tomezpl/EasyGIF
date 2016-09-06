#include "md5.hpp"
namespace EasyGIF{
	namespace Hashing{
		std::string GetFileMD5(const char *filename){
			std::string digest;
			CryptoPP::Weak::MD5 hash;
			CryptoPP::FileSource(filename,true,new CryptoPP::HashFilter(hash,new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
			return digest;
		}
		std::string GetFileMD5(std::string filename){return GetFileMD5(filename.c_str());}
	}
}
