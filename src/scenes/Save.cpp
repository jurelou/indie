//
// Save.cpp for  in /home/louis/Documents/cpp_indie_studio/src/scenes
// 
// Made by louis
// Login   <louis.jurczyk@epitech.eu>
// 
// Started on  Fri Jun 16 19:03:46 2017 louis
// Last update Sat Jun 17 21:45:08 2017 louis
//

#include	"Save.hpp"

Save::Save(std::vector<AScene *>                 scenes)
{
  irr::video::ITexture	*_img;
  irr::gui::IGUIImage	*bg;
  _scenes = scenes;
  _driver = Device->getVideoDriver();
  _event = static_cast<Event *>(Device->getEventReceiver());
  _gui = Device->getGUIEnvironment();
  const irr::core::dimension2du& screenSize = _driver->getScreenSize();
  _elem = new irr::gui::IGUIElement(
  				    irr::gui::EGUIET_ELEMENT,
  				    _gui,
  				    _gui->getRootGUIElement(),
  				    -1,
  				    irr::core::rect<irr::s32>(0,0,screenSize.Width,screenSize.Height)
  				    );
  _elem->setVisible(false);
  _img = _driver->getTexture("./misc/GUI/background_menu.jpg");
  bg = _gui->addImage(irr::core::rect<irr::s32>(0, 0, screenSize.Width, screenSize.Height), _elem);
  bg->setImage(_img);
  bg->setScaleImage(true);
  fd = _gui ->addEditBox(L"./save/save.xml",
						  irr::core::rect<irr::s32>((screenSize.Width * 0.8) - 200,
									    screenSize.Height * 0.325,
									    (screenSize.Width * 0.8) + 200,
									    screenSize.Height * 0.325 + 50),
						  true,
						  _elem);
  b_quit  = _gui->addButton(irr::core::rect<int>((screenSize.Width / 2) - 100,
						 screenSize.Height * 0.80,
						 (screenSize.Width / 2) + 100,
						 screenSize.Height * 0.80 + 75),
			    _elem,
			    Constants::EXIT,
			    L"");
  b_quit->setImage(_driver->getTexture("./misc/GUI/save/savemenu.png"));
  b_quit->setScaleImage();
  b_quit->setUseAlphaChannel(true);

  //
  b_savefile  = _gui->addButton(irr::core::rect<int>((screenSize.Width * 0.8) - 100,
						     screenSize.Height * 0.45,
						     (screenSize.Width * 0.8) + 100,
						     screenSize.Height * 0.45 + 75),
			    _elem,
			    Constants::EXIT,
			    L"");
  b_savefile->setPressedImage(_driver->getTexture("./misc/GUI/save/savesaveon.png"));
  b_savefile->setImage(_driver->getTexture("./misc/GUI/save/savesave.png"));
  b_savefile->setScaleImage();
  b_savefile->setUseAlphaChannel(true);
  //

  b_play  = _gui->addButton(irr::core::rect<int>((screenSize.Width * 0.2) - 100,
						 screenSize.Height * 0.45,
						 (screenSize.Width * 0.2) + 100,
						 screenSize.Height * 0.45 + 75),
			    _elem,
			    Constants::PLAYING,
			    L"");
  b_play->setPressedImage(_driver->getTexture("./misc/GUI/save/saveloadon.png"));
  b_play->setImage(_driver->getTexture("./misc/GUI/save/saveload.png"));
  b_play->setScaleImage();
  b_play->setUseAlphaChannel(true);

  save_file = _gui->addListBox(irr::core::rect<irr::s32>(screenSize.Width * 0.2 - 50,
							 screenSize.Height * 0.3,
							 screenSize.Width * 0.2 + 50,
							 screenSize.Height * 0.3 + 100),
			       _elem);
  int   cpt;
  cpt = 0;
  DIR * rep = opendir("./save/");
  if (rep != NULL)
    {
      struct dirent * ent;
      while ((ent = readdir(rep)) != NULL)
	if (ent->d_name[0] != '.')
	  file_path.push_back(ent->d_name);
      closedir(rep);
    }
  std::wstring widestr;
  for (auto it : file_path)
    {
      widestr = std::wstring(it.begin(), it.end());
      save_file->addItem(widestr.c_str());
    }
  save_file->setAutoScrollEnabled(true);
}
Save::~Save()
{
}

void				Save::read_xml(std::string fd)
{
  irr::io::IrrXMLReader		*xml = irr::io::createIrrXMLReader(fd.c_str());
  std::string		map_file;
  float x, y, z;
  int hp, isRandom, nbPlayers, nbIA ,current;

  GInfo._players.clear();
  while (xml && xml->read())
    {
      switch(xml->getNodeType())
	{
	case irr::io::EXN_ELEMENT:
	  {
	    if (!strcmp("data", xml->getNodeName()))
	      {
		nbPlayers = xml->getAttributeValueAsInt("nbPlayers");
		current = xml->getAttributeValueAsInt("current");
		nbIA = xml->getAttributeValueAsInt("nbIA");
	      }
	    else if (!strcmp("map", xml->getNodeName()))
	      {
		isRandom = xml->getAttributeValueAsInt("isRandom");
		map_file = xml->getAttributeValue("path");
	      }
	    else if (!strcmp("Human", xml->getNodeName()))
	      {
		
		x = xml->getAttributeValueAsFloat("x");
		y = xml->getAttributeValueAsFloat("y");
		z = xml->getAttributeValueAsFloat("z");
		hp = xml->getAttributeValueAsInt("hp");
		std::cout << "human: " << x << " " << y << " " << z << "hp=>" << hp <<std::endl;
	      }
	  }
	  break;
	}
    }
  if (current >= 0  &&  nbPlayers > 0)
    {
      GInfo._nbPlayers = nbPlayers;
      GInfo._nbIA = nbIA;
      GInfo.currentPlayer = current;
      if (map_file.size() == 0)
	return;
      GInfo._pathMap = map_file;
      GInfo._isRandomMap = false;
      delete _scenes.at(Constants::WindowState::PLAYING);
      _scenes.at(Constants::PLAYING) = NULL;
      GInfo._reset = false;
      GInfo._players.clear();
      GInfo._objects.clear();
      std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~"<<std::endl;
      std::cout << GInfo._nbPlayers <<std::endl;
      std::cout << GInfo._nbIA <<std::endl;
      std::cout << GInfo._players.size() <<std::endl;
      WINDOW_STATE  = Constants::PLAYING;
    }
  delete xml;
}

std::string		Save::copy_file()
{
  std::string		res;
  std::time_t t = std::time(0);

  res = "./save/maps/" + std::to_string(t) + ".save";

  std::ifstream source("./map/.randomap.bmp", std::ios::binary);
  std::ofstream dest(res, std::ios::binary); 

  std::istreambuf_iterator<char> begin_source(source);
  std::istreambuf_iterator<char> end_source;
  std::ostreambuf_iterator<char> begin_dest(dest);
  copy(begin_source, end_source, begin_dest);
  source.close();
  dest.close();
  return (res);  
}

void				Save::write_xml()
{
  if (GInfo.currentPlayer == -1)
    return;
  irr::core::stringw filename;
  irr::core::stringc tmp;
  tmp = fd->getText();
  filename = tmp.c_str();
  irr::io::IXMLWriter* xwriter = Device->getFileSystem()->createXMLWriter( filename );
  if (!xwriter)
    Device->drop();
  
  xwriter->writeXMLHeader();

  irr::core::stringw characterName = L"Dom Fernando" ;
  xwriter->writeElement(L"data",true,
			L"nbPlayers", std::to_wstring(GInfo._nbPlayers).c_str(),
			L"current", std::to_wstring(GInfo.currentPlayer).c_str(),
			L"nbIA", std::to_wstring(GInfo._nbIA).c_str());

  xwriter->writeLineBreak();


  
  if (GInfo._isRandomMap == true)
    {
      std::string str = this->copy_file();
      std::wstring wstr(str.begin(), str.end());
      xwriter->writeElement(L"map",true,
			    L"isRandom", std::to_wstring(GInfo._isRandomMap).c_str(),
			    L"path", wstr.c_str());
      std::cout << wstr.c_str() << std::endl;
    }
  else
    {
      std::wstring toto(GInfo._pathMap.begin(), GInfo._pathMap.end());
      xwriter->writeElement(L"map",true,
			    L"isRandom", std::to_wstring(GInfo._isRandomMap).c_str(),
			    L"path", toto.c_str());
    }

  
  
  for (int i = 0; i < GInfo._players.size(); i++)
    {
      xwriter->writeElement(L"Human",true,
			    L"x", std::to_wstring(GInfo._players.at(i)->getPosition().X).c_str(),
			    L"y", std::to_wstring(GInfo._players.at(i)->getPosition().Y).c_str(),
			    L"z", std::to_wstring(GInfo._players.at(i)->getPosition().Z).c_str(),
			    L"hp",std::to_wstring(GInfo._players.at(i)->getHp()).c_str());
      xwriter->writeLineBreak();
    }
  xwriter->drop();
}

void				Save::update()
{
  if (GInfo._players.size() > 0)
    {
      b_savefile->setVisible(true);
      save_file->setVisible(false);
      fd->setVisible(true);
      b_play->setVisible(false);
    }
  else
    {
      b_savefile->setVisible(false);
      fd->setVisible(false);
      b_play->setVisible(true);
      save_file->setVisible(true);
    }
  
  if (b_quit->isPressed())
    WINDOW_STATE = Constants::MAIN_MENU;
  else if (b_play->isPressed())
    {
      int i = 0;
      for (auto it : file_path)
	{
	  if (i == save_file->getSelected())
	    {
	      std::string toto = "./save/" + it;
	      this->read_xml(toto);
	      break;
	    }
	  i++;
	}
    }
  else if (b_savefile->isPressed())
    {
      this->write_xml();
    }
}

irr::gui::IGUIEnvironment	*Save::getGui() const
{ return (_gui); }

void				Save::drawAll()
{
  _gui->drawAll();
}

void				Save::setVisible(bool i)
{ _elem->setVisible(i); }
