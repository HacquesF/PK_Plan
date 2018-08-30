#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>
#include <iostream>
#include "MyArea.hpp" //Also actChoice
class PrmWindow : public Gtk::Window {
	private :
		Glib::RefPtr<Gtk::Application> refapp;
		
	protected : 
		Gtk::Window* _mainWindow;
		Glib::RefPtr<Gtk::Builder> _refBuilder;
      Gtk::Box* _box;
      MyArea _drawArea;
		Gtk::RadioButton* _butRect;
		Gtk::RadioButton* _butLine;
		Gtk::RadioButton* _butSelect;

	public:
		PrmWindow(BaseObjectType* , const Glib::RefPtr<Gtk::Builder>& );
		virtual ~PrmWindow();
		void moreInit(Glib::RefPtr<Gtk::Application>&);
		void on_chgRadio();
};

#endif
