#include "screenshot.hpp"
#include "../util/file_system.hpp"

#include <iostream>
#include <string>
#include <gtk/gtk.h>
#include <unistd.h>
#include <xcb/xcb.h>

const std::string g_defaultModule = "screenshot_static";

std::string g_filename = "";
std::string g_module = "";

GtkBuilder* g_pBuilder = nullptr;
GtkWidget* g_pMainWnd = nullptr;

// Can the application start capturing already?
// (GTK+ doesn't destroy the windows immediately so this will be used to tell whether it's been destroyed or not)
bool g_ProceedCapture = false;

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

extern "C" {
	void ui_btn_capture_gif(GtkButton* widget, gpointer user_data)
	{
		GtkWidget* pCaptureWnd = gtk_widget_get_toplevel(GTK_WIDGET(widget));
		gtk_widget_destroy(pCaptureWnd);
		gtk_main_quit();
		g_module = "screenshot_gif";

	}

	void ui_btn_capture_ss(GtkButton* widget, gpointer user_data)
	{
		GtkWidget* pCaptureWnd = gtk_widget_get_toplevel(GTK_WIDGET(widget));
		gtk_widget_hide(pCaptureWnd);
		gtk_widget_destroy(pCaptureWnd);
		gtk_main_quit();
		g_module = "screenshot_static";
	}

	void ui_btn_capture(GtkButton* widget, gpointer user_data)
	{
		std::cout << "You clicked \"Capture\"" << std::endl;
		GtkWidget* pCaptureWnd = GTK_WIDGET(gtk_builder_get_object(g_pBuilder, "captureDlgWnd"));
		std::cout << "captureDlgWnd grabbed" << std::endl;
		gtk_widget_show(pCaptureWnd);
		std::cout << "captureDlgWnd shown" << std::endl;
		gtk_widget_destroy(g_pMainWnd);
		std::cout << "mainWnd destroyed" << std::endl;
	}

	void ui_btn_capture_destroy(GtkButton* widget, gpointer user_data)
	{
		g_ProceedCapture = true;
	}
}

int main(int argc, char** argv)
{
	GError* error = nullptr;

	gtk_init(&argc, &argv);

	g_pBuilder = gtk_builder_new();
	if(!gtk_builder_add_from_file(g_pBuilder, EasyGIF::FileSystem::GetAssetPath("./ui/ezapp.glade").c_str(), &error))
	{
		g_warning("%s", error->message);
		//g_free(error);
		return 1;
	}

	gtk_builder_connect_signals(g_pBuilder, nullptr);

	gtk_builder_add_callback_symbol(g_pBuilder, "ui_btn_capture", G_CALLBACK(ui_btn_capture));
	gtk_builder_add_callback_symbol(g_pBuilder, "ui_btn_capture_gif", G_CALLBACK(ui_btn_capture_gif));
	gtk_builder_add_callback_symbol(g_pBuilder, "ui_btn_capture_ss", G_CALLBACK(ui_btn_capture_ss));

	
	g_pMainWnd = GTK_WIDGET(gtk_builder_get_object(g_pBuilder, "mainWnd"));

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
		gtk_widget_show(g_pMainWnd);
		gtk_main();

		// TODO: This will need to be fixed
		// but it works for now so I'll leave it like this
		//if(g_ProceedCapture)
		//{
			if(g_module == "screenshot_static")
				TakeScreenshot(g_filename);
			else if(g_module == "screenshot_gif")
				RecordGIF(g_filename);
		//}
	}

	g_object_unref(G_OBJECT(g_pBuilder));

	return 0;
}
