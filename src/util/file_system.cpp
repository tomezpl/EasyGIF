#include "file_system.hpp"

namespace EasyGIF {
	namespace FileSystem {
		std::string GetAssetPath(std::string assetLocalPath)
		{
			std::string finalPath = "";

			#ifdef EZGIF_APP_INSTALLED
			finalPath = "/usr/lib/easygif/";
			#endif

			finalPath.append("./");
			finalPath.append(assetLocalPath);

			return finalPath;
		}
	}
}
