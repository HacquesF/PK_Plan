
#include "PrmWindow.hpp"
#include <gtkmm.h>
#include <iostream>
int main(int argc, char* argv[]){ 
   
	//-------------------GTK thingy
	auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
	auto builder = Gtk::Builder::create();
	try
  {
    builder->add_from_file("glade/window_main.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }
	
	PrmWindow* mainWindow= nullptr;
	builder->get_widget_derived("main_window",mainWindow);
	mainWindow->moreInit(app);
  return app->run(*mainWindow);
	
}

//----------------GTK function

