//
// Intro.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio/include
// 
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Wed May 24 20:25:40 2017 jurczy_l
// Last update Sun May 28 13:38:22 2017 jurczy_l
//

#ifndef				INTRO_HPP_
# define			INTRO_HPP_

#include			<iostream>
#include			"irrlicht.h"
#include			"Constants.hpp"
#include			"AScene.hpp"
#include			"Event.hpp"

class				Intro : public AScene
{
public:
  Intro(irr::scene::ISceneManager *);
  ~Intro();

  void				update();
  void				drawAll();
  void				setVisible(bool);
  irr::scene::ISceneManager	*getSceneManager() const;  

private:
  irr::scene::ISceneManager	*_manager;
  irr::scene::IAnimatedMeshSceneNode	*node;
  irr::scene::IParticleSystemSceneNode	*ps;
  irr::scene::IAnimatedMesh	*mesh;
  irr::scene::ICameraSceneNode	*cam;
  irr::scene::IParticleEmitter	*em;
  irr::scene::IParticleAffector	*paf;
  irr::video::ITexture		*_images;
  irr::u32	then;
  irr::f32	frameDeltaTime;
  int		x1,y1,z1;
  int		x2, y2, z2;
  bool		isTraveled;
};

#endif
