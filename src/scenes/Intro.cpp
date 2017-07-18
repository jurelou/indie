//
// Intro.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Wed May 24 20:25:22 2017 jurczy_l
// Last update Sun Jun 18 13:47:23 2017 louis
//

#include	"Intro.hpp"
#include	"Event.hpp"

Intro::Intro(irr::scene::ISceneManager *parent)
{
  _driver = Device->getVideoDriver();
  _manager = parent->createNewSceneManager();
  _event = static_cast<Event *>(Device->getEventReceiver());
  x1 = 0;
  y1 = 0;
  z1 = -10;
  x2 = 0;
  y2 = 5;
  z2 = 0;
  mesh = _manager->getMesh("./misc/Worm.b3d");
  if (!mesh)
    {
      Device->drop();
      exit(0);
    }
  node = _manager->addAnimatedMeshSceneNode(mesh);
  if (node)
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      node->setMD2Animation(0);
      node->setScale(irr::core::vector3df(2,2,2));
    }

  _manager->addCameraSceneNode(0, irr::core::vector3df(x1, y1, z1), irr::core::vector3df(x2, y2, z2));
  _images = _driver->getTexture("./misc/logo.png");


  cam = _manager->getActiveCamera();
  ps = _manager->addParticleSystemSceneNode(false);
  em = ps->createBoxEmitter(irr::core::aabbox3d<irr::f32>(-40,40,-40,40,-40,40),
			    irr::core::vector3df(0.0f,0.08f,0.0f),
			    0,0,
			    irr::video::SColor(0,255,255,255),
			    irr::video::SColor(0,255,255,255),
			    2000, 8000,0,
			    irr::core::dimension2df(100.f, 100.f),
			    irr::core::dimension2df(50.f, 50.f));
  ps->setEmitter(em);
  em->drop();
  paf = ps->createFadeOutParticleAffector();
  ps->addAffector(paf);
  paf->drop();
  ps->setPosition(irr::core::vector3df(0, 0, 0));
  ps->setScale(irr::core::vector3df(2, 2, 2));
  ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
  ps->setMaterialTexture(0, _driver->getTexture("./misc/fire.bmp"));
  ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
  then = Device->getTimer()->getTime();
  frameDeltaTime = 0;
  isTraveled = false;
}

Intro::~Intro()
{}

void		Intro::update()
{
  irr::core::vector3df camPosition = cam->getPosition();
  if (camPosition.Y < 50 && isTraveled == false)
    camPosition.Y += 0.5;
  if (camPosition.Z > -50 && isTraveled == false)
      camPosition.Z -= 0.5;

  if (camPosition.Y >= 50 && camPosition.Z <= -50 && isTraveled == false)
    {
      irr::scene::IParticleEmitter* em1 = ps->getEmitter();
      em1->setMaxParticlesPerSecond(50);
      em1->setMinParticlesPerSecond(25);
      ps->setEmitter(em1);
      isTraveled = true;
    }
  if (isTraveled == true)
    {
      const irr::u32 now = Device->getTimer()->getTime();
      frameDeltaTime += (irr::f32)(now - then) / 1000.f;
      then = now;
    }
  cam->setPosition(camPosition);
  if (frameDeltaTime > 3 && _event->isSomethingPressed() == true)
    WINDOW_STATE= Constants::WindowState::MAIN_MENU;
}

irr::scene::ISceneManager		*Intro::getSceneManager() const
{ return (_manager); }

void					Intro::drawAll()
{
  _manager->drawAll();
  if (frameDeltaTime > 3)
    _driver->draw2DImage(_images,
			 irr::core::position2d<irr::s32>(640 - 256, 360 - 128),
			 irr::core::rect<irr::s32>(0, 0, 512, 256),
			 NULL,
			 irr::video::SColor(255, 255, 255, 255),
			 true);
}

void					Intro::setVisible(bool i)
{}
