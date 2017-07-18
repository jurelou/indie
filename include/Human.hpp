//
// Human.cpp for cpp_indie_studio in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Tue Jun 27 15:23:39 2017 louis
//

#ifndef                                 HUMAN_HPP_
# define                                HUMAN_HPP_

#include                                "Constants.hpp"
#include                                "Event.hpp"
#include				"GameInfo.hpp"
#include				"irrlicht.h"
#include                                "APlayer.hpp"
#include				"AWeapon.hpp"
#include				"Gun.hpp"
#include				"Kamikaze.hpp"
#include				"Teleport.hpp"
#include				"Knife.hpp"
#include				"RocketLaucher.hpp"
#include				"../lib/include/irrlicht_tps_camera.hpp"

class                                   Human : public APlayer
{
  public:
  Human(irr::scene::ISceneManager *&manager);
  ~Human();
  void                                update();
  void                                shoot();
  irr::scene::IAnimatedMeshSceneNode *getMesh() const;
  irr::core::vector3df		      getPosition() const;
  void					update_cam();
  irr::scene::IAnimatedMesh           *mesh;
  irr::scene::IAnimatedMesh           *tomb;
  TPSController                 *controller;
  irr::core::vector3df                  getBulletPos() const;
  int				getHp() const;
  AWeapon			*getWeapon() const;
  virtual void				takeDamage(irr::u32 damage);
  void					end_turn();
  void					die();
private:
  irr::scene::ISceneNode		*_bullet;
  std::vector<AWeapon *>		_weapons;
  void					create_bullet();
  Event                               *_event;
  irr::scene::ISceneManager           *_manager;
  irr::u32				then;
  int					indexWeapon;
  int				_hp;
};

#endif                                  /* !HUMAN_HPP_ */
