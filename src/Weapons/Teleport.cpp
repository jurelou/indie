//
// Teleport.cpp for Teleport in /home/scalabw/rendu/cpp/cpp_indie_studio/src
// 
// Made by William Scalabre
// Login   <scalabw@epitech.eu>
// 
// Started on  Wed Jun 14 11:50:28 2017 William Scalabre
// Last update Sun Jun 18 17:43:17 2017 louis
//

#include	"Teleport.hpp"

Teleport::Teleport(irr::scene::ISceneManager *manager, APlayer *origin)
{
  target = Constants::GUN;
  _image = Device->getVideoDriver()->getTexture("./misc/skin_weapon/weapon_teleport.png");
  nbDamage = 0;
  nbAmmu = 1;
  this->manager = manager;
  this->origin = origin;
  this->hasTravelled = false;
  this->selectedSceneNode = 0;
  this->inter = irr::core::vector3df(0, 0, 0);
  this->hasEnded = false;
}

Teleport::~Teleport()
{}

void     Teleport::erase()
{
  this->hasTravelled = false;
  this->selectedSceneNode = 0;
  this->hasEnded = false;
}

void     Teleport::createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos)
{
  this->ray.start = pos;
  for (int i = 0; i < 2000; i++)
    pos += dir;
  this->ray.end = ray.start + (pos - ray.start).normalize() * 10000.0f;
  this->hasTravelled = true;
  this->hasEnded = false;
}

void     Teleport::checkCollisionWithHuman()
{
  this->selectedSceneNode =
            this->manager->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
                    this->ray,
                    this->inter,
                    this->hitTriangle,
                    0,
                    0);
  if (this->inter.X != 0 && this->inter.Y != 0 && this->inter.Z != 0 && origin->getPosition() != this->inter)
    {
      this->inter.Y += 100;
      this->origin->_meshNode->setPosition(this->inter);
      this->hasTravelled = false;
      this->hasEnded = true;
      if (!SEngine.getMute())
	SEngine.playTeleport();
    }
}

void     Teleport::update()
{
  if (this->hasTravelled)
    {
      this->checkCollisionWithHuman();
    }
}

bool                  Teleport::do_end()
{
  return (this->hasEnded);
}
