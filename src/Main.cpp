
#include "PrmWindow.hpp"
#include <gtkmm.h>
#include <iostream>
#include "Line.hpp"
//void click_startH(){
//	std::cout<<"Bijouor\n";
//}
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
	
	
//	//----------------------Quasar
//	Quasar q;
//	std::unique_ptr<Jeu> jeuQ = std::unique_ptr<Jeu>(&q);	
//	if(argc == 1){
//		Humain j (50);
//		jeuQ.get()->recommencer(j.getCB());
//		ChoixPossible chx = AUCUN;
//		while(chx != QUITTER){
//			jeuQ.get()->voirScore();
//			chx =j.getChoix(jeuQ.get()->getScore());
//			switch(chx){
//				case BOUTON1:
//					jeuQ.get()->bouton1();
//					break;
//				case BOUTON2:
//					jeuQ.get()->bouton2();
//					break;
//				case GAIN:
//					jeuQ.get()->retirerGain(j.getCB());
//					break;
//				case REJOUER:
//					jeuQ.get()->recommencer(j.getCB());
//					break;
//				default:;
//			}
//		}
//		std::cout<<"Vous avez terminé avec : "<<j.getCB()->getSolde()<<std::endl;
//	}else{//bot en argument lance un nombre de partie de robot voulue
//		int nbGame = std::stoi(argv[1]);
//		Robot r(0);
//		r.seeStrat();
//		ChoixPossible chx = AUCUN;
//		for(int i=0;i<nbGame;++i){//Compteur de partie
//			jeuQ.get()->recommencer(r.getCB());
//			while(jeuQ->getEtat()){//tant que la partie est en cours
//				chx =r.getChoix(jeuQ.get()->getScore());
//				switch(chx){
//					case BOUTON1:
//						jeuQ.get()->bouton1();
//						break;
//					case BOUTON2:
//						jeuQ.get()->bouton2();
//						break;
//					case GAIN:
//						jeuQ.get()->retirerGain(r.getCB());
//						break;
//					case AUCUN:
//						std::cout<<"Choix Inconnu\n";
//						break;
//					default:;
//				}
//			}
//			std::cout<<jeuQ.get()->getScore()<<":"<<r.getCB()->getSolde()<<" | ";
//		}
//		std::cout<<"\nAvec "<<nbGame<<" partie, le robot a eu : "<<r.getCB()->getSolde()<<std::endl;
//	}
	//return 0;
}

//----------------GTK function

