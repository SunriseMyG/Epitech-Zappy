/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef Sprite_H_
    #define Sprite_H_

    #include "AUI.hpp"

    namespace Graphic
    {
        class Sprite : public Graphic::AUI
        {


            public:
                Sprite(std::string textureFile, int width, int height);
                Sprite(Texture2D texture, int width, int height);
                ~Sprite();

        };
    }

#endif