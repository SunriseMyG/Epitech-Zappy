/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef AOBJECT_H_
    #define AOBJECT_H_

    #include "../Interfaces/IObject.hpp"

    namespace Graphic
    {
        class AObject : public Graphic::IObject
        {
            public:
                AObject(std::string objFile);
                AObject(Model newModel);
                AObject(Model newModel, std::string objFile);
                ~AObject();
                void draw();
                void animate(int animID);
                const Vector3& getPosition() const;
                const Vector3& getRotation() const;
                const Vector3& getScale() const;
                const Color& getColor() const;
                const BoundingBox& getHitbox() const;
                void setPosition(const Vector3& position);
                void setRotation(const Vector3& rotation);
                void setScale(const Vector3& scale);
                void setColor(const Color& color);
                void setHitbox(const BoundingBox& hitbox);

            private:
                Model _model;
                Vector3 _position;
                Vector3 _rotation;
                Vector3 _scale;
                Color _color;
                BoundingBox _hitbox;
                ModelAnimation *_anims;
                int _animcount;
                int _framecount;

        };
    }

#endif