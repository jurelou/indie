//
// Tree.cpp for cpp_indie_studio in /home/louis/Documents/cpp_indie_studio/src
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Fri Jun 16 14:17:49 2017 louis
//

#ifndef                                 BARREL_HPP_
# define                                BARREL_HPP_

#include				"irrlicht.h"
#include                                "Constants.hpp"
#include                                "Event.hpp"
#include				"IObject.hpp"

class                                   Barrel : public IObject
{
  public:
  Barrel(irr::scene::ISceneManager *&manager);
  ~Barrel();

  void					update();
  const irr::core::vector3df&		getPosition() const;
  void					setPos();
  irr::scene::IAnimatedMeshSceneNode	*getMesh() const;
  
  void					setBoom(bool boum);
  bool					getBoom() const;
private:
  irr::scene::IAnimatedMesh		*mesh;
  Event					*_event;
  irr::scene::ISceneManager		*_manager;
  irr::scene::IAnimatedMeshSceneNode    *_meshNode;

  bool					_boum;
};

#endif                                  /* !HUMAN_HPP_ */
