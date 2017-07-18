//
// Settings.cpp for Project-Master in /home/louis/Documents/cpp_indie_studio/src/scenes
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 15:23:23 2017 jurczy_l
// Last update Tue Jun 27 15:25:43 2017 louis
//

#include		"Event.hpp"
#include		"Settings.hpp"
#include		"SoundEngine.hpp"
#include		"key_code.hpp"
#include                "define_key.hpp"


int l = -1;

Settings::Settings()
{
  irr::video::ITexture	*_img;
  irr::gui::IGUIImage	*bg;
  _driver = Device->getVideoDriver();
  _event = static_cast<Event*>(Device->getEventReceiver());
  _gui = Device->getGUIEnvironment();
  const irr::core::dimension2du& screenSize = _driver->getScreenSize();
  _elem = new irr::gui::IGUIElement(
				    irr::gui::EGUIET_ELEMENT,
				    _gui,
				    _gui->getRootGUIElement(),
				    -1,
				    irr::core::rect<irr::s32>(0,0,screenSize.Width,screenSize.Height)
				    );

  _img = _driver->getTexture("./misc/GUI/background_menu.jpg");
  bg = _gui->addImage(irr::core::rect<irr::s32>(0,0, screenSize.Width,screenSize.Height),_elem);
  bg->setImage(_img);
  bg->setScaleImage(true);

  _elem->setVisible(false);
  sound_box = _gui->addCheckBox(sound,
				irr::core::rect<int>(
						     screenSize.Width*0.275 - 15,
						     (screenSize.Height*0.775),
						     (screenSize.Width*0.275) + 15,
						     (screenSize.Height*0.775)+50),
				_elem, 4, L"");
  sound_box->setChecked(true);
  
  text_sound = _gui->addStaticText(L"Sound", irr::core::rect<int>(
						       screenSize.Width*0.31 - 35,
						       (screenSize.Height*0.775),
						       (screenSize.Width*0.31) + 35,
						       (screenSize.Height*0.775)+50),
		      false, false, _elem, -1);
  text_sound->setTextAlignment(irr::gui::EGUIA_UPPERLEFT, irr::gui::EGUIA_CENTER);
  text_sound->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

  quit = _gui->addButton(irr::core::rect<int>(
					      screenSize.Width * 0.3 - 100,
					      screenSize.Height * 0.85,
					      screenSize.Width * 0.3 + 100,
					      screenSize.Height * 0.85 + 75),
					      _elem, -1, L"", NULL);
  quit->setImage(_driver->getTexture("./misc/GUI/settings/settingsmenu.png"));
  apply = _gui->addButton(irr::core::rect<int>(
					       screenSize.Width * 0.7 - 100,
					       screenSize.Height * 0.85,
					       screenSize.Width * 0.7 + 100,
					       screenSize.Height * 0.85 + 75),
		  _elem, -2, L"", NULL);
  apply->setImage(_driver->getTexture("./misc/GUI/settings/settingsapply.png"));
  link_keys[0] = Constants::FRONT;
  link_keys[1] = Constants::BEHIND;
  link_keys[2] = Constants::GO_LEFT;
  link_keys[3] = Constants::GO_RIGHT;
  link_keys[4] = Constants::ATTACK;
  link_keys[5] = Constants::SELECT;
  link_keys[6] = Constants::JUMP;
  link_keys[7] = Constants::SUICID;
  link_keys[8] = Constants::UP;
  link_keys[9] = Constants::DOWN;
  link_keys[10] = Constants::LEFT;
  link_keys[11] = Constants::RIGHT;

  init_first_line(screenSize);
  init_second_line(screenSize);
  init_third_line(screenSize);
  reset();
}

Settings::~Settings()
{

}

bool				Settings::Checker(irr::EKEY_CODE key)
{
  int	i;

  i = 0;
  if (key == irr::KEY_ESCAPE)
    return (false);
  while (GInfo.keys[link_keys[i]])
    {
      if (GInfo.keys[link_keys[i]] == key)
	return (false);
      i++;
    }
  return (true);
}

void				Settings::key_change()
{
  int	i;
  int	j;
  int	k;

  i = 0;
  j = 0;
  k = 0;
  while (i != 144)
    {
      if (_event->isKeyPressed(all_key[i]))
	{
	  std::cout << "nique " << i << std::endl;
	  if(Checker(all_key[i]) == true)
	    {
	      while (!Press_btn[k])
		k++;
	      GInfo.keys[link_keys[k]] = all_key[i];
	      std::wstring widestr = std::wstring(name_key[i].begin(), name_key[i].end());
	      while (j != 12)
		  {
		    if (Press_btn[j])
		      text_key[j]->setText(widestr.c_str());
		    j++;
		  }
	      for (int g = 0; g != 12; g++)
		Press_btn[g] = false;
	    }
	  else if (l != -1)
	    {
	      l = 0;
	      while (l != 12)
		Press_btn[l++] = false;
	    }
	  break;
	}
      i++;
    }
}

void				Settings::update()
{
  int	i;
  int	j;
  int	k;

  i = 0;
  for (k = 0; k != 12; k++)
    {
      if (btn_key[k]->isPressed())
	{
	  l = k;
	  Press_btn[k] = true;
	  break;
	}
    }
  if (l != -1 && Press_btn[l])
    key_change();
  if (sound_box->isChecked())
    {
      if (SEngine.getMute())
	SEngine.playMenuMusic();
      SEngine.setMute(false);
    }
  else
    {
      SEngine.stopMenuMusic();
      SEngine.setMute(true);
    }
  if (quit->isPressed())
    {
      WINDOW_STATE = Constants::MAIN_MENU;
      if (!isApply)
	{
	  std::cout << "reset" << std::endl;
	  reset();
	}
      isApply = false;
    }
  else if (apply->isPressed())
    isApply = true;
}

void				Settings::reset()
{
  for (int i = 0; i != 12; i++)
    Press_btn[i] = false;

  text_key[0]->setText(L"Z");
  text_key[1]->setText(L"S");
  text_key[2]->setText(L"Q");
  text_key[3]->setText(L"D");
  text_key[4]->setText(L"T");
  text_key[5]->setText(L"C");
  text_key[6]->setText(L"SPACEBAR");
  text_key[7]->setText(L"P");
  text_key[8]->setText(L"UP ARROW KEY");
  text_key[9]->setText(L"DOWN ARROW KEY");
  text_key[10]->setText(L"LEFT ARROW KEY");
  text_key[11]->setText(L"RIGHT ARROW KEY");

  GInfo.keys[Constants::FRONT] = irr::KEY_KEY_Z;
  GInfo.keys[Constants::BEHIND] = irr::KEY_KEY_S;
  GInfo.keys[Constants::GO_LEFT] = irr::KEY_KEY_Q;
  GInfo.keys[Constants::GO_RIGHT] = irr::KEY_KEY_D;
  GInfo.keys[Constants::ATTACK] = irr::KEY_KEY_T;
  GInfo.keys[Constants::SELECT] = irr::KEY_KEY_C;
  GInfo.keys[Constants::JUMP] = irr::KEY_SPACE;
  GInfo.keys[Constants::SUICID] = irr::KEY_KEY_P;
  GInfo.keys[Constants::UP] = irr::KEY_UP;
  GInfo.keys[Constants::DOWN] = irr::KEY_DOWN;
  GInfo.keys[Constants::LEFT] = irr::KEY_LEFT;
  GInfo.keys[Constants::RIGHT] = irr::KEY_RIGHT;


  sound_box->setChecked(true);
  isApply = false;
  if (SEngine.getMute())
	SEngine.playMenuMusic();
}

void				Settings::init_first_line(const irr::core::dimension2du& screenSize)
{
   ////////////////////////////AVANCER//////////////////////


  text_to_add = _gui->addStaticText(L"Z", irr::core::rect<int>(
							       (screenSize.Width * 0.2) - 100,
						       (screenSize.Height*0.25),
						       (screenSize.Width*0.2) + 100,
						       (screenSize.Height*0.25)+30),
		      false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
					      screenSize.Width * 0.2 - 100,
					      screenSize.Height * 0.25 + 30,
					      (screenSize.Width * 0.2) + 100,
					      (screenSize.Height * 0.25 + 30) + 75),
			 _elem, 0, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingsmoveforward.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ////////////////////////////RECULER///////////////////////

  text_to_add = _gui->addStaticText(L"S", irr::core::rect<int>(
						       screenSize.Width*0.4 - 100,
						       (screenSize.Height*0.25),
						       (screenSize.Width*0.4) + 100,
						       (screenSize.Height*0.25)+30),
		      false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
					      screenSize.Width*0.4 - 100,
					      (screenSize.Height*0.25 + 30),
					      (screenSize.Width*0.4) + 100,
					      (screenSize.Height*0.25 + 30)+75),
			 _elem, 1, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingsmoveback.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ////////////////////////////Gauche///////////////////////

  text_to_add = _gui->addStaticText(L"Q", irr::core::rect<int>(
						      screenSize.Width * 0.6 - 100,
						      (screenSize.Height*0.25),
						      (screenSize.Width * 0.6) + 100,
						      (screenSize.Height*0.25)+30),
		      false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));

  btn_to_add = _gui->addButton(irr::core::rect<int>(
					       screenSize.Width * 0.6 - 100,
					       (screenSize.Height*0.25)+30,
					       (screenSize.Width* 0.6 )+ 100,
					       (screenSize.Height*0.25+30)+75),
			  _elem, 2, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingsmoveleft.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ///////////////////////////Droite///////////////////////

  text_to_add = _gui->addStaticText(L"D", irr::core::rect<int>(
							       screenSize.Width * 0.8 - 100,
							       (screenSize.Height*0.25),
							       (screenSize.Width*0.8) + 100,
							       (screenSize.Height*0.25)+30),
				    false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
				       screenSize.Width*0.8 - 100,
				       (screenSize.Height*0.25)+30,
				       (screenSize.Width*0.8) + 100,
				       (screenSize.Height*0.25+30)+75),
		  _elem, 3, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingsmoveright.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
}

void				Settings::init_second_line(const irr::core::dimension2du& screenSize)
{
  ////////////////////////////ATTAQUE//////////////////////

  text_to_add = _gui->addStaticText(L"T", irr::core::rect<int>(
						       screenSize.Width * 0.2 - 100,
						       (screenSize.Height*0.425),
						       (screenSize.Width*0.2)+100,
						       (screenSize.Height*0.425)+30),
		      false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
					      screenSize.Width*0.2 - 100,
					      ((screenSize.Height*0.425) + 30),
					      (screenSize.Width*0.2)+100,
					      (screenSize.Height*0.425 + 30)+75),
			 _elem, 0, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingsattack.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ////////////////////////////CHANGER ARME///////////////////////

  text_to_add = _gui->addStaticText(L"C", irr::core::rect<int>(
						       screenSize.Width*0.4 - 100,
						       (screenSize.Height*0.425),
						       (screenSize.Width*0.4)+100,
						       (screenSize.Height*0.425)+30),
		      false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
					      screenSize.Width*0.4 - 100,
					      (screenSize.Height*0.425)+30,
					      (screenSize.Width*0.4) + 100,
					      (screenSize.Height*0.425+30)+75),
			 _elem, 1, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingsweapon.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ////////////////////////////Sauter///////////////////////

  text_to_add = _gui->addStaticText(L"SPACE", irr::core::rect<int>(
								   screenSize.Width*0.6 - 100,
						      (screenSize.Height*0.425),
						      (screenSize.Width*0.6)+100,
						      (screenSize.Height*0.425)+30),
				    false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
					       screenSize.Width*0.6 - 100,
					       (screenSize.Height*0.425)+30,
					       (screenSize.Width*0.6)+100,
					       (screenSize.Height*0.425+30)+75),
			  _elem, 2, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingsjump.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ///////////////////////////Suicide///////////////////////

  text_to_add = _gui->addStaticText(L"P", irr::core::rect<int>(
						   screenSize.Width*0.8 - 100,
						   (screenSize.Height*0.425),
						   (screenSize.Width*0.8)+100,
						   (screenSize.Height*0.425)+30),
				    false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
				       screenSize.Width*0.8 - 100,
				       (screenSize.Height*0.425)+30,
				       (screenSize.Width*0.8) + 100,
				       (screenSize.Height*0.425+30)+75),
		  _elem, 3, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingssuicide.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
}

void				Settings::init_third_line(const irr::core::dimension2du& screenSize)
{
   ////////////////////////////AVANCER//////////////////////


  text_to_add = _gui->addStaticText(L"UP ARROW key", irr::core::rect<int>(
						       screenSize.Width*0.2 - 100,
						       (screenSize.Height*0.60),
						       (screenSize.Width*0.2) + 100,
						       (screenSize.Height*0.60)+30),
		      false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
					      screenSize.Width*0.2 - 100,
					      ((screenSize.Height*0.60)+30),
					      (screenSize.Width*0.2) + 100,
					      (screenSize.Height*0.60+30)+75),
			 _elem, 0, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingscamup.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ////////////////////////////RECULER///////////////////////

  text_to_add = _gui->addStaticText(L"DOWN ARROW key", irr::core::rect<int>(
						       screenSize.Width*0.4 - 100,
						       (screenSize.Height*0.60),
						       (screenSize.Width*0.4)+100,
						       (screenSize.Height*0.60)+30),
		      false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
					      screenSize.Width*0.4 - 100,
					      (screenSize.Height*0.60)+30,
					      (screenSize.Width*0.4)+100,
					      (screenSize.Height*0.60+30)+75),
			 _elem, 1, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingscamdown.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ////////////////////////////Cam Gauche///////////////////////

  text_to_add = _gui->addStaticText(L"LEFT ARROW key", irr::core::rect<int>(
						      screenSize.Width*0.6 - 100,
						      (screenSize.Height*0.60),
						      (screenSize.Width*0.6)+100,
						      (screenSize.Height*0.60)+30),
		      false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
					       screenSize.Width*0.6 - 100,
					       (screenSize.Height*0.60)+30,
					       (screenSize.Width*0.6)+100,
					       (screenSize.Height*0.60+30)+75),
			  _elem, 2, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingscamleft.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
  ///////////////////////////cam DROITE///////////////////////

  text_to_add = _gui->addStaticText(L"RIGHT ARROW key", irr::core::rect<int>(
						   screenSize.Width*0.8 - 100,
						   (screenSize.Height*0.60),
						   (screenSize.Width*0.8)+100,
						   (screenSize.Height*0.60)+30),
				    false, false, _elem, -1);
  text_to_add->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
  text_to_add->setBackgroundColor(irr::video::SColor(255, 0, 0, 0));
  btn_to_add = _gui->addButton(irr::core::rect<int>(
				       screenSize.Width*0.8 - 100,
				       (screenSize.Height*0.60)+30,
				       (screenSize.Width*0.8)+100,
				       (screenSize.Height*0.60+30)+75),
		  _elem, 3, L"",NULL);
  btn_to_add->setImage(_driver->getTexture("./misc/GUI/settings/settingscamright.png"));
  text_to_add->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
  btn_key.push_back(btn_to_add);
  text_key.push_back(text_to_add);
  Press_btn.push_back(false);
}

irr::gui::IGUIEnvironment	*Settings::getGui() const
{ return (_gui); }

void				Settings::drawAll()
{  _gui->drawAll(); }

void				Settings::setVisible(bool i)
{_elem->setVisible(i); }
