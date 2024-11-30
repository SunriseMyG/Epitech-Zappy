/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef IOBJECT_H_
    #define IOBJECT_H_

    #include "../includes/Headers.hpp"

    namespace Graphic
    {
        class IObject
        {
            public:
                virtual ~IObject() = default;

                virtual void draw() = 0;
                virtual void animate(int animID) = 0;
                virtual const Vector3& getPosition() const = 0;
                virtual const Vector3& getRotation() const = 0;
                virtual const Vector3& getScale() const = 0;
                virtual const Color& getColor() const = 0;
                virtual const BoundingBox& getHitbox() const = 0;
                virtual void setPosition(const Vector3& position) = 0;
                virtual void setRotation(const Vector3& rotation) = 0;
                virtual void setScale(const Vector3& scale) = 0;
                virtual void setColor(const Color& color) = 0;
                virtual void setHitbox(const BoundingBox& hitbox) = 0;


        };
    }

#endif