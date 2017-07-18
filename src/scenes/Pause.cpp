//
// Menu.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src/scenes
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Thu May 25 15:23:23 2017 jurczy_l
// Last update Sat Jun 17 19:52:06 2017 Springer-Roy Romain
//

#include	"Pause.hpp"

Pause::Pause()
{
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
  irr::gui::IGUIImage *logo = _gui->addImage(irr::core::rect<irr::s32>((screenSize.Width / 2) - 250,
								       screenSize.Height * 0 - 25,
								       (screenSize.Width / 2) + 250,
								       screenSize.Height * 0 + 275),
					     _elem,
					     -1,
					     0);
  logo->setImage(_driver->getTexture("./misc/GUI/PausePause.png"));
		 /*  irr::gui::IGUIStaticText *text = _gui->addStaticText(L"Pause",
						       irr::core::rect<irr::s32>(
										 screenSize.Width * 0.48,
										 screenSize.Height * 0.10,
										 screenSize.Width * 0.48 + 200,
										 screenSize.Height * 0.10 + 75
										 ),
						       false,
						       true,
						       _elem
						       );*/

  _play = _gui->addButton(
			  irr::core::rect<irr::s32>(
						    (screenSize.Width / 2) - 100,
						    screenSize.Height * 0.30,
						    (screenSize.Width / 2) + 100,
						    screenSize.Height * 0.30 + 75
						    ),
			  _elem,
			  -1,
			  L""
			  );
  _play->setImage(_driver->getTexture("./misc/GUI/play_off.jpg"));
  _play->setScaleImage();
  _save = _gui->addButton(
			  irr::core::rect<irr::s32>(
						    (screenSize.Width / 2) - 100,
						    screenSize.Height * 0.50,
						    (screenSize.Width / 2) + 100,
						    screenSize.Height * 0.50 + 75
),
			  _elem,
			  -1,
			  L""
			  );
  _save->setImage(_driver->getTexture("./misc/GUI/saveoff.png"));
  _save->setScaleImage();
  _exit = _gui->addButton(
			  irr::core::rect<irr::s32>(
						    (screenSize.Width / 2) - 100,
						    screenSize.Height * 0.70,
						    (screenSize.Width / 2) + 100,
						    screenSize.Height * 0.70 + 75
),
			  _elem,
			  -1,
			  L""
			  );
  _exit->setImage(_driver->getTexture("./misc/GUI/exitoff.jpg"));
  _exit->setScaleImage();
  _elem->setVisible(false);
}

Pause::~Pause()
{
}

void				Pause::update()
{
  if (_play->isPressed())
    {
      std::cout << "Return in game" << std::endl;
      WINDOW_STATE = Constants::PLAYING;
    }
  else if (_save->isPressed())
    {
      WINDOW_STATE = Constants::SAVE;
    }
  else if (_exit->isPressed())
    {
      std::cout << "exit the game" << std::endl;
      GInfo._reset = true;
      WINDOW_STATE = Constants::LAUNCHER;
    }
}

irr::gui::IGUIEnvironment	*Pause::getGui() const
{ return (_gui); }

void				Pause::drawAll()
{
  _gui->drawAll();
}

void				Pause::setVisible(bool i)
{ _elem->setVisible(i); }
