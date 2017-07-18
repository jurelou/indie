//
// AGun.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio/include
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Tue Jun 13 20:41:54 2017 jurczy_l
// Last update Sun Jun 18 11:37:40 2017 louis
//

#ifndef                                              KNIFE_HPP_
# define                                             KNIFE_HPP_

#include                                             "AWeapon.hpp"
#include                                             "Bullet.hpp"
#include                                             "irrlicht.h"
#include                                             "Human.hpp"

class                                                Knife : public AWeapon
{
public:
  Knife(irr::scene::ISceneManager *manager, APlayer *origin);
  ~Knife();
  void                                                createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos);
  void                                                checkCollisionWithHuman();
  void                                                update();
  void                                                erase();
  bool		do_end();
private:
  irr::scene::ISceneManager                           *manager;
  irr::scene::IAnimatedMesh                           *mesh;
  irr::scene::IAnimatedMeshSceneNode                  *node;
  irr::core::array<irr::scene::IBillboardSceneNode *> bsn;
  bool							_end;
  bool                                                isTouched;
  bool                                                hasEnded;
  int                                                 currFrame;
  irr::u32                                            then;
  irr::f32                                            currRotation;
  irr::f32                                            frameDeltaTime;
  APlayer                                             *origin;
  Physics                                             *currBullet;
};

#endif
