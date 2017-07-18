//
// Teleport.hpp for Teleport in /home/scalabw/rendu/cpp/cpp_indie_studio/include
// 
// Made by William Scalabre
// Login   <scalabw@epitech.eu>
// 
// Started on  Wed Jun 14 11:42:49 2017 William Scalabre
// Last update Sun Jun 18 02:57:30 2017 louis
//

#ifndef		                                           TELEPORT_HPP_
# define	                                           TELEPORT_HPP_

#include	                                           "AWeapon.hpp"
#include	                                           "irrlicht.h"
#include                                             "Human.hpp"

class		                                             Teleport : public AWeapon
{
public:
  Teleport(irr::scene::ISceneManager *manager, APlayer *origin);
  ~Teleport();
  void                                                createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos);
  void                                                checkCollisionWithHuman();
  void                                                update();
  void                                                erase();
  bool		do_end();
private:
  irr::scene::ISceneManager                           *manager;
  irr::scene::ISceneNode                              *selectedSceneNode;
  irr::core::vector3df                                inter;
  irr::core::triangle3df                              hitTriangle;
  irr::core::line3d<irr::f32>                         ray;
  bool                                                hasTravelled;
  bool                                                hasEnded;
  APlayer                                             *origin;
};

#endif
