#include "screenshot.hpp"
#include "../util/file_system.hpp"

#include <iostream>
#include <string>
#include <gtk/gtk.h>

void TakeScreenshot(std::string);
void RecordGIF(std::string);

const std::string g_defaultModule = "screenshot_static";

std::string g_filename = "";
std::string g_module = "";

int main(int argc, char** argv)
{
	GtkBuilder* builder;
	GtkWidget* window;
	GError* error = nullptr;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	if(!gtk_builder_add_from_file(builder, EasyGIF::FileSystem::GetAssetPath("./ui/ezapp.glade"), &error))
	{
		g_warning("%s", error->message);
		g_free(error);
		return 1;
	}

	window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWnd"));
	gtk_builder_connect_signals(builder, nullptr);

	g_object_unref(G_OBJECT(builder));

	// check if user wants to launch a specific module (e.g. screenshot_gif) right away
	if(argc > 1)
		g_module = argv[1];

	if(argc > 2)
		g_filename = argv[2];

	if(g_module == "screenshot_static")
		TakeScreenshot(g_filename);
	else if(g_module == "screenshot_gif")
		RecordGIF(g_filename);
	else if(g_module != "")
		std::cout << "Unknown module \"" << g_module << std::endl;
	else if(g_module == "")
	{
		gtk_widget_show(window);
		gtk_main();
	}

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
