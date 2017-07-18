//
// Win.hpp for indie_studio in /home/spring_r/Project/cpp_indie_studio/include/scenes
// 
// Made by Springer-Roy Romain
// Login   <spring_r@epitech.eu>
// 
// Started on  Thu Jun 15 13:19:44 2017 Springer-Roy Romain
// Last update Thu Jun 15 17:16:44 2017 Springer-Roy Romain
//

#ifndef			WIN_HPP_
# define		WIN_HPP_

#include		<vector>
#include		<iostream>
#include		"irrlicht.h"
#include		"Constants.hpp"
#include		"AScene.hpp"
#include		"Event.hpp"

class			Win : public AScene
{
public:
  Win();
  ~Win();

  void			update();
  void			drawAll();
  void			setVisible(bool);
  irr::gui::IGUIEnvironment		*getGui() const;

private:
  irr::gui::IGUIEnvironment             *_gui;
  irr::gui::IGUISkin			*_skin;
  irr::gui::IGUIElement			*_elem;
  irr::gui::IGUIButton			*_menu;
  irr::gui::IGUIButton			*_quit;
};

#endif
