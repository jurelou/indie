/*
** AWeapon.h for Indie in /home/spring_r/Project/cpp_indie_studio/UML
** 
** Made by Springer-Roy Romain
** Login   <spring_r@epitech.eu>
** 
** Started on  Thu May 25 13:10:57 2017 Springer-Roy Romain
// Last update Wed Jun 28 13:31:34 2017 louis
*/
#ifndef		AWEAPON_HPP_
# define	AWEAPON_HPP_

#include	"irrlicht.h"
#include	"Constants.hpp"

class		AWeapon
{
public:
  void			setDamage(unsigned short int dam);
  unsigned short int	getDamage() const;
  void			setAmmu(unsigned short int ammu);
  unsigned short int	getAmmu() const;
  irr::video::ITexture  *getImage() const;
  virtual bool		do_end() = 0;
  virtual void		createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos) = 0;
  virtual void		update() = 0;
  virtual void		erase() = 0;

  Constants::target_type	target;
protected:
  unsigned short int	nbDamage;
  unsigned short int	nbAmmu;
  irr::video::ITexture  *_image;
};

#endif
