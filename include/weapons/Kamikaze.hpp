//
// Kamikaze.hpp for Kamikaze in /home/scalabw/rendu/cpp/cpp_indie_studio/include
// 
// Made by William Scalabre
// Login   <scalabw@epitech.eu>
// 
// Started on  Wed Jun 14 11:42:49 2017 William Scalabre
// Last update Sun Jun 18 11:35:35 2017 louis
//

#ifndef		                                           KAMIKAZE_HPP_
# define	                                           KAMIKAZE_HPP_

#include	                                           "AWeapon.hpp"
#include	                                           "irrlicht.h"
#include                                             "Human.hpp"

class		                                             Kamikaze : public AWeapon
{
public:
  Kamikaze(irr::scene::ISceneManager *manager, APlayer *origin);
  ~Kamikaze();
  void                                                createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos);
  void                                                checkCollisionWithHuman();
  void                                                update();
  void                                                erase();
  bool		do_end();
private:
  
  irr::core::aabbox3d<irr::f32>                       radius;
  irr::core::array<irr::scene::IBillboardSceneNode *> bsn;
  APlayer                                             *origin;
  bool							_end;
  bool                                                isFired;
  bool                                                hasEnded;
  bool                                                startFrame;
  int                                                 currFrame;
  irr::u32                                            then;
  irr::f32                                            frameDeltaTime;
};

#endif
