//
// Physics.cpp for indoe in /home/marmus_a/Documents/rendu/cpp_indie_studio
// 
// Made by augustin marmus
// Login   <marmus_a@epitech.eu>
// 
// Started on  Wed Jun 14 11:35:47 2017 augustin marmus
// Last update Wed Jun 14 12:20:29 2017 augustin marmus
//

#include		"Physics.hpp"

Physics::Physics(const irr::core::vector3df& a,
		 const irr::core::vector3df& s,
		 const irr::core::vector3df& p)
{
  this->acceleration = a; 
  this->speed = s;
  this->pos = p;
}

Physics::~Physics()
{}

void				Physics::update_physics()
{
  this->speed = this->acceleration + this->speed;
  this->pos = this->pos + this->speed;
}

const irr::core::vector3df&	Physics::getPos() const
{return (this->pos);}
