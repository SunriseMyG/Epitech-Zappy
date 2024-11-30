/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Sprite.hpp"

Graphic::Sprite::Sprite(std::string textureFile, int width, int height) :
    AUI(textureFile, width, height)
{
    
}

Graphic::Sprite::Sprite(Texture2D texture, int width, int height) :
    AUI(texture, width, height)
{
    
}

Graphic::Sprite::~Sprite()
{

}