//
// Map.hpp for cpp_indie_studio in /Users/eliasdemnati/Repo/Rendu/cpp_indie_studio/include
// 
// Made by Elias Demnati
// Login   <elias.demnati@epitech.net>
// 
// Started on  Mon May 22 14:55:21 2017 Elias Demnati
// Last update Wed Jun 28 14:45:08 2017 louis
//

#ifndef                                       MAP_HPP_
# define                                      MAP_HPP_

#include                                      <array>
#include                                      <vector>
#include                                      <string>
#include                                      <SDL/SDL.h>
#include		                      "irrlicht.h"
#include		                      "Constants.hpp"

class                                         Map
{
  public:
    struct layers
    {
      std::array<std::array<int, 256>, 256>   map;
      int                                     _size;
      float                                   _pers;
    };

    Map(irr::scene::ISceneManager *manager);
    ~Map();
    void                                      initBase();
    void                                      generateMap();
    Map::layers                               generateRandomLayer();
    std::array<std::array<int, 256>, 256>     getLayerArray(int currFreq);
    int                                       interpolValue(int i, int j, int currFreq) const;
    int                                       calcInterpol(int y1, int y2, int n, int delta) const;
    float                                     getTotalPers();
    void                                      calcSuccessiveLayers();
    void                                      generateVectorOfLayers();
    void                                      saveAsBmp();
    void                                      colorerPixel(SDL_Surface* s, int x, int y, Uint32 coul);
    void	                              loadTerrain(const irr::io::path mapPath);
    irr::scene::ITerrainSceneNode*		      getMap() const;
private:
    irr::scene::ITerrainSceneNode*		      _map;
    irr::scene::ISceneManager*			      _manager;
    int                                       _frq;
    int                                       _oct;
    float                                     _prs;
    int                                       _lis;
    layers                                    _random;
    std::vector<layers>                       _layers;
};

#endif
