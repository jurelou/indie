//
// GraphicalEngine.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Wed May 17 11:57:00 2017 jurczy_l
// Last update Sun Jun 18 13:50:11 2017 louis
//

#include	"GraphicalEngine.hpp"

GraphicalEngine::GraphicalEngine(bool fullsreen)
{

  IrrlichtDevice *nulldevice = createDevice(video::EDT_NULL);
  irr::core::dimension2d<u32> screensize = nulldevice->getVideoModeList()->getDesktopResolution();
  nulldevice->drop();

  if (fullsreen)
    Device = irr::createDevice(irr::video::EDT_OPENGL, screensize, 32, true, true);
  else
    Device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280,720));

  Device->setWindowCaption(L"Worms !!!");
  _driver = Device->getVideoDriver ();
  _sceneManager = Device->getSceneManager();
  GInfo._nbPlayers = 0;
  GInfo._nbIA = 0;
  GInfo._reset = false;
  GInfo._isRandomMap = true;
  recv = new Event();
  Device->setEventReceiver(recv);
  _scenes.resize(NbScenes, NULL);
  _scenes.at(Constants::WindowState::MAIN_MENU) = new Menu();
  _scenes.at(Constants::WindowState::INTRO) = new Intro(_sceneManager);
  _scenes.at(Constants::WindowState::SETTINGS) = new Settings();
  _scenes.at(Constants::WindowState::LAUNCHER) = new Launcher();
  _scenes.at(Constants::WindowState::PAUSE) = new Pause();
  _scenes.at(Constants::WindowState::PLAYER_WIN) = new Win();
  _scenes.at(Constants::WindowState::PLAYER_LOOSE) = new Loose();
  _scenes.at(Constants::WindowState::SAVE) = new Save(_scenes);
}

GraphicalEngine::~GraphicalEngine()
{
  Device->drop();
}

void		GraphicalEngine::draw()
{
  recv->endEventProcess();
  _driver->beginScene(true, true, irr::video::SColor(150,0,0,0));
  _scenes.at(WINDOW_STATE)->update();
  this->update();
  if (WINDOW_STATE == Constants::PAUSE)
    _scenes.at(Constants::PLAYING)->drawAll();
  _scenes.at(WINDOW_STATE)->drawAll();
  if (WINDOW_STATE == Constants::PLAYING && GInfo.currentPlayer != -1)
    ((Play *)_scenes.at(Constants::PLAYING))->update_overlay();
  _driver->endScene ();
  recv->startEventProcess();
}

void		GraphicalEngine::update()
{
  for (int i = 0; i < _scenes.size(); i++)
    if (_scenes.at(i))
      _scenes.at(i)->setVisible(false);
  if (GInfo._reset)
    {
      delete _scenes.at(Constants::WindowState::PLAYING);
      _scenes.at(Constants::PLAYING) = NULL;
      GInfo._reset = false;
      GInfo._players.clear();
      GInfo._objects.clear();
    }
  if (WINDOW_STATE == Constants::PLAYING && _scenes.at(Constants::WindowState::PLAYING) == NULL)
    _scenes.at(Constants::WindowState::PLAYING) = new Play(_sceneManager);
  _scenes.at(WINDOW_STATE)->setVisible(true);
}
