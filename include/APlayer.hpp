//
// APlayer.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio/include
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu Jun  8 13:38:47 2017 jurczy_l
// Last update Sun Jun 18 17:00:01 2017 augustin marmus
//

#ifndef		APLAYER_HPP_
# define	APLAYER_HPP_

#include	"irrlicht.h"
#include	"AWeapon.hpp"

class		APlayer
{
public:
  virtual void		update() = 0;
  virtual irr::core::vector3df	getPosition() const = 0;
  virtual AWeapon	*getWeapon() const = 0;
  virtual irr::scene::IAnimatedMeshSceneNode *getMesh() const = 0;
  virtual int		getHp() const = 0;
  virtual void		takeDamage(irr::u32 damage) = 0;
  virtual irr::core::vector3df		getBulletPos() const = 0;
  virtual void			end_turn() = 0;
  virtual void			die() = 0;

  irr::scene::IAnimatedMeshSceneNode	*_meshNode;
  irr::scene::ITextSceneNode            *textMesh;
  bool			alive;
};

#endif
