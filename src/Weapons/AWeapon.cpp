/*
** AWeapon.h for Indie in /home/spring_r/Project/cpp_indie_studio/UML
** 
** Made by Springer-Roy Romain
** Login   <spring_r@epitech.eu>
** 
** Started on  Thu May 25 13:10:57 2017 Springer-Roy Romain
// Last update Tue Jun 13 21:34:46 2017 jurczy_l
*/

#include	"AWeapon.hpp"

void			AWeapon::setDamage(unsigned short int dam)
{
  this->nbDamage = dam;
}

unsigned short int	AWeapon::getDamage() const
{
  return this->nbDamage;
}

void			AWeapon::setAmmu(unsigned short int ammu)
{
  this->nbAmmu = ammu;
}

unsigned short int	AWeapon::getAmmu() const
{
  return this->nbAmmu;
}

irr::video::ITexture    *AWeapon::getImage() const                                
{
  return (_image);
}
