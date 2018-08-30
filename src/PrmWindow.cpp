#include "PrmWindow.hpp"

PrmWindow::PrmWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder)
	: Gtk::Window(cobject),
	  _refBuilder(builder)
{

	//------------------App window
	_refBuilder->get_widget("main_window",_mainWindow);
	
	//------------------Connecting the drawing area
   _refBuilder->get_widget("box1",_box);
   _box->pack_end(_drawArea,true,true);
   _drawArea.show();
   
   //-----------------Radio buttons
	_refBuilder->get_widget("butRect",_butRect);
	_butRect->signal_clicked().connect( sigc::mem_fun(*this,&PrmWindow::on_chgRadio));
	_refBuilder->get_widget("butLine",_butLine);
	_butLine->signal_clicked().connect( sigc::mem_fun(*this,&PrmWindow::on_chgRadio));
	_refBuilder->get_widget("butSelect",_butSelect);
	_butSelect->signal_clicked().connect( sigc::mem_fun(*this,&PrmWindow::on_chgRadio));
   _butLine->set_active();

	
	show_all_children();
	
}


PrmWindow::~PrmWindow(){
}
void PrmWindow::moreInit(Glib::RefPtr<Gtk::Application>& app){
	refapp = app;
}


//--------Signal
void PrmWindow::on_chgRadio(){
   //default
   actChoice res = dLine;
   //verify wich button is pressed
   if(_butRect->get_active()) res = dRect;
   if(_butLine->get_active()) res = dLine;
   if(_butSelect->get_active()) res = Select;
   _drawArea.chgAction(res);
   
   //That or one fun for each button that call a chgRadio(action)
}
