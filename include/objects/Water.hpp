//
// Water.cpp for cpp_indie_studio in /home/louis/Documents/cpp_indie_studio/src
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Fri Jun 16 18:34:52 2017 louis
//

#ifndef                                 WATER_HPP_
# define                                WATER_HPP_

#include				"irrlicht.h"
#include                                "Constants.hpp"
#include                                "Event.hpp"
#include				"IObject.hpp"
#include				"RealisticWater.h"

class                                   Water : public IObject
{
  public:
  Water(irr::scene::ISceneManager *&manager);
  ~Water();

  void					update();
  const irr::core::vector3df&		getPosition() const;
  void					setPos();
  irr::scene::IAnimatedMeshSceneNode	*getMesh() const;

  void					setBoom(bool boom);
  bool					getBoom() const;
private:
  irr::scene::IAnimatedMesh		*mesh;
   Event				*_event;
  irr::scene::ISceneManager		*_manager;
  irr::scene::IAnimatedMeshSceneNode    *_meshNode;
  irr::f32				_shift;
  RealisticWaterSceneNode		*water;
  bool					_boom;
};

#endif                                  /* !HUMAN_HPP_ */
