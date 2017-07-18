//
// Constants.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio/include
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Wed May 17 12:02:12 2017 jurczy_l
// Last update Sun Jun 18 13:34:20 2017 louis
//

#ifndef		CONSTANTS_HPP_
# define	CONSTANTS_HPP_

#include	<list>
#include	"irrlicht.h"
#include  "SoundEngine.hpp"

namespace Constants
{
  enum		target_type
    {
      NO,
      GUN,
      ROCKET
    };
  enum		WindowState
    {
      INTRO = 0,
      MAIN_MENU,
      SETTINGS,
      PLAYING,
      PLAYER_WIN,
      PLAYER_LOOSE,
      EXIT,
      LAUNCHER,
      PAUSE,
      SAVE
    };

  enum	       obj_type
    {
      WATER,
      PLANE,
      BARREL,
      UNDEFINED
    };

  enum		Action
    {
      NONE = -1,
      QUIT = 0,
      UP,
      DOWN,
      LEFT,
      RIGHT,
      FRONT,
      BEHIND,
      GO_RIGHT,
      GO_LEFT,
      JUMP,
      SUICID,
      ATTACK,
      SELECT
    };
}

extern Constants::WindowState	WINDOW_STATE;
extern irr::IrrlichtDevice	  *Device;
extern SoundEngine            SEngine;
static const unsigned int	maxPlayers = 42;
static const unsigned int	NbScenes = 10;
static const unsigned int	NbWeapons = 5;
static const irr::f32		MOVEMENT_SPEED = 140.f;

static const irr::f32 scalingFactor=1.2f;

#endif
