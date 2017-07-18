//
// Menu.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src/scenes
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Thu May 25 15:23:23 2017 jurczy_l
// Last update Sun Jun 18 17:46:51 2017 louis
//

#include	"Menu.hpp"

Menu::Menu()
{
  irr::video::ITexture	*_img;
  irr::gui::IGUIImage	*bg;

  _driver = Device->getVideoDriver();
  _event = static_cast<Event *>(Device->getEventReceiver());
  _gui = Device->getGUIEnvironment();

  const irr::core::dimension2du& screenSize = _driver->getScreenSize();
  _elem = new irr::gui::IGUIElement(
				    irr::gui::EGUIET_ELEMENT,
				    _gui,
				    _gui->getRootGUIElement(),
				    -1,
				    irr::core::rect<irr::s32>(0,0,screenSize.Width,screenSize.Height)
				    );
  _elem->setVisible(false);
  irr::gui::IGUIElement *toto = _gui->addButton( irr::core::rect<irr::s32>(0,0,50,50),_elem, -1, L"a");
  _skin = _gui->getSkin();
  _img = _driver->getTexture("./misc/GUI/background_menu.jpg");
  bg = _gui->addImage(irr::core::rect<irr::s32>(0,0, screenSize.Width,screenSize.Height),_elem);
  bg->setImage(_img);
  bg->setScaleImage(true);
  _driver->removeTexture(_img);
  irr::gui::IGUIFont* font = _gui->getFont("./misc/GUI/bigfont.png");
  if (font)
    _gui->getSkin()->setFont(font);

  b_play = (_gui->addButton(irr::core::rect<int>((screenSize.Width / 2) - 200,
						 screenSize.Height * 0.35,
						 (screenSize.Width / 2) + 200,
						 screenSize.Height * 0.35 + 75),
			    _elem,
			    Constants::PLAYING,
			    L""));
  b_play->setImage(_driver->getTexture("./misc/GUI/menu/menuplay.png"));
  b_play->setScaleImage();
  b_play->setUseAlphaChannel(true);
  b_load = _gui->addButton(irr::core::rect<int>((screenSize.Width / 2) - 200,
						screenSize.Height * 0.50,
						(screenSize.Width / 2) + 200,
						screenSize.Height * 0.50 + 75),
			   _elem,
			   Constants::SAVE,
			   L"");
  b_load->setImage(_driver->getTexture("./misc/GUI/menu/menuload.png"));
  b_load->setScaleImage();
  b_load->setUseAlphaChannel(true);
  b_settings = _gui->addButton(irr::core::rect<int>((screenSize.Width / 2) - 200,
						    screenSize.Height * 0.65,
						    (screenSize.Width / 2) + 200,
						    screenSize.Height * 0.65 + 75),
			       _elem,
			       Constants::SETTINGS,
			       L"");
  b_settings->setImage(_driver->getTexture("./misc/GUI/menu/menusettings.png"));
  b_settings->setScaleImage();
  b_settings->setUseAlphaChannel(true);
  b_quit  = _gui->addButton(irr::core::rect<int>((screenSize.Width / 2) - 200,
						 screenSize.Height * 0.80,
						 (screenSize.Width / 2) + 200,
						 screenSize.Height * 0.80 + 75),
			    _elem,
			    Constants::EXIT,
			    L"");
  b_quit->setImage(_driver->getTexture("./misc/GUI/menu/menuquit.png"));
  b_quit->setScaleImage();
  b_quit->setUseAlphaChannel(true);
  if (!SEngine.getMute())
    SEngine.playMenuMusic();
}

Menu::~Menu()
{}

void				Menu::update()
{
  if (b_play->isPressed())
    WINDOW_STATE = Constants::LAUNCHER;
  else if (b_settings->isPressed())
    WINDOW_STATE = Constants::SETTINGS;
  else if (b_load->isPressed())
    WINDOW_STATE = Constants::SAVE;
  else if (b_quit->isPressed())
    {
      Device->drop();
      exit(0);
    }
}

irr::gui::IGUIEnvironment	*Menu::getGui() const
{ return (_gui); }

void				Menu::drawAll()
{
  _gui->drawAll();
}

void				Menu::setVisible(bool i)
{_elem->setVisible(i); }
