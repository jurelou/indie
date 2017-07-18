/*
** GameInfo.h for Project-Master in /home/louis/Documents/cpp_indie_studio/UML
**
** Made by jurczy_l
** Login   <louis.jurczyk@epitech.eu>
**
** Started on  Mon May 22 10:35:59 2017 jurczy_l
// Last update Wed Jun 28 00:33:52 2017 louis
*/

#ifndef		             GAMEINFO_HPP_
# define	             GAMEINFO_HPP_

#include			<string>
#include			<list>
#include			<map>
#include			"IObject.hpp"
#include			"APlayer.hpp"
#include			"Map.hpp"


struct                 GameInfo
{
  Map                  *_map;
  std::vector<APlayer*>   _players;
  std::vector<IObject*>  _objects;
  int                  _nbPlayers;
  int                  _nbIA;
  bool                 _isRandomMap;
  std::string		_pathMap;
  int			currentPlayer;
  bool			_reset;
  bool			newTurn;
  std::map<Constants::Action, irr::EKEY_CODE>              keys;
};

extern GameInfo               GInfo;

#endif
