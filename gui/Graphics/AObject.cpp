/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "AObject.hpp"

Graphic::AObject::AObject(std::string objFile)
{
    this->_animcount = 0;
    this->_framecount = 0;
    this->_model = LoadModel(objFile.c_str());
    this->_position = Vector3{0, 0, 0};
    this->_rotation = Vector3{1, 1, 1};
    this->_scale = Vector3{1.0f, 1.0f, 1.0f};
    this->_hitbox = GetModelBoundingBox(this->_model);
    this->_anims = LoadModelAnimations(objFile.c_str(), &this->_animcount);
    this->_color = WHITE;
}


Graphic::AObject::AObject(Model newModel)
{
    this->_animcount = 0;
    this->_framecount = 0;
    this->_model = newModel;
    this->_position = Vector3{0, 0, 0};
    this->_rotation = Vector3{1, 1, 1};
    this->_scale = Vector3{1.0f, 1.0f, 1.0f};
    this->_hitbox = GetModelBoundingBox(this->_model);
    this->_color = WHITE;
}

Graphic::AObject::AObject(Model newModel, std::string objFile)
{
    this->_animcount = 0;
    this->_framecount = 0;
    this->_model = newModel;
    this->_position = Vector3{0, 0, 0};
    this->_rotation = Vector3{1, 1, 1};
    this->_scale = Vector3{1.0f, 1.0f, 1.0f};
    this->_hitbox = GetModelBoundingBox(this->_model);
    this->_anims = LoadModelAnimations(objFile.c_str(), &this->_animcount);
    this->_color = WHITE;
}

Graphic::AObject::~AObject()
{

}

void Graphic::AObject::draw()
{
    DrawModelEx(_model, _position, _rotation, 0, _scale, _color);
}

void Graphic::AObject::animate(int animID)
{
    if (this->_animcount < animID) {
        return;
    }
    if (this->_framecount >= _anims[animID].frameCount) {
        this->_framecount = 0;
    }
    UpdateModelAnimation(_model, _anims[animID], this->_framecount);
    this->_framecount += 1;
}

const Vector3& Graphic::AObject::getPosition() const
{
    return this->_position;
}

const Vector3& Graphic::AObject::getRotation() const
{
    return this->_rotation;
}

const Vector3& Graphic::AObject::getScale() const
{
    return this->_scale;
}

const Color& Graphic::AObject::getColor() const
{
    return this->_color;
}

const BoundingBox& Graphic::AObject::getHitbox() const
{
    return this->_hitbox;
}

void Graphic::AObject::setPosition(const Vector3& position)
{
    Vector3 dif = Vector3Subtract(position, this->_position);
    this->_position = position;
    this->_hitbox.min = Vector3Add(this->_hitbox.min, dif);
    this->_hitbox.max = Vector3Add(this->_hitbox.max, dif);
}

void Graphic::AObject::setRotation(const Vector3& rotation)
{
    // this->_rotation = rotation;
    this->_model.transform = MatrixRotateXYZ((Vector3){ rotation.x, rotation.y, rotation.z });
}

void Graphic::AObject::setScale(const Vector3& scale)
{
    this->_scale = scale;
    this->_hitbox.min = Vector3Scale(this->_hitbox.min, this->_scale.x);
    this->_hitbox.max = Vector3Scale(this->_hitbox.max, this->_scale.x);
}

void Graphic::AObject::setColor(const Color& color)
{
    this->_color = color;
}

void Graphic::AObject::setHitbox(const BoundingBox& hitbox)
{
    this->_hitbox = hitbox;
}
