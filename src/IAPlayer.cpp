//
// IAPlayer.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Sun Jun 18 21:20:08 2017 f-society
//

#include              <iostream>
#include              <random>
#include              "IAPlayer.hpp"
#include		          "Bullet.hpp"
#include		"Kamikaze.hpp"
#include		"Teleport.hpp"

IAPlayer::IAPlayer(irr::scene::ISceneManager *&manager)
{
  std::cout << "Constructing IAPlayer" << std::endl;
  alive = true;
  _event = static_cast<Event *>(Device->getEventReceiver());
  _manager = manager;
  _bullet = NULL;
  indexWeapon = 0;
  mesh = _manager->getMesh("./misc/WalkingWorm.b3d");
  if (!mesh)
    Device->drop();

  tomb = _manager->getMesh("./misc/gravestone.b3d");
  if (!tomb)
    Device->drop();

  _meshNode = _manager->addAnimatedMeshSceneNode(mesh);
  if (_meshNode)
    {
      _meshNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      _meshNode->setMD2Animation(0);
      _meshNode->setScale(irr::core::vector3df(50, 50, 50));
    }
  int x, y;
  x = std::rand() % 12000;
  y = std::rand() % 12000;
  _meshNode->setPosition(irr::core::vector3df(x, 20000, y));
  _meshNode->setCurrentFrame(15);
  irr::scene::ITriangleSelector *selector
    = _manager->createTerrainTriangleSelector(GInfo._map->getMap(), 0);
  GInfo._map->getMap()->setTriangleSelector(selector);
  irr::u32 then = Device->getTimer()->getTime();
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
  controller=new TPSController;
  {
    irr::scene::ISceneNodeAnimator *anim = new irr::scene::TPSAnimator(controller);
    _meshNode->addAnimator(anim);
    anim->drop();
  }
  textMesh = NULL;
  controller->setDistance(scalingFactor*500.0f);
  controller->setPerson(_meshNode,
			scalingFactor * irr::core::vector3df(0, 350.0f, 0));
  controller->setAnimationNode(_meshNode);
  controller->setBaseAngle(-90.0f);
  controller->setVelocity(0.5f*scalingFactor);
  _hp = 100;
  //on push toutes les armes

  _weapons.push_back(new Gun(_manager, this));
  _weapons.push_back(new RocketLaucher(_manager, this));
  //_weapons.push_back(new Teleport(_manager, this));
  _weapons.push_back(new Kamikaze(_manager, this));
  //_weapons.push_back(new Knife(_manager, this));
  this->target = 0;
}

IAPlayer::~IAPlayer()
{
  std::cout << "Destructing IAPlayer" << std::endl;
}

void			IAPlayer::update_cam()
{
  f32 zMove = 0, xMove = 0, head = 0, pitch = 0, dist = 0;

  if (GInfo.newTurn == true)
    {
      while (GInfo._players[this->target]->getHp() <= 0
	     || GInfo._players[this->target] == this)
	this->target = std::rand() % (GInfo._nbPlayers + GInfo._nbIA);
      GInfo.newTurn == false;
    }
  dist = std::sqrt(std::pow(GInfo._players[this->target]->getPosition().Z - this->getPosition().Z, 2)
		   + std::pow(GInfo._players[this->target]->getPosition().X - this->getPosition().X, 2));
  if (dist > 1000)
    {
      if (GInfo._players[this->target]->getPosition().Z > this->getPosition().Z)
	zMove += 10.0f;
      if (GInfo._players[this->target]->getPosition().Z < this->getPosition().Z)
	zMove -= 10.0f;
      if (GInfo._players[this->target]->getPosition().X > this->getPosition().X)
	xMove += 10.0f;
      if (GInfo._players[this->target]->getPosition().X < this->getPosition().X)
	xMove -= 10.0f;
    }
  else
    this->shoot();
  //controller->setPosition(zMove, xMove);
  irr::core::vector3df p;
  p = this->_meshNode->getPosition();
  p.X += xMove;
  p.Z += zMove;
  this->_meshNode->setPosition(p);
  //controller->move(1.0, 0);
  if (zMove == 0 && xMove == 0)
    _meshNode->setCurrentFrame(15);
  if (_event->isKeyPressed(GInfo.keys[Constants::SELECT]))
    {
      indexWeapon++;
      indexWeapon %= 3;
    }
  if(!(std::rand() % 10000))
    controller->jump();
  if(_event->isKeyDown(GInfo.keys[Constants::LEFT]))
    head=-1.0f;
  if(_event->isKeyDown(GInfo.keys[Constants::RIGHT]))
    head=1.0f;
  if(_event->isKeyDown(GInfo.keys[Constants::DOWN]))
    pitch=-1.0f;
  else if(_event->isKeyDown(GInfo.keys[Constants::UP]))
    pitch=1.0f;
  irr::core::vector3df	tmp = this->getPosition();
  tmp.Y += 300;
  controller->getCamera()->setPosition(tmp);
  controller->getCamera()->setTarget(GInfo._players[this->target]->getPosition());
  //controller->updateCamera();
  //controller->getCamera()->setTarget(GInfo._players[this->target]->getPosition());
}

void                  IAPlayer::update()
{
  if (_hp <= 0 ||  _meshNode->getPosition().Y <= 0)
    {
      if (this->alive == true)
	this->die();
      return;
    }
  this->update_cam();
  _weapons.at(indexWeapon)->update();
}

void		     IAPlayer::create_bullet()
{
}

void                  IAPlayer::shoot()
{
  irr::core::vector3df		dir;
  irr::core::vector3df		pos;
  irr::f32			dist;

  this->indexWeapon = std::rand() % 3;
  dir = -this->_manager->getActiveCamera()->getPosition();;
  dir += GInfo._players[this->target]->getPosition();
  dir.Y += 500;
  dist = sqrt(dir.X * dir.X + dir.Y * dir.Y + dir.Z * dir.Z);
  dir /= dist;
  dir *= 50.;
  pos = this->getPosition();
  pos.Y += 100;
  _weapons.at(indexWeapon)->createNewBullet(dir, pos);
}

irr::core::vector3df	IAPlayer::getPosition() const
{  return (this->_meshNode->getPosition()); }

irr::scene::IAnimatedMeshSceneNode *IAPlayer::getMesh() const
{   return (this->_meshNode); }

AWeapon			*IAPlayer::getWeapon() const
{  return (_weapons.at(indexWeapon)); }

int		IAPlayer::getHp() const
{ return(_hp); }

void			IAPlayer::takeDamage(irr::u32 damage)
{
  _hp -= damage;
}

irr::core::vector3df		IAPlayer::getBulletPos() const
{
  if (_bullet)
    return(_bullet->getPosition());
  return (irr::core::vector3df(0.0, 0.0, 0.0));
}

void				IAPlayer::end_turn()
{
  _weapons.at(indexWeapon)->erase();
}

void				IAPlayer::die()
{
  this->alive = false;
  _meshNode->setMesh(this->tomb);
  _meshNode->setMaterialTexture(0, Device->getVideoDriver()->getTexture("misc/cursed_grave.png"));
  _meshNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _meshNode->setScale(irr::core::vector3df(400, 400, 400));
}
