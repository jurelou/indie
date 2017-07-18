//
// Physics.cpp for  in /home/marmus_a/Documents/rendu/cpp_indie_studio
// 
// Made by augustin marmus
// Login   <marmus_a@epitech.eu>
// 
// Started on  Wed Jun 14 11:27:36 2017 augustin marmus
// Last update Wed Jun 14 14:20:20 2017 augustin marmus
//

#include	"irrlicht.h"

#ifndef		PHYSICS_HPP_
# define	PHYSICS_HPP_

class		Physics
{
public:
  Physics(const irr::core::vector3df& acc,
	  const irr::core::vector3df& speed,
	  const irr::core::vector3df& pos);
  ~Physics();
  void				update_physics();
  const irr::core::vector3df&	getPos() const;

protected:
  irr::core::vector3df	acceleration;
  irr::core::vector3df	speed;
  irr::core::vector3df	pos;
};

#endif	/* !PHYSICS_HPP_ */
