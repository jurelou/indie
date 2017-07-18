//
// Settings.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src/scenes
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Thu May 25 15:23:23 2017 jurczy_l
// Last update Sat Jun 17 21:02:14 2017 Springer-Roy Romain
//

#include	"Launcher.hpp"

Launcher::Launcher()
{
  _driver = Device->getVideoDriver();
  _event = static_cast<Event *>(Device->getEventReceiver());
  _gui = Device->getGUIEnvironment();
  _skin = _gui->getSkin();
  irr::gui::IGUIFont *font = _gui->getFont("./misc/GUI/font_w.png");
  if (font)
    _skin->setFont(font);
  const irr::core::dimension2du& w = _driver->getScreenSize();
  _elem = new irr::gui::IGUIElement(
				    irr::gui::EGUIET_ELEMENT,
				    _gui,
				    _gui->getRootGUIElement(),
				    -1,
				    irr::core::rect<irr::s32>(0,0,w.Width,w.Height)
				    );
  _elem->setVisible(false);
  irr::gui::IGUIImage *bg = _gui->addImage(irr::core::rect<irr::s32>(0,0, w.Width, w.Height), _elem);
  irr::video::ITexture* tex;
  tex = _driver->getTexture("./misc/GUI/background_launcher.jpg");
  bg->setImage(tex);
  bg->setScaleImage(true);
  _driver->removeTexture(tex);
  set_player = _gui->addButton(
			       irr::core::rect<irr::s32>(
							 w.Width * 0.7,
							 w.Height *0.10,
							 w.Width * 0.7 + 200,
							 w.Height * 0.10 + 75
							 ),
			       _elem,
			       -1,
			       L""
			       );
  set_player->setImage(_driver->getTexture("./misc/GUI/play_off.jpg"));
  set_player->setScaleImage();
  set_player->setUseAlphaChannel(true);
  _menu = _gui->addButton(
			  irr::core::rect<irr::s32>(
						    w.Width * 0.7,
						    w.Height *0.30,
						    w.Width * 0.7 + 200,
						    w.Height * 0.30 + 75
						    ),
			  _elem,
			  -1,
			  L""
			  );
  _menu->setImage(_driver->getTexture("./misc/GUI/menuoff.jpg"));
  _menu->setScaleImage();
  _menu->setUseAlphaChannel(true);

  irr::gui::IGUIStaticText *text = _gui->addStaticText(L"NOMBRE DE JOUEURS:",
		      irr::core::rect<int>(
					   w.Width * 0.15,
					   w.Height *0.35 + 12,
					   w.Width * 0.15 + 600,
					   w.Height * 0.35 + 30
					   ),
						       false,
						       true,
						       _elem,
						       -1,
						       false
						       );
  text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  irr::gui::IGUIStaticText *text2 = _gui->addStaticText(L"NOMBRE D'IA:",
						       irr::core::rect<int>(
									    w.Width * 0.15,
									    w.Height *0.55 + 15,
									    w.Width * 0.15 + 600,
									    w.Height * 0.55 + 30
									    ),
						       false,
						       true,
						       _elem,
						       -1,
						       false
							);
  text2->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  nb_players = _gui->addSpinBox(L"",
				irr::core::rect<irr::s32>(
							  w.Width * 0.35,
							  w.Height *0.35,
							  w.Width * 0.35 + 100,
							  w.Height * 0.35 + 50
							  ),
				true,
				_elem);

  nb_ia = _gui->addSpinBox(L"",
			   irr::core::rect<irr::s32>(
						     w.Width * 0.35,
						     w.Height *0.55,
						     w.Width * 0.35 + 100,
						     w.Height * 0.55 + 50
						     ),
			   true,
			   _elem);

  irr::gui::IGUIStaticText *pre_map= _gui->addStaticText(L"LOAD EXISTING MAP:",
							 irr::core::rect<int>(w.Width * 0.2 - 100,
									      w.Height * 0.75,
									      w.Width * 0.2 + 400,
									      w.Height * 0.75 + 100),
							 false,
							 true,
							 _elem,
							 -1,
							 false
							 );
  pre_map->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  irr::gui::IGUIStaticText *pre_ma_p= _gui->addStaticText(L"GENERATE RANDOM MAP:",
							  irr::core::rect<int>(w.Width * 0.5 - 0,
									       w.Height * 0.75,
									       w.Width * 0.5 + 400,
									       w.Height * 0.75 + 100),
							 false,
							 true,
							 _elem,
							 -1,
							 false
							 );
  pre_ma_p->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  irr::gui::IGUIStaticText *msg= _gui->addStaticText(L"OR",
						     irr::core::rect<int>(w.Width * 0.4 - 0,
									  w.Height*0.85,
									  w.Width * 0.4 + 400,
									  w.Height * 0.85 + 100),
						     false,
						     true,
						     _elem,
						     -1,
						     false
						     );
  msg->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  _map_list = _gui->addListBox(irr::core::rect<irr::s32>(w.Width * 0.2 - 100,
							 w.Height * 0.8,
							 w.Width * 0.2 + 200,
							 w.Height * 0.8 + 100),
			       _elem
			       );
  _random_map = _gui->addButton(
			       irr::core::rect<irr::s32>(
							 w.Width * 0.48,
							 w.Height *0.81,
							 w.Width * 0.48 + 350,
							 w.Height * 0.81 + 75
							 ),
			       _elem,
			       -1,
			       L""
			       );
  _random_map->setIsPushButton(true);
  _random_map->setImage(_driver->getTexture("./misc/GUI/random_off.jpg"));
  _random_map->setPressedImage(_driver->getTexture("./misc/GUI/random_on.jpg"));
  _random_map->setUseAlphaChannel(true);
  _random_map->setScaleImage();
  int	cpt;
  cpt = 0;
  DIR * rep = opendir("./map/");
  if (rep != NULL)
    {
      struct dirent * ent;
      while ((ent = readdir(rep)) != NULL)
	if (ent->d_name[0] != '.')
	  _map_path.push_back(ent->d_name);
      closedir(rep);
    }
  std::wstring widestr;
  for (auto it : _map_path)
    {
      widestr = std::wstring(it.begin(), it.end());
      _map_list->addItem(widestr.c_str());
    }
  _map_list->setAutoScrollEnabled(true);
  nb_ia->setValue(0);
  nb_ia->setRange(0,10);
  nb_ia->setDecimalPlaces(0);

  nb_players->setValue(4);
  nb_players->setRange(0,100);
  nb_players->setDecimalPlaces(0);
}

Launcher::~Launcher()
{}

void				Launcher::update()
{
  if (_random_map->isPressed())
    _map_list->setSelected(-1);
  else
    std::cout << "not prese" << std::endl;
  for (int j = 0; j < _map_list->getItemCount(); j++)
    if ( j == _map_list->getSelected())
      {
  	_random_map->setPressed(false);
  	_map_list->setItemOverrideColor(j, irr::video::SColor(255,0,255,0));
      }
    else
      _map_list->setItemOverrideColor(j, irr::video::SColor(255,255,255,255)); 
  if (set_player->isPressed())
    {
      GInfo._nbPlayers = nb_players->getValue();
      GInfo._nbIA = nb_ia->getValue();
      GInfo.currentPlayer = 0;
      //      GInfo._isRandomMap = _random_map->isPressed();
      std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
      std::cout << "~~ GENERATING CONTEXT ~~" << std::endl;
      std::cout << "~~" << GInfo._nbPlayers << " Players"<< std::endl;
      std::cout << "~~" << GInfo._nbIA << " IA" << std::endl;      
      if (_random_map->isPressed())
	{
	  GInfo._isRandomMap = true;
	  std::cout << "~~ random MAP"<< std::endl;
	}
      else
	{
	  int i = 0;
	  for (auto it : _map_path)
	    {
	      if (i == _map_list->getSelected())
		{
		  GInfo._pathMap = "./map/" + it;
		  GInfo._isRandomMap = false;
		  std::cout << "~~ Pre-loaded map: "<<it << std::endl;
		}
	      i++;
	    }
	}
      std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
      WINDOW_STATE = Constants::PLAYING;
    }
  if(_menu->isPressed())
    WINDOW_STATE = Constants::MAIN_MENU;
}

irr::gui::IGUIEnvironment	*Launcher::getGui() const
{ return (_gui); }

void				Launcher::drawAll()
{  _gui->drawAll(); }

void				Launcher::setVisible(bool i)
{_elem->setVisible(i); }
