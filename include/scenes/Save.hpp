//
// Save.cpp for  in /home/louis/Documents/cpp_indie_studio/include/scenes
// 
// Made by louis
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Fri Jun 16 19:03:41 2017 louis
// Last update Sat Jun 17 20:24:11 2017 louis
//

#ifndef			SAVE_HPP_
# define		SAVE_HPP_


#include		<list>
#include		<ctime>
#include		<fstream>
#include		<ios>
#include		<string>
#include		<iostream>
#include                <sys/types.h>
#include                <dirent.h>
#include		"irrlicht.h"
#include		"Constants.hpp"
#include		"AScene.hpp"
#include		"Event.hpp"
#include		"xmlwriter.hpp"
#include		"APlayer.hpp"
#include		"Human.hpp"

class			Save : public AScene
{
public:
  Save(std::vector<AScene *> scenes);
  ~Save();

  void			update();
  void			drawAll();
  void			setVisible(bool);
  irr::gui::IGUIEnvironment	*getGui() const;
private:

  std::string		copy_file();
  std::vector<AScene *>                 _scenes;
  void			read_xml(std::string fd);
  void			write_xml();
  irr::gui::IGUIEnvironment             *_gui;
  irr::gui::IGUIElement			*_elem;
  irr::gui::IGUIButton			*b_quit;
  irr::gui::IGUIButton			*b_play;
  irr::gui::IGUIButton			*b_savefile;
  irr::gui::IGUIEditBox			*fd;
  irr::gui::IGUIListBox		*save_file;
  std::list<std::string>	file_path;
};

#endif
