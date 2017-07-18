//
// Tree.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Sat Jun 17 22:29:20 2017 louis
//

#include              <iostream>
#include              <random>
#include              "Water.hpp"

Water::Water(irr::scene::ISceneManager *&manager)
{
  type = Constants::WATER;
  std::cout << "Constructing Water" << std::endl;
  _event = static_cast<Event *>(Device->getEventReceiver());
  _manager = manager;
  _shift = 0.;
  _boom = false;
  water = new RealisticWaterSceneNode(_manager, 100000.0f, 100000.0f, "./misc/map/");

  _manager->getRootSceneNode()->addChild(water);

  water->setPosition(irr::core::vector3df(0,500 ,0));
}

Water::~Water()
{
  std::cout << "Destructing Water" << std::endl;
}

void			Water::update()
{
  // _shift += 0.25;
  // water->setPosition(irr::core::vector3df(0,500 + _shift,0));
}

irr::scene::IAnimatedMeshSceneNode	*Water::getMesh() const
{ return (_meshNode); }

const irr::core::vector3df&	Water::getPosition() const
{  return (this->_meshNode->getPosition()); }


void			Water::setPos()
{}

bool			Water::getBoom() const
{ return (false); }

void			Water::setBoom(bool boom)
{  _boom = boom; }
