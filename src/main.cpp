//
// main.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Wed May 17 11:38:25 2017 jurczy_l
// Last update Sat Jun 17 16:01:54 2017 augustin marmus
//

#include	<exception>
#include	<iostream>
#include	<string>
#include	"irrlicht.h"
#include	"Game.hpp"
#include  "GameInfo.hpp"
#include  "SoundEngine.hpp"

irr::IrrlichtDevice	*Device = NULL;
Constants::WindowState	WINDOW_STATE = Constants::WindowState::INTRO;
GameInfo GInfo;
SoundEngine SEngine;

int		main(int ac, char **av, char **env)
{
  bool	fullscreen;


  std::srand(time(NULL));
  fullscreen = false;
  (void)env;
  (void)ac;
  (void)av;
  if (ac == 2 && strcmp(av[1], "-f") == 0)
    fullscreen = true;
  else
    fullscreen = false;

  try
    {
      Game	core(fullscreen);

      core.run();
    }
  catch (const std::bad_alloc&)
    {
      std::cerr << "Memory error" << std::endl;
      return (-1);
    }
}
