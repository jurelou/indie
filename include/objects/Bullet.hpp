//
// Bullet.hpp for indie in /home/mafrmus_a/Documents/rendu/cpp_indie_studio
// 
// Made by augustin marmus
// Login   <marmus_a@epitech.eu>
// 
// Started on  Wed Jun 14 11:57:24 2017 augustin marmus
// Last update Wed Jun 14 14:25:03 2017 augustin marmus
//

#ifndef          BULLET_HPP_
# define         BULLET_HPP_

#include	       "IObject.hpp"
#include	       "Physics.hpp"
#include         "Constants.hpp"
#include         "GameInfo.hpp"

class		         Bullet : public virtual IObject, public Physics
{
public:
  Bullet(const irr::core::vector3df& a,
	 const irr::core::vector3df& s,
	 const irr::core::vector3df& p);
  virtual void		update();
  virtual		      ~Bullet();
  virtual void		setPos();
  virtual const irr::core::vector3df& getPos() const;
};

#endif	/* !BULLET_HPP_ */
