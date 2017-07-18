/*
** Clock.h for Project-Master in /home/louis/Documents/cpp_indie_studio/UML
** 
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
** 
** Started on  Mon May 22 10:45:00 2017 jurczy_l
// Last update Fri Jun 16 12:30:40 2017 augustin marmus
*/

#ifndef		CLOCK_HPP_
# define	CLOCK_HPP_

# include	<string>
# include	<iostream>
# include	"irrlicht.h"
# include	"ITimer.h"
# include	"Constants.hpp"


class		Clock
{
 public:
  Clock();
  ~Clock();

  void			start();
  irr::u32		getTime();
  void			pause();
  void			play();
  void			reset();
private:
  irr::u32	startTime;
  irr::u32	pauseTime;
  irr::u32	pausedTime;
};

#endif
