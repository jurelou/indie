//
// Game.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Wed May 17 11:51:04 2017 jurczy_l
// Last update Wed Jun 28 11:15:31 2017 louis
//

#include	"Game.hpp"

Game::Game(bool fullscreen)
{
  this->_gfxEngine = new GraphicalEngine(fullscreen);
  WINDOW_STATE = Constants::INTRO;
  lastFPS = -1;

  GInfo.keys[Constants::FRONT] = irr::KEY_KEY_Z;
  GInfo.keys[Constants::BEHIND] = irr::KEY_KEY_S;
  GInfo.keys[Constants::GO_LEFT] = irr::KEY_KEY_Q;
  GInfo.keys[Constants::GO_RIGHT] = irr::KEY_KEY_D;
  GInfo.keys[Constants::ATTACK] = irr::KEY_KEY_T;
  GInfo.keys[Constants::SELECT] = irr::KEY_KEY_C;
  GInfo.keys[Constants::JUMP] = irr::KEY_SPACE;
  GInfo.keys[Constants::SUICID] = irr::KEY_KEY_P;
  GInfo.keys[Constants::UP] = irr::KEY_UP;
  GInfo.keys[Constants::DOWN] = irr::KEY_DOWN;
  GInfo.keys[Constants::LEFT] = irr::KEY_LEFT;
  GInfo.keys[Constants::RIGHT] = irr::KEY_RIGHT;
}

Game::~Game()
{}

void		Game::run()
{
  while (Device->run())
    {
      _gfxEngine->draw();
    }
  delete _gfxEngine;
}

void		Game::update()
{

}
