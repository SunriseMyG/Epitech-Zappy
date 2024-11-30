/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "AUI.hpp"

Graphic::AUI::AUI(std::string textureFile, int width, int height)
{
    this->_texture = LoadTexture(textureFile.c_str());
    this->_sprite = Rectangle{0, 0, (float)width, (float)height};
    this->_sprite.width = width;
    this->_sprite.height = height;
}

Graphic::AUI::AUI(Texture2D texture, int width, int height)
{
    this->_texture = texture;
    this->_sprite = Rectangle{0, 0, (float)width, (float)height};
    this->_sprite.width = width;
    this->_sprite.height = height;
}

Graphic::AUI::~AUI()
{
    //UnloadTexture(this->_texture);
}

void Graphic::AUI::draw()
{
    DrawTextureRec(_texture, _sprite, _position, WHITE);
}

const Vector2& Graphic::AUI::getPosition() const
{
    return this->_position;
}

void Graphic::AUI::setPosition(const Vector2& position)
{
    this->_position = position;
}

void Graphic::AUI::setSpriteState(int stateID)
{
    this->_sprite.x = this->_sprite.height * stateID;
}

void Graphic::AUI::setText(const std::string& text)
{
    
}
