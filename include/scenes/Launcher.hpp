//
// Menu.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Thu May 25 15:25:17 2017 jurczy_l
// Last update Wed Jun 14 13:04:19 2017 Springer-Roy Romain
//

#ifndef			LAUNCHER_HPP_
# define		LAUNCHER_HPP_

#include		<vector>
#include		<sys/types.h>
#include		<dirent.h>
#include		<list>
#include		<iostream>
#include		"irrlicht.h"
#include		"Constants.hpp"
#include		"AScene.hpp"
#include		"GameInfo.hpp"
#include		"Event.hpp"

class			Launcher : public AScene
{
public:
  Launcher();
  ~Launcher();

  void			update();
  void			drawAll();
  void			setVisible(bool);
  irr::gui::IGUIEnvironment		*getGui() const;
private:
  irr::gui::IGUIEnvironment             *_gui;
  irr::gui::IGUIElement			*_elem;
  irr::gui::IGUIListBox			*_map_list;
  std::list<std::string>		_map_path;
  irr::gui::IGUISkin			*_skin;
  irr::gui::IGUIButton			*set_player;
  irr::gui::IGUIButton			*_random_map;
  irr::gui::IGUIButton			*_menu;
  irr::gui::IGUISpinBox			*nb_players;
  irr::gui::IGUISpinBox			*nb_ia;
};

#endif
