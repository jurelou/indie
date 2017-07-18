//
// Game.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Wed May 17 11:40:49 2017 jurczy_l
// Last update Wed Jun 28 00:35:38 2017 louis
//

#ifndef		GAME_HPP_
# define	GAME_HPP_

# include	<iostream>
# include	<vector>
# include	<string>
# include	<map>
# include	"GraphicalEngine.hpp"
# include	"irrlicht.h"
# include	"Constants.hpp"
# include	"GameInfo.hpp"

class				Game
{
public:
  Game(bool);
  ~Game();
  void				run();

private:
  GraphicalEngine		*_gfxEngine;
  GameInfo			*_context;
  int				lastFPS;
  void				update();
};

#endif
