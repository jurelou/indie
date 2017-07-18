//
// GraphicalEngine.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio/include
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Wed May 17 11:55:22 2017 jurczy_l
// Last update Tue Jun 27 15:19:46 2017 louis
//

#ifndef		GRAPHICALENGINE_HPP_
# define	GRAPHICALENGINE_HPP_

#include	<iostream>
#include	<string>
#include	"irrlicht.h"
#include	"Constants.hpp"
#include	"Event.hpp"
//   SCENES
#include	"AScene.hpp"
#include	"Intro.hpp"
#include	"Menu.hpp"
#include	"Play.hpp"
#include	"Settings.hpp"
#include	"Launcher.hpp"
#include	"Pause.hpp"
#include	"Win.hpp"
#include	"Loose.hpp"
#include	"Save.hpp"

class		GraphicalEngine
{
public:
  GraphicalEngine(bool);
  ~GraphicalEngine();

  void		draw();
  void		update();
private:
  Event					*recv;
  irr::video::IVideoDriver		*_driver;
  irr::scene::ISceneManager		*_sceneManager;
  irr::gui::IGUIEnvironment		*guienv;
  irr::gui::IGUIFont			*font;
  std::vector<AScene *>			_scenes;
};

#endif
