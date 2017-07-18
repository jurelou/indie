//
// Barel.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Sat Jun 17 16:44:11 2017 augustin marmus
//

#include	              <iostream>
#include		      <random>
#include		      "Barrel.hpp"
#include		      "Bullet.hpp"

Barrel::Barrel(irr::scene::ISceneManager *&manager)
{
  type = Constants::BARREL;
  std::cout << "Constructing Barrel" << std::endl;
  _event = static_cast<Event *>(Device->getEventReceiver());
  _manager = manager;
  mesh = _manager->getMesh("./misc/Tree/barrel.3ds");
  _boum = false;
  if (!mesh)
    Device->drop();
  _meshNode = _manager->addAnimatedMeshSceneNode(mesh);
  if (_meshNode)
    {
      _meshNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      _meshNode->setScale(irr::core::vector3df(400, 400, 400));
    }
  int x, y;
  x = std::rand() % 16800;
  y = std::rand() % 16800;
  _meshNode->setPosition(irr::core::vector3df(x, 1500, y));
  _meshNode->setCurrentFrame(15);



  
  irr::scene::ITriangleSelector *selector
    = _manager->createTerrainTriangleSelector(GInfo._map->getMap(), 0);
  GInfo._map->getMap()->setTriangleSelector(selector);





  const irr::core::aabbox3d<irr::f32>& box = _meshNode->getBoundingBox();
  irr::core::vector3df radius = box.MaxEdge - box.getCenter();
  irr::scene::ISceneNodeAnimator *anim =		\
    _manager->createCollisionResponseAnimator(selector,
					      _meshNode,
					      radius,
					      irr::core::vector3df(0,-10,0),
					      irr::core::vector3df(0,0,0),
					      0.5);
  selector->drop();
  _meshNode->addAnimator(anim);
  anim->drop();
}

Barrel::~Barrel()
{
  std::cout << "Destructing Barrel" << std::endl;
}

void			Barrel::update()
{
}

const irr::core::vector3df&	Barrel::getPosition() const
{  return (this->_meshNode->getPosition()); }


void			Barrel::setPos()
{}

irr::scene::IAnimatedMeshSceneNode *Barrel::getMesh() const
{  return (_meshNode); }

void			Barrel::setBoom(bool boum)
{  _boum = boum; }

bool			Barrel::getBoom() const
{ return (_boum); }
