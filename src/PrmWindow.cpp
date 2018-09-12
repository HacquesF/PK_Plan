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
   
   //-----------------File Menu
    _agFile = Gio::SimpleActionGroup::create();
    _agFile->add_action("import", sigc::mem_fun(*this, &PrmWindow::on_Import) );
    insert_action_group("file", _agFile);
    
   _refBuilder->get_widget("imiImport",_imiImport);
   
   
   
//    _imiDelete->add_accelerator("Delete",_accgEdit,65535,NULL,NULL/*ACCEL_VISIBLE*/);
//    _imiDelete->signal_activate().connect( sigc::mem_fun(*this,&PrmWindow::on_Delete));

	
	show_all_children();
	
}


PrmWindow::~PrmWindow(){
}
void PrmWindow::moreInit(Glib::RefPtr<Gtk::Application>& app){
	_refapp = app;
    _refapp->set_accel_for_action("edit.delete", "Delete");
    _refapp->set_accel_for_action("file.import", "<control>i");
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

void PrmWindow::on_Import(){
    std::string fname = choseFile();
    _drawArea.loadPlan(fname);
}

//-------------Private
//TODO: filter in args
std::string PrmWindow::choseFile(){
    //https://developer.gnome.org/gtkmm-tutorial/3.4/sec-dialogs-filechooserdialog.html.en
    Gtk::FileChooserDialog dialog("Please choose a file",Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
    
    //Show the dialog and wait for a user response:
    int result = dialog.run();

    //Handle the response:
    switch(result)
    {
        case(Gtk::RESPONSE_OK):
        {
            return dialog.get_filename();
            break;
        }
        case(Gtk::RESPONSE_CANCEL):
        {
            break;
        }
        default:
        {
            std::cout << "Unexpected button clicked." << std::endl;
            break;
        }
    }
    return "";
}
