#ifndef CRYPTOPP_ENABLE_NAMESPACE_WEAK
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#endif
#ifndef MD5_H
#define MD5_H
#include <crypto++/md5.h>
#include <crypto++/files.h>
#include <crypto++/hex.h>
#include <string>
#include "stringmod.hpp"
namespace EasyGIF{
	namespace Hashing{
		std::string GetFileMD5(const char *);
		std::string GetFileMD5(std::string);
		std::string GetFileMD5(std::string file_path,bool lowercase);
	}
}
#endif
