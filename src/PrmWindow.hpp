#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <gtkmm.h>
#include <iostream>
#include "MyArea.hpp" //Also actChoice
class PrmWindow : public Gtk::Window {
	private :
		Glib::RefPtr<Gtk::Application> _refapp;
		std::string choseFile();
	protected : 
		Gtk::Window* _mainWindow;
		Glib::RefPtr<Gtk::Builder> _refBuilder;
        Gtk::Box* _box;
        MyArea _drawArea;
		Gtk::RadioButton* _butRect;
		Gtk::RadioButton* _butLine;
		Gtk::RadioButton* _butSelect;
        Gtk::ImageMenuItem* _imiDelete;
        Gtk::ImageMenuItem* _imiImport;
        Glib::RefPtr<Gio::SimpleActionGroup> _agEdit;
        Glib::RefPtr<Gio::SimpleActionGroup> _agFile;

	public:
		PrmWindow(BaseObjectType* , const Glib::RefPtr<Gtk::Builder>& );
		virtual ~PrmWindow();
		void moreInit(Glib::RefPtr<Gtk::Application>&);
		void on_chgRadio();
        void on_Delete();
        void on_Import();
};

#endif
