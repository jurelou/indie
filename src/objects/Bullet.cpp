//
// Bullet.cpp for indie in /home/marmus_a/Documents/rendu/cpp_indie_studio
// 
// Made by augustin marmus
// Login   <marmus_a@epitech.eu>
// 
// Started on  Wed Jun 14 12:01:31 2017 augustin marmus
// Last update Wed Jun 14 14:35:01 2017 augustin marmus
//

#include	<iostream>
#include	<string>
#include	"Bullet.hpp"

Bullet::Bullet(const irr::core::vector3df& a,
	       const irr::core::vector3df& s,
	       const irr::core::vector3df& p) : Physics(a, s, p)
{}

Bullet::~Bullet()
{}

const irr::core::vector3df&	Bullet::getPos() const
{
  Physics::getPos();
}

void		Bullet::update()
{
  this->update_physics();
}

void		Bullet::setPos()
{}
