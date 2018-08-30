#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>
#include <iostream>
#include "MyArea.hpp"
class PrmWindow : public Gtk::Window {
	private :
//		Quasar q;
//		WinGameHum* humWindow;
//		WinGameBot* botWindow;
		Glib::RefPtr<Gtk::Application> refapp;
	protected : 
		Gtk::Window* mainWindow;
		Glib::RefPtr<Gtk::Builder> refBuilder;
//		Gtk::DrawingArea* drawArea;
//		Cairo::RefPtr<Cairo::Context> ContextPlan;
      Gtk::Box* box;
      MyArea drawArea;
//		Gtk::Button* but_launchH, *but_launchB;
//		Gtk::SpinButton* nbArgent;
//		
//		void on_launchH();
//		void on_launchB();
	public:
		PrmWindow(BaseObjectType* , const Glib::RefPtr<Gtk::Builder>& );
		virtual ~PrmWindow();
		void moreInit(Glib::RefPtr<Gtk::Application>&);
//		gboolean on_expose_event(GtkWidget*, GdkEventExpose*, gpointer);
};

#endif
