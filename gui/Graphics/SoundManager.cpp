/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** FactoryObject
*/

#include "SoundManager.hpp"

SoundManager::SoundManager()
{
    InitAudioDevice();
    SetMasterVolume(0.3f);

    _allSounds["Music"] = LoadSound("./assets/sounds/music.mp3");
    _allSounds["Death"] = LoadSound("./assets/sounds/death.mp3");
    _allSounds["IncantationStart"] = LoadSound("./assets/sounds/anvil.mp3");
    _allSounds["IncantationEnd"] = LoadSound("./assets/sounds/levelup.mp3");
    _allSounds["Music"] = LoadSound("./assets/sounds/music.mp3");
    _allSounds["Spawn"] = LoadSound("./assets/sounds/egg_hatched.mp3");
    _allSounds["Fork"] = LoadSound("./assets/sounds/start_fork.mp3");
    _allSounds["EggDeath"] = LoadSound("./assets/sounds/egg_break.mp3");
    _allSounds["EggSpawn"] = LoadSound("./assets/sounds/end_fork.mp3");
}

SoundManager::~SoundManager()
{
    for (auto &sound : this->_allSounds) {
        UnloadSound(sound.second);
    }
    CloseAudioDevice();
}

SoundManager &SoundManager::GetInstance()
{
    static SoundManager instance;
    return instance;
}

void SoundManager::playAudio(const std::string soundName)
{
    if (_allSounds.count(soundName) == 0) {
        throw ErrorException("This sound does not exist in the manager");
    }
    if (!IsSoundPlaying(_allSounds[soundName]) && IsAudioDeviceReady()) {
        PlaySound(_allSounds[soundName]);
    }
}