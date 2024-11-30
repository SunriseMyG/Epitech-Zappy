/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef SOUND_MANAGER_H_
    #define SOUND_MANAGER_H_

    #include "../Interfaces/IObject.hpp"

        class SoundManager
        {
            public:
                static SoundManager &GetInstance();
                void playAudio(const std::string soundName);


            protected:
                SoundManager();
                ~SoundManager();
                SoundManager(const SoundManager&) = delete;
                SoundManager& operator=(const SoundManager&) = delete;

                std::map<std::string, Sound> _allSounds;

        };

#endif