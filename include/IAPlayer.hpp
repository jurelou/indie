//
// Human.cpp for cpp_indie_studio in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Tue Jun 27 15:24:14 2017 louis
//

#ifndef                                 IAPLAYER_HPP_
# define                                IAPLAYER_HPP_

#include                                "Constants.hpp"
#include                                "Event.hpp"
#include				"GameInfo.hpp"
#include                                "APlayer.hpp"
#include				"AWeapon.hpp"
#include				"Gun.hpp"
#include				"Kamikaze.hpp"
#include				"Teleport.hpp"
#include				"Knife.hpp"
#include				"RocketLaucher.hpp"
#include				"../lib/include/irrlicht_tps_camera.hpp"

class                                   IAPlayer : public APlayer
{
  public:
  IAPlayer(irr::scene::ISceneManager *&manager);
  ~IAPlayer();
  void                                update();
  void                                shoot();
  irr::scene::IAnimatedMeshSceneNode *getMesh() const;
  irr::core::vector3df		      getPosition() const;
  void					update_cam();
  irr::scene::IAnimatedMesh           *mesh;
  irr::scene::IAnimatedMesh           *tomb;
  TPSController                 *controller;
  int				getHp() const;
  AWeapon			*getWeapon() const;
  virtual void				takeDamage(irr::u32 damage);
  irr::core::vector3df			getBulletPos() const;
  void					end_turn();
  void					die();
private:
  std::vector<AWeapon *>		_weapons;
  void					create_bullet();
  Event                               *_event;
  irr::scene::ISceneManager           *_manager;
  irr::scene::ISceneNode		*_bullet;
  irr::u32				then;
  int					indexWeapon;
  irr::u32				_hp;
  irr::u32				target;
};

#endif                                  /* !IAPLAYER_HPP_ */
