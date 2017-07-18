//
// Game.hpp for indie in /home/marmus_a/Documents/rendu/cpp_indie_studio
//
// Made by augustin marmus
// Login   <marmus_a@epitech.eu>
//
// Started on  Fri May 26 11:16:56 2017 augustin marmus
// Last update Sun Jun 18 20:27:19 2017 louis
//

#include		<iostream>

#include		<math.h>


#include		"irrlicht.h"
#include		"Constants.hpp"
#include		"Human.hpp"
#include		"GameInfo.hpp"
#include		"Event.hpp"
#include		"AScene.hpp"
#include		"Map.hpp"
#include		"Clock.hpp"
//objects
#include                "IObject.hpp"
#include                "Tree.hpp"
#include		"Barrel.hpp"
#include		"Water.hpp"

#ifndef			PLAY_HPP_
# define		PLAY_HPP_

class			Play : public AScene
{
public:
  Play(irr::scene::ISceneManager *parent);
  ~Play();

  void			update();
  void			update_overlay();
  void			update_cam();
  void			update_players();
  void			drawAll();
  virtual void		setVisible(bool state);
  void		        setGameInfo(GameInfo *info);
  irr::scene::ISceneManager	*getSceneManager() const;

protected:
  irr::scene::ISceneManager	*_manager;
  irr::scene::ITextSceneNode	*_textWeapon;
  irr::scene::ICameraSceneNode	*_cam;
  irr::scene::ISceneNode	*_rootNode;
  irr::gui::IGUIFont		*_font;
  irr::f32			_shift;
  irr::f32			_mov;
  irr::f32			_a;
  irr::video::ITexture		*_crosshair;
  irr::video::ITexture		*_crosshair_b;
  irr::video::ITexture		*_weapon;
  irr::scene::IParticleSystemSceneNode  *ps;
  irr::scene::IParticleEmitter  *em;
  irr::scene::IParticleAffector *paf;
  Clock				_clock;
  irr::f32			_watershift;
  irr::u32			_start;
};

#endif			/* !PLAY_HPP_*/
