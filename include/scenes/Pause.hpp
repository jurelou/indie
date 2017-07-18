//
// Menu.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Thu May 25 15:25:17 2017 jurczy_l
// Last update Fri Jun 16 19:10:36 2017 louis
//

#ifndef			PAUSE_HPP_
# define		PAUSE_HPP_

#include		<vector>
#include		<iostream>
#include		"irrlicht.h"
#include		"Constants.hpp"
#include		"AScene.hpp"
#include		"Event.hpp"

class			Pause : public AScene
{
public:
  Pause();
  ~Pause();

  void			update();
  void			drawAll();
  void			setVisible(bool);
  irr::gui::IGUIEnvironment		*getGui() const;

private:
  irr::gui::IGUIEnvironment             *_gui;
  irr::gui::IGUISkin			*_skin;
  irr::gui::IGUIElement			*_elem;
  irr::gui::IGUIButton			*_play;
  irr::gui::IGUIButton			*_settings;
  irr::gui::IGUIButton			*_save;
  irr::gui::IGUIButton			*_exit;
};

#endif
