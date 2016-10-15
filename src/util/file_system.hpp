#ifndef EZGIF_UTIL_FILESYS
#define EZGIF_UTIL_FILESYS

#include <string>

namespace EasyGIF {
	/**
	 * A utility namespace to help with resolving the program's asset paths and such.
	*/
	namespace FileSystem {
		/**
		 * If the program is installed, it returns an absolute path to the asset located in the install directory (/usr/lib by default).
		 * Otherwise, it will return the same path as passed only with "./" added at the start since it's likely to be in the user's current directory.
		 *
		 * The program will need to be compiled with **EZGIF_APP_INSTALLED** to be considered installed in this function.
		*/
		extern const char* GetAssetPath(std::string assetLocalPath);
	}
}

#endif
