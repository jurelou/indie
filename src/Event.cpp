//
// CGUIEventDispatcher.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 23:24:42 2017 jurczy_l
// Last update Tue Jun 13 14:47:30 2017 
//

#include		"Event.hpp"

Event::Event()
{
   for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
     Keys[i] = BS_UP;
   for(irr::u32 i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
     Mouse[i] = MBS_UP;
   MouseData.x = MouseData.y = MouseData.lx = MouseData.ly = MouseData.cx = MouseData.cy = 0;
   MouseData.wheelPos = MouseData.lwheelPos = 0;
   deltaMouseX = deltaMouseY = 0;
   mouseHasMoved = false;
   generalCallerID = menuItemSelectedID = 0;
   menu = NULL;
   elementStatus[irr::gui::EGET_ELEMENT_FOCUS_LOST] = elementStatus[irr::gui::EGET_ELEMENT_FOCUSED] =
   elementStatus[irr::gui::EGET_ELEMENT_HOVERED] = elementStatus[irr::gui::EGET_ELEMENT_LEFT] =
   elementStatus[irr::gui::EGET_ELEMENT_CLOSED] = elementStatus[irr::gui::EGET_BUTTON_CLICKED] =
   elementStatus[irr::gui::EGET_SCROLL_BAR_CHANGED] = elementStatus[irr::gui::EGET_CHECKBOX_CHANGED] =
   elementStatus[irr::gui::EGET_LISTBOX_CHANGED] = elementStatus[irr::gui::EGET_LISTBOX_SELECTED_AGAIN] =
   elementStatus[irr::gui::EGET_FILE_SELECTED] = elementStatus[irr::gui::EGET_FILE_CHOOSE_DIALOG_CANCELLED] =
   elementStatus[irr::gui::EGET_MESSAGEBOX_YES] = elementStatus[irr::gui::EGET_MESSAGEBOX_NO] =
   elementStatus[irr::gui::EGET_MESSAGEBOX_OK] = elementStatus[irr::gui::EGET_MESSAGEBOX_CANCEL] =
   elementStatus[irr::gui::EGET_EDITBOX_ENTER] = elementStatus[irr::gui::EGET_TAB_CHANGED] =
   elementStatus[irr::gui::EGET_MENU_ITEM_SELECTED] = elementStatus[irr::gui::EGET_COMBO_BOX_CHANGED] =
   elementStatus[irr::gui::EGET_SPINBOX_CHANGED] = FALSE;
}

Event::~Event()
{
}

bool Event::isKeyUp(irr::EKEY_CODE key)
{
  if (Keys[key] == BS_UP)
    return true;
  return false;
}

bool Event::isKeyDown(irr::EKEY_CODE key)
{
  if (Keys[key] == BS_DOWN)
    return true;
  return false;
}

bool Event::isKeyPressed(irr::EKEY_CODE key)
{
  if(Keys[key] == BS_PRESSED)
    return true;
  return false;
}

bool Event::isKeyReleased(irr::EKEY_CODE key)
{
  if(Keys[key] == BS_RELEASED)
    return true;
  return false;
}

bool Event::isMouseButtonUp(mouseButton mb)
{
  if (Mouse[mb] == MBS_UP)
    return true;
  return false;
}

bool Event::isMouseButtonDown(mouseButton mb)
{
  if (Mouse[mb] == MBS_DOWN)
    return true;
  return false;
}

bool Event::isMouseButtonPressed(mouseButton mb)
{
  if (Mouse[mb] == MBS_PRESSED)
    {
      std::cout << "fuck " << std::endl;
      return true;
    }
  return false;
}

bool Event::isMouseButtonReleased(mouseButton mb)
{
  if (Mouse[mb] == MBS_RELEASED)
    return true;
  return false;
}

int Event::getDeltaMousePosX()
{
  return deltaMouseX;
}

int Event::getDeltaMousePosY()
{
  return deltaMouseY;
}

bool Event::mouseMoved()
{
  if(mouseHasMoved)
    {
      mouseHasMoved = false;
      return true;
    }
  return false;
}

bool Event::getEventCallerByElement(irr::gui::EGUI_EVENT_TYPE guiEventType)
{
  if (elementStatus[guiEventType] == TRUE)
    return true;
  return false;
}

int Event::getEventCallerByID()
{
  return generalCallerID;
}


int Event::getEventCallerOfMenuByID()
{
  return menuItemSelectedID;
}

void Event::startEventProcess()
{
  procesState = STARTED;
  for(int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    {
      if(Keys[i] == BS_RELEASED)
	Keys[i] = BS_UP;
      if(Keys[i] == BS_PRESSED)
	Keys[i] = BS_DOWN;
    }
  for(int i = 0; i < NUMBER_OF_MOUSE_BUTTONS; i++)
    {
      if(Mouse[i] == MBS_RELEASED)
	Mouse[i] = MBS_UP;
      if(Mouse[i] == MBS_PRESSED)
	Mouse[i] = MBS_DOWN;
    }
  elementStatus[irr::gui::EGET_ELEMENT_FOCUS_LOST] = elementStatus[irr::gui::EGET_ELEMENT_FOCUSED] =
    elementStatus[irr::gui::EGET_ELEMENT_HOVERED] = elementStatus[irr::gui::EGET_ELEMENT_LEFT] =
    elementStatus[irr::gui::EGET_ELEMENT_CLOSED] = elementStatus[irr::gui::EGET_BUTTON_CLICKED] =
    elementStatus[irr::gui::EGET_SCROLL_BAR_CHANGED] = elementStatus[irr::gui::EGET_CHECKBOX_CHANGED] =
    elementStatus[irr::gui::EGET_LISTBOX_CHANGED] = elementStatus[irr::gui::EGET_LISTBOX_SELECTED_AGAIN] =
    elementStatus[irr::gui::EGET_FILE_SELECTED] = elementStatus[irr::gui::EGET_FILE_CHOOSE_DIALOG_CANCELLED] =
    elementStatus[irr::gui::EGET_MESSAGEBOX_YES] = elementStatus[irr::gui::EGET_MESSAGEBOX_NO] =
    elementStatus[irr::gui::EGET_MESSAGEBOX_OK] = elementStatus[irr::gui::EGET_MESSAGEBOX_CANCEL] =
    elementStatus[irr::gui::EGET_EDITBOX_ENTER] = elementStatus[irr::gui::EGET_TAB_CHANGED] =
    elementStatus[irr::gui::EGET_MENU_ITEM_SELECTED] = elementStatus[irr::gui::EGET_COMBO_BOX_CHANGED] =
    elementStatus[irr::gui::EGET_SPINBOX_CHANGED] = FALSE;
}

void Event::endEventProcess()
{   procesState = ENDED;  }

bool Event::OnEvent(const irr::SEvent& event)
{
  switch (event.EventType)
    {
    case irr::EET_KEY_INPUT_EVENT:
      {
	if(procesState == STARTED)
          {
	    if(event.KeyInput.PressedDown)
	      {
		if(Keys[event.KeyInput.Key] != BS_DOWN)
		  Keys[event.KeyInput.Key] = BS_PRESSED;
		else
		  Keys[event.KeyInput.Key] = BS_DOWN;
		break;
	      }
	    else
	      {
		if(Keys[event.KeyInput.Key] != BS_UP)
                        Keys[event.KeyInput.Key] = BS_RELEASED;
		else
		  Keys[event.KeyInput.Key] = BS_UP;
		break;
	      }
          }
      }
      break;
    case irr::EET_MOUSE_INPUT_EVENT:
      {
	switch(event.MouseInput.Event)
	  {
	  case irr::EMIE_MOUSE_MOVED:
	    {
	      deltaMouseX = event.MouseInput.X - MouseData.lx;
	      deltaMouseY = event.MouseInput.Y - MouseData.ly;
	      MouseData.x = event.MouseInput.X;
	      MouseData.y = event.MouseInput.Y;
	      MouseData.lx = MouseData.x;
	      MouseData.ly = MouseData.y;
	      mouseHasMoved = true;
	      break;
	    }
	  case irr::EMIE_MOUSE_WHEEL:
	    {
	      MouseData.lwheelPos = MouseData.wheelPos;
	      MouseData.wheelPos += event.MouseInput.Wheel;
	      break;
	    }
	  case irr::EMIE_LMOUSE_PRESSED_DOWN:
	    {
	      if(Mouse[MBLEFT] == MBS_UP || Mouse[MBLEFT] == MBS_RELEASED)
                Mouse[MBLEFT] = MBS_PRESSED;
	      else
                Mouse[MBLEFT] = MBS_DOWN;
	      break;
	    }
	  case irr::EMIE_LMOUSE_LEFT_UP:
	    {
	      if(Mouse[MBLEFT] != MBS_UP)
                Mouse[MBLEFT] = MBS_RELEASED;
	      break;
	    }
	  case irr::EMIE_MMOUSE_PRESSED_DOWN:
	    {
	      if(Mouse[MBMIDDLE] == MBS_UP || Mouse[MBMIDDLE] == MBS_RELEASED)
                Mouse[MBMIDDLE] = MBS_PRESSED;
	      else
                Mouse[MBMIDDLE] = MBS_DOWN;
	      break;
	    }
	  case irr::EMIE_MMOUSE_LEFT_UP:
	    {
	      if (Mouse[MBMIDDLE] != MBS_UP)
                Mouse[MBMIDDLE] = MBS_RELEASED;
	      break;
	    }
	  case irr::EMIE_RMOUSE_PRESSED_DOWN:
	    {
	      if (Mouse[MBRIGHT] == MBS_UP || Mouse[MBRIGHT] == MBS_RELEASED)
                Mouse[MBRIGHT] = MBS_PRESSED;
	      else
                Mouse[MBRIGHT] = MBS_DOWN;
	      break;
	    }
	  case irr::EMIE_RMOUSE_LEFT_UP:
	    {
	      if(Mouse[MBRIGHT] != MBS_UP)
                Mouse[MBRIGHT] = MBS_RELEASED;
	      break;
	    }
          default:
	    break;
	  }
      }
      break;
    case irr::EET_GUI_EVENT:
      {
	generalCallerID = event.GUIEvent.Caller->getID();
	switch(event.GUIEvent.EventType)
	  {
	  case irr::gui::EGET_ELEMENT_FOCUS_LOST:
	  case irr::gui::EGET_ELEMENT_FOCUSED:
	  case irr::gui::EGET_ELEMENT_HOVERED:
	  case irr::gui::EGET_ELEMENT_LEFT:
	  case irr::gui::EGET_ELEMENT_CLOSED:
	  case irr::gui::EGET_BUTTON_CLICKED:
	  case irr::gui::EGET_SCROLL_BAR_CHANGED:
	  case irr::gui::EGET_CHECKBOX_CHANGED:
	  case irr::gui::EGET_LISTBOX_CHANGED:
	  case irr::gui::EGET_LISTBOX_SELECTED_AGAIN:
	  case irr::gui::EGET_FILE_SELECTED:
	  case irr::gui::EGET_FILE_CHOOSE_DIALOG_CANCELLED:
	  case irr::gui::EGET_MESSAGEBOX_YES:
	  case irr::gui::EGET_MESSAGEBOX_NO:
	  case irr::gui::EGET_MESSAGEBOX_OK:
	  case irr::gui::EGET_MESSAGEBOX_CANCEL:
	  case irr::gui::EGET_EDITBOX_ENTER:
	  case irr::gui::EGET_TAB_CHANGED:
	  case irr::gui::EGET_COMBO_BOX_CHANGED:
	  case irr::gui::EGET_SPINBOX_CHANGED:
	    elementStatus[event.GUIEvent.EventType] = TRUE;
	    break;
	  case irr::gui::EGET_MENU_ITEM_SELECTED:
	    elementStatus[irr::gui::EGET_MENU_ITEM_SELECTED] = TRUE;
	    menu = (irr::gui::IGUIContextMenu*)event.GUIEvent.Caller;
	    menuItemSelectedID = menu->getItemCommandId(menu->getSelectedItem());
            break;
	  default:
	    break;
	  }
      }
    default:
      break;
    }
  return false;
}

int		Event::getMouseX()
{ return MouseData.x; }

int Event::getMouseY()
{ return MouseData.y; }

int Event::getLastMouseX()
{ return MouseData.lx; }

int Event::getLastMouseY()
{ return MouseData.ly; }

irr::s32		Event::getDeltaMouseX()
{
  irr::s32	 a = MouseData.x - MouseData.lx;
  return (irr::s32)(a < 0 ? -a : a);
}

irr::s32		Event::getDeltaMouseY()
{
  irr::s32	 a = MouseData.y - MouseData.ly;
  return (irr::s32	 )(a < 0 ? -a : a);
}

irr::u32 Event::getClickedMouseX()
{ return MouseData.cx; }

irr::u32 Event::getClickedMouseY()
{ return MouseData.cy; }

irr::f32 Event::getMouseWheelPosition()
{ return MouseData.wheelPos; }

irr::f32 Event::getLastMouseWheelPosition()
{ return MouseData.lwheelPos; }

irr::f32 Event::getDeltaMouseWheelPosition()
{
  irr::f32 a = MouseData.wheelPos - MouseData.lwheelPos;
  return (irr::f32)(a < 0 ? -a : a);
}

bool		Event::isSomethingPressed()
{
  for(int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    {
      if(Keys[i] == BS_DOWN)
	return (true);
    }
  return (false);
}
