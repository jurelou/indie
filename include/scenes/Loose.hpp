//
// Loose.hpp for Indie_studio in /home/spring_r/Project/cpp_indie_studio/include/scenes
// 
// Made by Springer-Roy Romain
// Login   <spring_r@epitech.eu>
// 
// Started on  Fri Jun 16 15:42:10 2017 Springer-Roy Romain
// Last update Fri Jun 16 15:42:55 2017 Springer-Roy Romain
//

#ifndef			LOOSE_HPP_
# define		LOOSE_HPP_

#include		<vector>
#include		<iostream>
#include		"irrlicht.h"
#include		"Constants.hpp"
#include		"AScene.hpp"
#include		"Event.hpp"

class			Loose : public AScene
{
public:
  Loose();
  ~Loose();

  void			update();
  void			drawAll();
  void			setVisible(bool);
  irr::gui::IGUIEnvironment		*getGui() const;

private:
  irr::gui::IGUIEnvironment             *_gui;
  irr::gui::IGUISkin			*_skin;
  irr::gui::IGUIElement			*_elem;
};

#endif
