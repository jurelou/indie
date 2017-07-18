//
// Loose.cpp for Loose in /home/spring_r/Project/cpp_indie_studio/src/scenes
// 
// Made by Springer-Roy Romain
// Login   <spring_r@epitech.eu>
// 
// Started on  Fri Jun 16 15:43:28 2017 Springer-Roy Romain
// Last update Sun Jun 18 14:39:35 2017 louis
//

#include	"Loose.hpp"

Loose::Loose()
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
  irr::gui::IGUIImage *win = _gui->addImage(irr::core::rect<irr::s32>(
								      //screenSize.Width * 0.19,
								      (screenSize.Width / 2) - 400,
								      screenSize.Height * 0.1,
								      (screenSize.Width / 2) + 400,
								      screenSize.Height * 0.1 + 400
								      ),
					    _elem,
					    -1,
					    0);
  win->setImage(_driver->getTexture("./misc/GUI/loose.png"));
  _elem->setVisible(false);
}

Loose::~Loose()
{
}

void				Loose::update()
{
  if (_event->isSomethingPressed())
    WINDOW_STATE == Constants::PLAYING;
}

irr::gui::IGUIEnvironment	*Loose::getGui() const
{ return (_gui); }

void				Loose::drawAll()
{
  _gui->drawAll();
}

void				Loose::setVisible(bool i)
{ _elem->setVisible(i); }
