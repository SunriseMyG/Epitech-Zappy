/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef IUI_H_
    #define IUI_H_

    #include "../includes/Headers.hpp"

    namespace Graphic
    {
        class IUI
        {
            public:
                virtual ~IUI() = default;

                virtual void draw() = 0;
                virtual const Vector2& getPosition() const = 0;

                virtual void setPosition(const Vector2& position) = 0;
                virtual void setText(const std::string& text) = 0;



        };
    }

#endif