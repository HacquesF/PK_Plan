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
   
   //-----------------Edit Menu
   _agEdit = Gio::SimpleActionGroup::create();
   //Add action here, accel in moreInit
   _agEdit->add_action("delete", sigc::mem_fun(*this, &PrmWindow::on_Delete) );
   insert_action_group("edit", _agEdit);  
   
   _refBuilder->get_widget("imiDelete",_imiDelete);
   
   
   
//    _imiDelete->add_accelerator("Delete",_accgEdit,65535,NULL,NULL/*ACCEL_VISIBLE*/);
//    _imiDelete->signal_activate().connect( sigc::mem_fun(*this,&PrmWindow::on_Delete));

	
	show_all_children();
	
}


PrmWindow::~PrmWindow(){
}
void PrmWindow::moreInit(Glib::RefPtr<Gtk::Application>& app){
	_refapp = app;
    _refapp->set_accel_for_action("edit.delete", "Delete");
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
void PrmWindow::on_Delete(){
    _drawArea.deleteSel();
}
