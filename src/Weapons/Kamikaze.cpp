//
// Kamikaze.cpp for Kamikaze in /home/scalabw/rendu/cpp/cpp_indie_studio/src
// 
// Made by William Scalabre
// Login   <scalabw@epitech.eu>
// 
// Started on  Wed Jun 14 11:49:46 2017 William Scalabre
// Last update Sun Jun 18 17:43:02 2017 louis
//

#include	"Kamikaze.hpp"

Kamikaze::Kamikaze(irr::scene::ISceneManager *manager, APlayer *origin)
{
  _image = Device->getVideoDriver()->getTexture("./misc/skin_weapon/weapon_kamikaze.png");
  target = Constants::NO;
  _end = false;
  this->nbDamage = 999;
  this->nbAmmu = 1;
  this->origin = origin;
  this->isFired = false;
  this->startFrame = false;
  this->currFrame = 0;
  for (irr::s32 g = 1; g <= 19; ++g)
    {
      core::stringc tmp;
      tmp = "./misc/explosion/explosion";
      tmp += g;
      tmp += ".png";
      irr::scene::IBillboardSceneNode* t = manager->addBillboardSceneNode(0, irr::core::dimension2d<f32>(5000, 5000));
      t->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      t->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
      t->setMaterialTexture(0, Device->getVideoDriver()->getTexture(tmp));
      t->setVisible(false);
      this->bsn.push_back(t);
    }
  this->frameDeltaTime = 0;
  this->hasEnded = false;
}

Kamikaze::~Kamikaze()
{}

void      Kamikaze::erase()
{
  this->bsn[this->currFrame]->setVisible(false);
  this->isFired = false;
  this->startFrame = false;
  this->frameDeltaTime = 0;
  this->currFrame = 0;
  this->hasEnded = false;
}

void      Kamikaze::createNewBullet(irr::core::vector3df &dir, irr::core::vector3df &pos)
{
  if (!(this->isFired))
    {
      this->hasEnded = false;
      this->radius = irr::core::aabbox3d<irr::f32>(this->origin->_meshNode->getTransformedBoundingBox().MinEdge - 1500, this->origin->_meshNode->getTransformedBoundingBox().MaxEdge + 1500);
      this->isFired = true;
      if (!SEngine.getMute())
	{
	  SEngine.playVoice();
	  SEngine.playExplosion();
	}
    }
}

void      Kamikaze::checkCollisionWithHuman()
{
  for (auto it: GInfo._players)
    {
      if (it->getMesh()->getTransformedBoundingBox().intersectsWithBox(this->radius) && origin->getPosition() != it->getPosition())
        {
          std::cout << "touché" << std::endl;
	  it->takeDamage(this->getDamage());
	  if (it->getHp() < 0)
	    it->die();
        }
    }

  for (auto it: GInfo._objects)
    {
      if (it->type == Constants::BARREL && it->getMesh()->getTransformedBoundingBox().intersectsWithBox(this->radius) && origin->getPosition() != it->getPosition())
  	{
	  //it->takeDamage(this->getDamage());
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
  
  this->startFrame = true;
  this->then = Device->getTimer()->getTime();
  this->bsn[this->currFrame]->setVisible(true);
  this->bsn[this->currFrame]->setPosition(origin->getPosition());
}

void      Kamikaze::update()
{
  if (this->isFired)
    {
      if (!this->startFrame)
        this->checkCollisionWithHuman();
      if (this->startFrame)
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
      if (this->currFrame >= 18)
        {
          this->bsn[this->currFrame]->setVisible(false);
          this->isFired = false;
          this->startFrame = false;
          this->frameDeltaTime = 0;
          this->currFrame = 0;
	        this->hasEnded = true;
        } 
    }
}

bool                  Kamikaze::do_end()
{
  return (this->hasEnded);
}
