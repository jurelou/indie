//
// Human.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Wed Jun 28 15:11:25 2017 louis
//

#include              <iostream>
#include              <random>
#include              "Human.hpp"
#include	      "Bullet.hpp"

Human::Human(irr::scene::ISceneManager *&manager)
{
  std::cout << "Constructing Human" << std::endl;
  _event = static_cast<Event *>(Device->getEventReceiver());
  alive  = true;
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
  _weapons.push_back(new Gun(_manager, this));
  _weapons.push_back(new RocketLaucher(_manager, this));
  _weapons.push_back(new Teleport(_manager, this));
  _weapons.push_back(new Kamikaze(_manager, this));
  _weapons.push_back(new Knife(_manager, this));
}

Human::~Human()
{
  std::cout << "Destructing Human" << std::endl;
}

void			Human::update_cam()
{
  f32 zMove = 0, xMove = 0, head = 0, pitch = 0;

  if (_event->isKeyDown(GInfo.keys[Constants::FRONT]))
    zMove=1.0f;
  else if (_event->isKeyDown(GInfo.keys[Constants::BEHIND]))
    zMove=-1.0f;
  if (_event->isKeyDown(GInfo.keys[Constants::GO_LEFT]))
    xMove=-1.0f;
  else if (_event->isKeyDown(GInfo.keys[Constants::GO_RIGHT]))
    xMove=1.0f;
  if (zMove == 0 && xMove == 0)
    _meshNode->setCurrentFrame(15);
  controller->move(xMove, zMove);
  if (_event->isKeyPressed(GInfo.keys[Constants::SELECT]))
    {
      indexWeapon++;
      indexWeapon %= NbWeapons;
    }
  if(_event->isKeyDown(GInfo.keys[Constants::JUMP]))
    controller->jump();
  if(_event->isKeyDown(GInfo.keys[Constants::LEFT]))
    head=-1.0f;
  if(_event->isKeyDown(GInfo.keys[Constants::RIGHT]))
    head=1.0f;
  if(_event->isKeyDown(GInfo.keys[Constants::DOWN]))
    pitch=-1.0f;
  else if(_event->isKeyDown(GInfo.keys[Constants::UP]))
    pitch=1.0f;
  controller->rotate(head, pitch);
  controller->updateCamera();
}

void                  Human::update()
{
  irr::core::vector3df _meshNodePosition = _meshNode->getPosition();
  if (_hp <= 0 || _meshNodePosition.Y <= 0)
    {
      if (this->alive == true)
	  this->die();
      return;
    }
  this->update_cam();
  _weapons.at(indexWeapon)->update();
  static float bullet_speed = 0.0f;
  const irr::u32 now = Device->getTimer()->getTime();
  const irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
  then = now;

  if(_event->isKeyDown(GInfo.keys[Constants::UP]))
    _meshNodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
  if(_event->isKeyDown(GInfo.keys[Constants::DOWN]))
    _meshNodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
  if(_event->isKeyDown(GInfo.keys[Constants::LEFT]))
    _meshNodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
  if(_event->isKeyDown(GInfo.keys[Constants::RIGHT]))
    _meshNodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
  if(_event->isKeyPressed(GInfo.keys[Constants::ATTACK]))
    this->shoot();
}

void		     Human::create_bullet()
{
}

void                  Human::shoot()
{
  irr::core::vector3df		dir;
  irr::core::vector3df		pos;
  irr::f32			dist;

  dir = -this->_manager->getActiveCamera()->getPosition();
  dir += this->getPosition();
  dir.Y += 420;
  dist = sqrt(dir.X * dir.X + dir.Y * dir.Y + dir.Z * dir.Z);
  dir /= dist;
  dir *= 50.;
  pos = this->getPosition();
  pos.Y += 300;
  _weapons.at(indexWeapon)->createNewBullet(dir, pos);
}

irr::core::vector3df	Human::getPosition() const
{  return (this->_meshNode->getPosition()); }

irr::scene::IAnimatedMeshSceneNode *Human::getMesh() const
{   return (this->_meshNode); }

AWeapon			*Human::getWeapon() const
{  return (_weapons.at(indexWeapon)); }

int		Human::getHp() const
{ return(_hp); }

void			Human::takeDamage(irr::u32 damage)
{
  _hp -= damage;
}

irr::core::vector3df            Human::getBulletPos() const
{
  if (_bullet)
    return(_bullet->getPosition());
  return (irr::core::vector3df(0.0, 0.0, 0.0));
}

void				Human::end_turn()
{
  _weapons.at(indexWeapon)->erase();
}

void				Human::die()
{
  this->alive = false;
  _meshNode->setMesh(this->tomb);
  _meshNode->setMaterialTexture(0, Device->getVideoDriver()->getTexture("misc/cursed_grave.png"));
  _meshNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  _meshNode->setScale(irr::core::vector3df(400, 400, 400));
  if (textMesh != NULL)
    textMesh->setVisible(false);
}
