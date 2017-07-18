//
// Clock.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/UML
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Mon May 22 10:46:46 2017 jurczy_l
// Last update Fri Jun 16 12:30:11 2017 augustin marmus
//

#include	"Clock.hpp"

Clock::Clock()
{
  std::cout << "~~~Constructing CLOCK~~~" << std::endl;
  this->startTime = 0;
  this->pauseTime = 0;
  this->pausedTime = 0;
}

Clock::~Clock()
{}

void		Clock::start()
{this->startTime = Device->getTimer()->getTime();}

irr::u32	Clock::getTime()
{
  return (Device->getTimer()->getTime() - this->startTime - this->pausedTime);
}

void		Clock::pause()
{
  if (pauseTime == 0)
    pauseTime = Device->getTimer()->getTime();
}

void		Clock::play()
{
  this->pausedTime += Device->getTimer()->getTime() - this->pauseTime;
  this->pauseTime = 0;
}

void		Clock::reset()
{
  this->startTime = 0;
  this->pauseTime = 0;
  this->pausedTime = 0;
}
