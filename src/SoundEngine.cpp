#include        <string>
#include        <iostream>
#include        "SoundEngine.hpp"

SoundEngine::SoundEngine()
{
  this->menuMusic.openFromFile("./misc/music/menu.ogg");
  this->gameMusic.openFromFile("./misc/music/game.ogg");
  for (int i = 0; i <= 7; i++)
    {
      std::string tmp("./misc/sound/voice/voice" + std::to_string(i) + ".ogg");
      this->voice.push_back(sf::SoundBuffer());
      this->voice.at(i).loadFromFile(tmp);
    }
  this->explosion.loadFromFile("./misc/sound/explosion.wav");
  this->gun.loadFromFile("./misc/sound/gun.ogg");
  this->knife.loadFromFile("./misc/sound/knife.ogg");
  this->gameEnd.loadFromFile("./misc/sound/win.ogg");
  this->teleport.loadFromFile("./misc/sound/teleport.ogg");
  mute = false;
}

SoundEngine::~SoundEngine()
{}

void            SoundEngine::playMenuMusic()
{
  this->menuMusic.play();
}

void            SoundEngine::stopMenuMusic()
{
  this->menuMusic.stop();
}

void            SoundEngine::playGameMusic()
{
  this->gameMusic.play();
}

void            SoundEngine::stopGameMusic()
{
  this->gameMusic.stop();
}

void            SoundEngine::playVoice()
{
  this->currVoice.setBuffer(this->voice.at(std::rand() % 8));
  this->currVoice.play();
}

void            SoundEngine::playExplosion()
{
  this->explosionSound.setBuffer(this->explosion);
  this->explosionSound.play();
}

void            SoundEngine::playGun()
{
  this->gunSound.setBuffer(this->gun);
  this->gunSound.play();
}

void            SoundEngine::playKnife()
{
  this->knifeSound.setBuffer(this->knife);
  this->knifeSound.play();
}

void            SoundEngine::playGameEnd()
{
  this->gameEndSound.setBuffer(this->gameEnd);
  this->gameEndSound.play();
}

void            SoundEngine::playTeleport()
{
  this->teleportSound.setBuffer(this->teleport);
  this->teleportSound.play();
}

bool            SoundEngine::getMute() const
{
  return (mute);
}

void		SoundEngine::setMute(bool mute)
{
  this->mute = mute;
}
