//
// Knife.cpp for Knife in /home/scalabw/rendu/cpp/cpp_indie_studio/src
// 
// Made by William Scalabre
// Login   <scalabw@epitech.eu>
// 
// Started on  Wed Jun 14 11:47:40 2017 William Scalabre
// Last update Sun Jun 18 17:41:27 2017 louis
//

#include  "Knife.hpp"

Knife::Knife(irr::scene::ISceneManager *manager, APlayer *origin)
{
  _image = Device->getVideoDriver()->getTexture("./misc/skin_weapon/weapon_knife.png");
  target = Constants::GUN;
  this->manager = manager;
  this->nbDamage = 30;
  this->nbAmmu = 1;
  this->currRotation = 0;
  this->mesh = manager->getMesh("./misc/knife.obj");
  if (!(mesh))
    {
      Device->drop();
      exit(84);
    }
  this->node = manager->addAnimatedMeshSceneNode(this->mesh);
  this->node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  this->node->setScale(irr::core::vector3df(10, 10, 10));
  this->node->setPosition(irr::core::vector3df(0, 0, 0));
  this->node->setRotation(irr::core::vector3df(0, this->currRotation, 0));
  _end = false;
  this->origin = origin;
  this->isTouched = false;
  this->node->setMaterialTexture(0, Device->getVideoDriver()->getTexture("./misc/knife.png"));
  for (irr::s32 g = 1; g <= 19; ++g)
    {
      core::stringc tmp;
      tmp = "./misc/knifearm/knife";
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

Knife::~Knife()
{}

void      Knife::erase()
{
  this->bsn[this->currFrame]->setVisible(false);
  this->currFrame = 0;
  this->currBullet = 0;
  this->frameDeltaTime = 0;
  this->isTouched = false;
  this->hasEnded = false;
}

void      Knife::createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos)
{
  if (this->currBullet == 0)
    {
      SEngine.playVoice();
      dir = dir * 5;
      this->hasEnded = false;
      this->currBullet = new Physics(irr::core::vector3df(0, -0.1, 0), dir, pos);
      this->node->setPosition(pos);
      this->node->setVisible(true);
      this->then = Device->getTimer()->getTime();
    }
}

void      Knife::checkCollisionWithHuman()
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
	    SEngine.playKnife();
        }
    }
}

void    Knife::update()
{
  if (this->currBullet != 0)
    {
      if (!(this->isTouched) && frameDeltaTime < 2)
      {
        const irr::u32 now = Device->getTimer()->getTime();
        frameDeltaTime += (irr::f32)(now - then) / 1000.f;
        then = now;
        this->currBullet->update_physics();
        this->node->setPosition(this->currBullet->getPos());
        this->checkCollisionWithHuman();
        this->currRotation += 10;
        this->node->setRotation(irr::core::vector3df(this->currRotation, 0, 0));
      }
      if (this->isTouched)
        {
          const irr::u32 now = Device->getTimer()->getTime();
          frameDeltaTime += (irr::f32)(now - then) / 1000.f;
          then = now;
          if (frameDeltaTime > 0.04f && this->currFrame < 18)
            {
              this->bsn[this->currFrame]->setVisible(false);
              this->currFrame += 1;
              this->bsn[this->currFrame]->setVisible(true);
              this->bsn[this->currFrame]->setPosition(this->bsn[this->currFrame - 1]->getPosition());
              frameDeltaTime = 0;
            }
        }
      if (this->currFrame >= 18 || (!(this->isTouched) && frameDeltaTime > 2))
        {
	        this->hasEnded = true;
          this->bsn[this->currFrame]->setVisible(false);
          this->currFrame = 0;
          this->currBullet = 0;
          this->frameDeltaTime = 0;
          this->isTouched = false;
        }
    }
}

bool                  Knife::do_end()
{
  return (this->hasEnded);
}
