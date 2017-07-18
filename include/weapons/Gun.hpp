//
// AGun.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio/include
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Tue Jun 13 20:41:54 2017 jurczy_l
// Last update Sun Jun 18 13:35:48 2017 louis
//

#ifndef                                              GUN_HPP_
# define                                             GUN_HPP_

#include                                             "AWeapon.hpp"
#include                                             "Bullet.hpp"
#include                                             "irrlicht.h"
#include                                             "Human.hpp"

class                                                Gun : public AWeapon
{
public:
  Gun(irr::scene::ISceneManager *manager, APlayer *origin);
  ~Gun();
  void                                                createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos);
  bool							do_end();
  void                                                checkCollisionWithHuman();
  void                                                update();
  void                                                erase();
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
