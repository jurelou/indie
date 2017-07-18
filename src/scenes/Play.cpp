//
// Play.cpp for indie in /home/marmus_a/Documents/rendu/cpp_indie_studio
//
// Made by augustin marmus
// Login   <marmus_a@epitech.eu>
//
// Started on  Fri May 26 11:23:18 2017 augustin marmus
// Last update Sun Jun 18 21:47:15 2017 
//

#include	"Play.hpp"
#include	"IAPlayer.hpp"
#include	"Event.hpp"

Play::Play(irr::scene::ISceneManager *parent)
{
  SEngine.stopMenuMusic();
  _manager = parent->createNewSceneManager();
  _driver = Device->getVideoDriver();
  GInfo._map = new Map(_manager);
  if (GInfo._isRandomMap == true)
    {
      GInfo._map->generateMap();
      _rootNode = GInfo._map->getMap();
    }
  else
      GInfo._map->loadTerrain(GInfo._pathMap.c_str());

  _event = static_cast<Event *>(Device->getEventReceiver());
  _mov = 1000.f;
  _a = 0.;
  for (int i = 0; i < GInfo._nbPlayers; i++)
    GInfo._players.push_back(new Human(_manager));
  std::cout << GInfo._nbIA << " _nbIA" << std::endl;
  for (int i = 0; i < GInfo._nbIA; i++)
    GInfo._players.push_back(new IAPlayer(_manager));

  for (int i = 0; i < 20; i++)
      GInfo._objects.push_back(new Barrel(_manager));

  GInfo._objects.push_back(new Tree(_manager));
  GInfo._objects.push_back(new Tree(_manager));
  GInfo._objects.push_back(new Water(_manager));
  _cam = _manager->addCameraSceneNode();

  _cam->setFarValue(50000.);

  _font = Device->getGUIEnvironment()->getFont("./misc/GUI/font_w.png");
  GInfo.currentPlayer = -1;
  _shift = 0.;
  _start = Device->getTimer()->getTime();
  _cam->setPosition(irr::core::vector3df(8400 * cos(_shift) + 8400, 4000, 8400 * sin(_shift) + 8400));
  _cam->setTarget(irr::core::vector3df(8400, 2000, 8400));


  _manager->addSkyBoxSceneNode(_driver->getTexture("./misc/irrlicht2_up.jpg"),
                               _driver->getTexture("./misc/irrlicht2_dn.jpg"),
                               _driver->getTexture("./misc/irrlicht2_lf.jpg"),
                               _driver->getTexture("./misc/irrlicht2_rt.jpg"),
                               _driver->getTexture("./misc/irrlicht2_ft.jpg"),
                               _driver->getTexture("./misc/irrlicht2_bk.jpg"));
  _crosshair = _driver->getTexture("./misc/imgg.png");
  _crosshair_b = _driver->getTexture("./misc/vis.png");
  _driver->makeColorKeyTexture(_crosshair, irr::core::position2d<irr::s32>(0,0));
  _clock.start();
  if (!SEngine.getMute())
    GInfo.newTurn = true;
  if (!SEngine.getMute())
    SEngine.playGameMusic();
}

Play::~Play()
{}

void		Play::update_players()
{
  GInfo._players.at(GInfo.currentPlayer)->update();
}

void		Play::update_overlay()
{
  _weapon = GInfo._players.at(GInfo.currentPlayer)->getWeapon()->getImage();
  _driver->makeColorKeyTexture(_weapon, irr::core::position2d<irr::s32>(0,0));
  const irr::core::dimension2du &size = _driver->getScreenSize();
  std::stringstream ss;
  irr::u32 diff = 30000 - _clock.getTime();
  if (diff >= 5000 && diff <= 30000)
    {
      _font->draw(std::to_string(diff / 1000).c_str(),
  		  irr::core::rect<irr::s32>((size.Width * 0.8),
  					    (size.Height* 0.1),
  					    (size.Width * 0.8) + 400,
  					    (size.Height* 0.1) + 400
  					    ),
  		  irr::video::SColor(255,0,255,0));

    }
  else
    {
      _font->draw(std::to_string(diff / 1000).c_str(),
  		  irr::core::rect<irr::s32>((size.Width * 0.8),
  					    (size.Height* 0.1),
  					    (size.Width * 0.8) + 60,
  					    (size.Height* 0.1) + 60
  					    ),
  		  irr::video::SColor(255,255,0,0));
    }

  for (int i = 0; i < (GInfo._nbPlayers + GInfo._nbIA); i++)
     {
       std::string my_life(std::to_string(GInfo._players[i]->getHp()));
       if (GInfo._players[i]->getHp() > 0)
	 {
	   if (GInfo._players[i]->textMesh == NULL && i != GInfo.currentPlayer && GInfo._players[i]->alive)
	     {
	       GInfo._players[i]->textMesh = _manager->addTextSceneNode(_font, (std::wstring(my_life.begin(), my_life.end())).c_str()
									, video::SColor(255,255,255,255), GInfo._players[i]->_meshNode);
	     }
	   else if (i != GInfo.currentPlayer && GInfo._players[i]->alive && GInfo._players[i]->textMesh)
	     {
	       GInfo._players[i]->textMesh->setVisible(true);
	       GInfo._players[i]->textMesh->setText(std::wstring(my_life.begin(), my_life.end()).c_str());
	       GInfo._players[i]->textMesh->setTextColor(video::SColor(255,255,0,0));
	     }
	   else
	     {
	       if (GInfo._players[i]->textMesh != NULL && GInfo._players[i]->alive)
		 GInfo._players[i]->textMesh->setVisible(false);
	       _font->draw(std::wstring(my_life.begin(), my_life.end()).c_str(),
			   irr::core::rect<irr::s32>((size.Width * 0.1),
						     (size.Height * 0.1),
						     ((size.Width * 0.1) + 20),
						     ((size.Height * 0.1) + 20)),
			   irr::video::SColor(255,0,255,0));
	     }
	 }
     }
  _font->draw(L"Press 'C' to change weapon",
	      irr::core::rect<irr::s32>((size.Width * 0.8),
					(size.Height * 0.7),
					((size.Width * 0.75) + 20),
					((size.Height * 0.7) + 20)),
	      irr::video::SColor(255,0,255,0));
  _driver->draw2DImage(_weapon,
  		       irr::core::position2d<irr::s32>(
  						       size.Width * 0.8,
  						       size.Height * 0.725),
  		       irr::core::rect<irr::s32>(0,
  						 0,
  						 200,
  						 200),
		       0,
  		       irr::video::SColor(255,255,255,255),
  		       true);
  if (GInfo._players.at(GInfo.currentPlayer)->getWeapon()->target == Constants::GUN)
    {
      _driver->draw2DImage(_crosshair, irr::core::position2d<irr::s32>((size.Width / 2) - 50,
								       (size.Height / 2 - 50)
								       ),
			   irr::core::rect<irr::s32>(0,
						     0,
						     _crosshair->getOriginalSize().Width,
						     _crosshair->getOriginalSize().Height),
			   0,
			   irr::video::SColor(255,255,255,255), true);
    }
  else if (GInfo._players.at(GInfo.currentPlayer)->getWeapon()->target == Constants::ROCKET)
    {
      _driver->draw2DImage(_crosshair_b, irr::core::position2d<irr::s32>((size.Width / 2) - 50,
								       (size.Height / 2 - 50)
								       ),
			   irr::core::rect<irr::s32>(0,
						     0,
						     _crosshair_b->getOriginalSize().Width,
						     _crosshair_b->getOriginalSize().Height),
			   0,
			   irr::video::SColor(255,255,255,255), true);
    }
}

void		Play::update()
{
  for (auto it: GInfo._objects)
    it->update();
  irr::u32 i = 0;
  for (auto it: GInfo._players)
    if (it->alive == true)
      i++;
  if (i <= 1)
    {
      WINDOW_STATE = Constants::PLAYER_WIN;
      if (!SEngine.getMute())
	{
	  SEngine.stopGameMusic();
	  SEngine.playGameEnd();
	}
      return;
    }

  if (_event->isKeyPressed(irr::KEY_ESCAPE))
    WINDOW_STATE = Constants::PAUSE;
  if (GInfo.currentPlayer == -1)
    {
      _cam->setPosition(irr::core::vector3df(8400 * cos(_shift) + 8400, 4000, 8400 * sin(_shift) + 8400));
      _cam->setTarget(irr::core::vector3df(8400, 2000, 8400));
      _shift += 0.01;
      if (_shift > 2 * M_PI)
	_shift -= 2 * M_PI;
      if (_clock.getTime() >= 10000)
	{
	  _clock.reset();
	  _clock.start();
	  GInfo.currentPlayer = 0;
	  GInfo.newTurn = true;
	  ((Human *)(GInfo._players[GInfo.currentPlayer]))->controller->setCamera(_cam);
	}
    }
  else
    {
      /////
      if (GInfo._players.at(GInfo.currentPlayer)->alive == false)
	{
	  _clock.reset();
	  _clock.start();
	  GInfo.currentPlayer++;
      	  GInfo.currentPlayer %= GInfo._nbPlayers + GInfo._nbIA;
	  GInfo.newTurn = true;
	  ((Human *)(GInfo._players[GInfo.currentPlayer]))->controller->setCamera(_cam);
	}
      ////
      this->update_players();
      if (GInfo._players.at(GInfo.currentPlayer)->getWeapon()->do_end() == true)
	{
	  _clock.reset();
	  _clock.start();
	  GInfo._players.at(GInfo.currentPlayer)->end_turn();
	  GInfo.currentPlayer++;
      	  GInfo.currentPlayer %= GInfo._nbPlayers + GInfo._nbIA;
	  GInfo.newTurn = true;
      	  ((Human *)(GInfo._players[GInfo.currentPlayer]))->controller->setCamera(_cam);

	}
      if (_clock.getTime() >= 30000)
      	{
	  _clock.reset();
	  _clock.start();
      	  GInfo.currentPlayer++;
      	  GInfo.currentPlayer %= GInfo._nbPlayers + GInfo._nbIA;
	  GInfo.newTurn = true;
      	  ((Human *)(GInfo._players[GInfo.currentPlayer]))->controller->setCamera(_cam);
      	}
    }
}

irr::scene::ISceneManager	*Play::getSceneManager() const
{   return (_manager); }

void				Play::drawAll()
{  _manager->drawAll(); }

void				Play::setVisible(bool state)
{
  return ;
}
