//
// RocketLaucher.cpp for RocketLaucher in /home/scalabw/rendu/cpp/cpp_indie_studio/src
// 
// Made by William Scalabre
// Login   <scalabw@epitech.eu>
// 
// Started on  Wed Jun 14 11:47:40 2017 William Scalabre
// Last update Sun Jun 18 18:03:49 2017 augustin marmus
//

#include	"RocketLaucher.hpp"

RocketLaucher::RocketLaucher(irr::scene::ISceneManager *manager, APlayer *origin)
{
  target = Constants::ROCKET;
  _image = Device->getVideoDriver()->getTexture("./misc/skin_weapon/weapon_baz.png");
  this->manager = manager;
  this->nbDamage = 30;
  this->nbAmmu = 1;
  this->mesh = manager->getMesh("./misc/missile.obj");
  this->node = manager->addAnimatedMeshSceneNode(this->mesh);
  this->node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->node->setScale(irr::core::vector3df(40, 40, 40));
  this->node->setPosition(irr::core::vector3df(-100, -100, -100));
  this->node->setRotation(irr::core::vector3df(0, 90, 0));
  this->origin = origin;
  this->isTouched = false;
  this->node->setMaterialTexture(0, Device->getVideoDriver()->getTexture("./misc/missile.png"));
  for (irr::s32 g = 1; g <= 19; ++g)
    {
      core::stringc tmp;
      tmp = "./misc/explosion/explosion";
      tmp += g;
      tmp += ".png";
      irr::scene::IBillboardSceneNode* t = manager->addBillboardSceneNode(0, irr::core::dimension2d<f32>(1500, 1500));
      t->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      t->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
      t->setMaterialTexture(0, Device->getVideoDriver()->getTexture(tmp));
      t->setVisible(false);
      this->bsn.push_back(t);
    }
  this->currFrame = 0;
  this->frameDeltaTime = 0;
  this->currBullet = 0;
  this->hasEnded = false;
}

RocketLaucher::~RocketLaucher()
{}

void      RocketLaucher::erase()
{
  this->bsn[this->currFrame]->setVisible(false);
  this->currFrame = 0;
  this->currBullet = 0;
  this->frameDeltaTime = 0;
  this->isTouched = false;
  this->hasEnded = false;
}

void      RocketLaucher::createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos)
{
  if (this->currBullet == 0)
    {
      if (!SEngine.getMute())
	SEngine.playVoice();
      dir.Y += 10;
      dir *= 1.7;
      pos.Y -= 200;
      this->hasEnded = false;
      this->currBullet = new Physics(irr::core::vector3df(0, -0.9, 0), dir, pos);
      this->node->setPosition(pos);
      this->node->setVisible(true);
      this->then = Device->getTimer()->getTime();
    }
}

void      RocketLaucher::checkCollisionWithHuman()
{
  irr::core::aabbox3d<irr::f32> box;
  irr::core::aabbox3d<irr::f32> boxBullet;

  boxBullet = this->node->getTransformedBoundingBox();
  for (auto it: GInfo._players)
    {
      if (it->getMesh()->getTransformedBoundingBox().intersectsWithBox(boxBullet) && origin->getPosition() != it->getPosition())
        {
          this->isTouched = true;
          this->then = Device->getTimer()->getTime();
          this->frameDeltaTime = 0;
          this->node->setVisible(false);
          this->bsn[this->currFrame]->setVisible(true);
          this->bsn[this->currFrame]->setPosition(it->getPosition());
	  it->takeDamage(this->getDamage());
	  if (it->getHp() < 0)
	    it->die();
	  if (!SEngine.getMute())
	    SEngine.playExplosion();
        }
    }
  for (auto it: GInfo._objects)
    {
      if (it->type == Constants::BARREL && it->getMesh()->getTransformedBoundingBox().intersectsWithBox(boxBullet) && \
	  origin->getPosition() != it->getPosition())
	{
	  this->isTouched = true;
	  this->then = Device->getTimer()->getTime();
	  this->frameDeltaTime = 0;
	  this->node->setVisible(false);
	  this->bsn[this->currFrame]->setVisible(true);
	  this->bsn[this->currFrame]->setPosition(it->getPosition());
	  it->setBoom(true);
	}
    }
  for (int i = 0; i < GInfo._objects.size(); i++)
    {
      if (GInfo._objects.at(i)->getBoom() == true)
	{
	  GInfo._objects.at(i)->getMesh()->remove();
	  GInfo._objects.erase(GInfo._objects.begin() + i);
	}
    }
}

void    RocketLaucher::update()
{
  if (this->currBullet != 0)
    {
      if (!(this->isTouched))
        {
          const irr::u32 now = Device->getTimer()->getTime();
          frameDeltaTime += (irr::f32)(now - then) / 1000.f;
          then = now;
          this->currBullet->update_physics();
          this->node->setPosition(this->currBullet->getPos());
          this->checkCollisionWithHuman();
        }
      if (this->isTouched)
        {
          const irr::u32 now = Device->getTimer()->getTime();
          frameDeltaTime += (irr::f32)(now - then) / 1000.f;
          then = now;
          if (frameDeltaTime > 0.02f && this->currFrame < 18)
            {
              this->bsn[this->currFrame]->setVisible(false);
              this->currFrame += 1;
              this->bsn[this->currFrame]->setVisible(true);
              this->bsn[this->currFrame]->setPosition(this->bsn[this->currFrame - 1]->getPosition());
              frameDeltaTime = 0;
            }
        }
      if (this->currFrame >= 18 || (frameDeltaTime > 8 && !(this->isTouched)))
        {
          this->bsn[this->currFrame]->setVisible(false);
          this->currFrame = 0;
          this->currBullet = 0;
          this->frameDeltaTime = 0;
          this->isTouched = false;
          this->hasEnded = true;
        }
    }
}


bool                  RocketLaucher::do_end()
{
  return (this->hasEnded);
}
