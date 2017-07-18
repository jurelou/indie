#ifndef                   SOUNDENGINE_HPP_
# define                  SOUNDENGINE_HPP_

#include                  <vector>
#include                  <SFML/Audio.hpp>
#include                  "irrlicht.h"

class                     SoundEngine
{
public:
  SoundEngine();
  ~SoundEngine();
  void                    playMenuMusic();
  void                    stopMenuMusic();
  void                    playGameMusic();
  void                    stopGameMusic();
  void                    playVoice();
  void                    playExplosion();
  void                    playGun();
  void                    playKnife();
  void                    playGameEnd();
  void                    playTeleport();
  bool				getMute() const;
  void			setMute(bool mute);
private:
  bool			mute;
  sf::Music               menuMusic;
  sf::Music               gameMusic;
  std::vector<sf::SoundBuffer>  voice;
  sf::Sound               currVoice;
  sf::SoundBuffer         explosion;
  sf::Sound               explosionSound;
  sf::SoundBuffer         gun;
  sf::Sound               gunSound;
  sf::SoundBuffer         knife;
  sf::Sound               knifeSound;
  sf::SoundBuffer         teleport;
  sf::Sound               teleportSound;
  sf::SoundBuffer         gameEnd;
  sf::Sound               gameEndSound;
};

#endif
