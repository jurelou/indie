//
// Menu.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Thu May 25 15:25:17 2017 jurczy_l
// Last update Sun May 28 13:38:31 2017 jurczy_l
//

#ifndef			MENU_HPP_
# define		MENU_HPP_

#include		<vector>
#include		<iostream>
#include		"irrlicht.h"
#include		"Constants.hpp"
#include		"AScene.hpp"
#include		"Event.hpp"

class			Menu : public AScene
{
public:
  Menu();
  ~Menu();

  void			update();
  void			drawAll();
  void			setVisible(bool);
  irr::gui::IGUIEnvironment		*getGui() const;
private:
  irr::gui::IGUIEnvironment             *_gui;
  irr::gui::IGUIElement			*_elem;

  irr::gui::IGUISkin			*_skin;
  irr::gui::IGUIButton			*b_play;
  irr::gui::IGUIButton			*b_settings;
  irr::gui::IGUIButton			*b_quit;
  irr::gui::IGUIButton			*b_load;
};

#endif
