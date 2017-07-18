//
// IObject.hpp for indie in /home/marmus_a/Documents/rendu/cpp_indie_studio
// 
// Made by augustin marmus
// Login   <marmus_a@epitech.eu>
// 
// Started on  Wed Jun 14 11:50:44 2017 augustin marmus
// Last update Wed Jun 28 00:38:38 2017 louis
//

#include	"irrlicht.h"
#include	"Constants.hpp"

#ifndef			IOBJECT_HPP_
# define		IOBJECT_HPP_

class		IObject
{
public:
  virtual void				update() = 0;
  virtual const irr::core::vector3df&	getPosition() const = 0;
  virtual void				setPos() = 0;
  virtual irr::scene::IAnimatedMeshSceneNode	*getMesh() const = 0;
  virtual bool				getBoom() const = 0;
  virtual void				setBoom(bool boum) = 0;

  Constants::obj_type			type;
};

#endif		/* !IOBJECT_HPP_  */
