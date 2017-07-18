//
// Tree.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Fri Jun 16 18:33:13 2017 louis
//

#include              <iostream>
#include              <random>
#include              "Tree.hpp"
#include		          "Bullet.hpp"

Tree::Tree(irr::scene::ISceneManager *&manager)
{
  type = Constants::PLANE;
  std::cout << "Constructing Tree" << std::endl;
  _event = static_cast<Event *>(Device->getEventReceiver());
  _manager = manager;
  _shift = 0.;
  _boom = false;
  mesh = _manager->getMesh("./misc/Tree/vimy.obj");
  if (!mesh)
    Device->drop();

  _meshNode = _manager->addAnimatedMeshSceneNode(mesh);
  if (_meshNode)
    {
      _meshNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      _meshNode->setScale(irr::core::vector3df(5, 5, 5));
    }

  int x, y;
  x = std::rand() % 12000;
  y = std::rand() % 12000;
  //  _meshNode->setPosition(irr::core::vector3df(x, 5000, y));
  //_meshNode->setCurrentFrame(15);
  _rand  = 5000 + std::rand() % 9000;
  _meshNode->setPosition(irr::core::vector3df(_rand * cos(_shift) + _rand, 5000, _rand * sin(_shift) + _rand));

  irr::scene::ITriangleSelector *selector
    = _manager->createTerrainTriangleSelector(GInfo._map->getMap(), 0);
  GInfo._map->getMap()->setTriangleSelector(selector);


  const irr::core::aabbox3d<irr::f32>& box = _meshNode->getBoundingBox();
  irr::core::vector3df radius = box.MaxEdge - box.getCenter();
  irr::scene::ISceneNodeAnimator *anim =		\
    _manager->createCollisionResponseAnimator(selector,
					      _meshNode,
					      radius,
					      irr::core::vector3df(0,0,0),
					      irr::core::vector3df(0,0,0),
					      0.5);
  selector->drop();
  _meshNode->addAnimator(anim);
  anim->drop();
}

Tree::~Tree()
{
  std::cout << "Destructing Tree" << std::endl;
}

void			Tree::update()
{
  _meshNode->setPosition(irr::core::vector3df(_rand * cos(_shift) + _rand, 5000, _rand * sin(_shift) + _rand));
  _shift += 0.01;
  if (_shift > 2 * M_PI)
    _shift -= 2 * M_PI;
  _meshNode->setRotation(irr::core::vector3df(0,0,1));
}

irr::scene::IAnimatedMeshSceneNode	*Tree::getMesh() const
{ return (_meshNode);}

const irr::core::vector3df&	Tree::getPosition() const
{  return (this->_meshNode->getPosition()); }


void			Tree::setPos()
{}

bool			Tree::getBoom() const
{ return (_boom); }

void			Tree::setBoom(bool boom)
{  _boom = boom; }
