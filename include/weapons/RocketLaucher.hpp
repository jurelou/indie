//
// RocketLaucher.hpp for RocketLaucher in /home/scalabw/rendu/cpp/cpp_indie_studio/include
// 
// Made by William Scalabre
// Login   <scalabw@epitech.eu>
// 
// Started on  Wed Jun 14 11:42:49 2017 William Scalabre
// Last update Wed Jun 28 15:00:57 2017 louis
//

#ifndef		                                           ROCKETLAUCHER_HPP_
# define	                                           ROCKETLAUCHER_HPP_

#include	                                     "AWeapon.hpp"
#include                                             "Bullet.hpp"
#include	                                     "irrlicht.h"
#include                                             "Human.hpp"

class		                                             RocketLaucher : public AWeapon
{
public:
  RocketLaucher(irr::scene::ISceneManager *manager, APlayer *origin);
  ~RocketLaucher();
  void                                                createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos);
  void                                                checkCollisionWithHuman();
  void                                                update();
  void                                                erase();
  bool						     do_end();
  
private:
  irr::scene::ISceneManager                           *manager;
  irr::scene::IAnimatedMesh                           *mesh;
  irr::scene::IAnimatedMeshSceneNode                  *node;
  irr::core::array<irr::scene::IBillboardSceneNode *> bsn;
  bool                                                isTouched;
  bool                                                hasEnded;
  int                                                 currFrame;
  irr::u32                                            then;
  irr::f32                                            frameDeltaTime;
  APlayer                                             *origin;
  Physics                                             *currBullet;
};

#endif
