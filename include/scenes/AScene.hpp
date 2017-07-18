//
// AScene.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Fri May 26 14:26:11 2017 jurczy_l
// Last update Sat Jun 17 21:10:02 2017 louis
//

#ifndef				ASCENE_HPP_
# define			ASCENE_HPP_

#include			<iostream>
#include			"irrlicht.h"
#include			"Event.hpp"
#include		        "GameInfo.hpp"
//x#include			"RealisticWater.h"

class				 AScene
{
public:
  virtual void			update() = 0;
  virtual void			drawAll() = 0;
  virtual void			setVisible(bool) = 0;
protected:
  Event				      *_event;
  irr::video::IVideoDriver	*_driver;
};

#endif
