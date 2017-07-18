//
// CGUIEventDispatcher.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:25:07 2017 jurczy_l
// Last update Mon Jun 12 10:48:12 2017 
//

#ifndef		EVENT_HPP__
#define		EVENT_HPP__

#include	"irrlicht.h"
#include	<stdio.h>
#include	<iostream>
#include	<sstream>

#define		NUMBER_OF_MOUSE_BUTTONS	3
#define		NUMBER_OF_GUI_ELEMENTS	21

enum		buttonState
  {
    BS_UP,
    BS_DOWN,
    BS_PRESSED,
    BS_RELEASED
  };

enum		mouseButton
  {
    MBLEFT,
    MBMIDDLE,
    MBRIGHT
  };

enum		mouseButtonState
  {
    MBS_UP,
    MBS_DOWN,
    MBS_PRESSED,
    MBS_RELEASED
  };

struct		mouseInformation
{
  irr::s32	x, y, lx, ly, cx, cy;
  irr::f32	wheelPos, lwheelPos;
};

enum		ProcessEventState
  {
    STARTED,
    ENDED
  };

enum		ElementStatus
  {
    TRUE,
    FALSE
  };

class		Event : public irr::IEventReceiver
{
public:
  Event();
  ~Event();

  bool		getEventCallerByElement(irr::gui::EGUI_EVENT_TYPE);
  int		getEventCallerOfMenuByID();
  int		getEventCallerByID();

  bool		isKeyUp(irr::EKEY_CODE key);
  bool		isKeyDown(irr::EKEY_CODE key);
  bool		isKeyPressed(irr::EKEY_CODE key);
  bool		isKeyReleased(irr::EKEY_CODE key);

  bool		isSomethingPressed();

  bool		isMouseButtonUp(mouseButton mb);
  bool		isMouseButtonDown(mouseButton mb);
  bool		isMouseButtonPressed(mouseButton mb);
  bool		isMouseButtonReleased(mouseButton mb);

  bool		mouseMoved();
  void		startEventProcess();
  void		endEventProcess();

  int		getDeltaMousePosX();
  int		getDeltaMousePosY();

  int getMouseX();
  int getMouseY();
  int getLastMouseX();
  int getLastMouseY();

  irr::s32 getDeltaMouseX();
  irr::s32 getDeltaMouseY();
  irr::u32 getClickedMouseX();
  irr::u32 getClickedMouseY();
  irr::f32 getMouseWheelPosition();
  irr::f32 getLastMouseWheelPosition();
  irr::f32 getDeltaMouseWheelPosition();
  bool OnEvent(const irr::SEvent& event);

protected:
  buttonState		Keys[irr::KEY_KEY_CODES_COUNT];
  mouseButtonState	Mouse[NUMBER_OF_MOUSE_BUTTONS];
  ElementStatus		elementStatus[NUMBER_OF_GUI_ELEMENTS];
  mouseInformation	MouseData;
  ProcessEventState	procesState;
  irr::gui::IGUIContextMenu	*menu;
  irr::s32			menuItemSelectedID;
  irr::s32			generalCallerID;
  int			deltaMouseX;
  int			deltaMouseY;
  bool			mouseHasMoved;
};

#endif
