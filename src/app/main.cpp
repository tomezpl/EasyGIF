#include "screenshot.hpp"
#include <iostream>
#include <string>

void TakeScreenshot(std::string);
void RecordGIF(std::string);

int main(int argc, char** argv)
{
	const std::string defaultModule = "screenshot_static";

	std::string filename = "";
	std::string module = "";

	// check if user wants to launch a specific module (e.g. screenshot_gif) right away
	if(argc > 1)
		module = argv[1];
	else
		module = defaultModule;

	if(argc > 2)
		filename = argv[2];

	if(module == "screenshot_static")
		TakeScreenshot(filename);
	else if(module == "screenshot_gif")
		RecordGIF(filename);
	else
		std::cout << "Unknown module \"" << module << std::endl;

	return 0;
}

void TakeScreenshot(std::string filename = "")
{
	EasyGIF::App::ScreenshotStatic ss;
	ss.RunUI();

	if(filename == "")
		filename = "./screenshot_static.png";

	ss.Save(filename);
}

void RecordGIF(std::string filename = "")
{
	EasyGIF::App::ScreenshotGIF sg;
	sg.RunUI();

	if(filename == "")
		filename = "./screenshot_gif.gif";
	
	sg.Save(filename);
}
