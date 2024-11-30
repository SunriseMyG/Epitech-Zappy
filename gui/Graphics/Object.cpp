/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Object.hpp"

Graphic::Object::Object(std::string objFile) :
    AObject(objFile)
{
    
}

Graphic::Object::Object(std::string objFile, Color color) :
    AObject(objFile)
{
    this->setColor(color);
}

Graphic::Object::Object(Model newModel) :
    AObject(newModel)
{
    
}

Graphic::Object::Object(Model newModel, std::string objFile) :
    AObject(newModel, objFile)
{
    
}

Graphic::Object::Object(Model newModel, Color color) :
    AObject(newModel)
{
    this->setColor(color);
}