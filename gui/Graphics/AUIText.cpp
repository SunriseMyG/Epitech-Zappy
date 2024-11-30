/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "AUIText.hpp"

Graphic::AUIText::AUIText(std::string text, float size)
{
    this->_position = Vector2{0, 0};
    this->_text = text;
    this->_size = size;
    this->_font = LoadFont("./assets/Minecraft.ttf");
}

Graphic::AUIText::~AUIText()
{

}

void Graphic::AUIText::draw()
{
    DrawTextEx(_font, _text.c_str(), _position, _size, 1, WHITE);
}

const Vector2& Graphic::AUIText::getPosition() const
{
    return this->_position;
}

void Graphic::AUIText::setPosition(const Vector2& position)
{
    this->_position = position;
}

void Graphic::AUIText::setText(const std::string& text)
{
    this->_text = text;
}