
//
// Menu.hpp for Project-Master in /home/louis/Documents/cpp_indie_studio
//
// Made by jurczy_l
// Login   <louis.jurczyk@epitech.eu>
//
// Started on  Thu May 25 15:25:17 2017 jurczy_l
// Last update Tue Jun 27 15:25:15 2017 louis
//

#ifndef			SETTINGS_HPP_
# define		SETTINGS_HPP_

#include		<vector>
#include		<map>
#include		<iostream>
#include		<IGUICheckBox.h>
#include		"irrlicht.h"
#include		"Constants.hpp"
#include		"AScene.hpp"
#include		"Event.hpp"

class			Settings : public AScene
{
public:
  Settings();
  ~Settings();

  void			update();
  void			drawAll();
  void			setVisible(bool);
  void			reset();
  void			init_first_line(const irr::core::dimension2du& screenSize);
  void			init_second_line(const irr::core::dimension2du& screenSize);
  void			init_third_line(const irr::core::dimension2du& screenSize);
  bool			OnEvent(const irr::SEvent& event);
  bool			Checker(irr::EKEY_CODE key);
  void			add_elem();
  void			key_change();
  irr::gui::IGUIEnvironment		*getGui() const;
private:
  bool					fullscreen;
  bool					sound;
  bool					isApply;

  std::vector<irr::gui::IGUIButton*>	btn_key;
  std::vector<irr::gui::IGUIStaticText*>	text_key;
  std::vector<bool>			Press_btn;
  irr::gui::IGUIButton			*btn_to_add;
  irr::gui::IGUIStaticText	       	*text_to_add;
  irr::gui::IGUIButton			*left;
  irr::gui::IGUIButton			*jump;

  std::map<int, Constants::Action>	link_keys;

  irr::gui::IGUICheckBox		*fullsrn_box;
  irr::gui::IGUICheckBox		*sound_box;
  irr::gui::IGUIStaticText		*text_sound;
  irr::gui::IGUIButton			*apply;
  irr::gui::IGUIButton			*quit;
  irr::gui::IGUIEnvironment             *_gui;
  irr::gui::IGUIElement			*_elem;
  irr::gui::IGUISkin			*_skin;
};

#endif
