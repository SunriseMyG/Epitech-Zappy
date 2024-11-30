/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef AUITEXT_H_
    #define AUITEXT_H_

    #include "../Interfaces/IUI.hpp"

    namespace Graphic
    {
        class AUIText : public Graphic::IUI
        {
            public:
                AUIText(std::string text, float size);
                ~AUIText();
                void draw();
                const Vector2& getPosition() const;
                void setPosition(const Vector2& position);
                void setText(const std::string& text);

            private:
                Vector2 _position;
                std::string _text;
                float _size;
                Font _font;
        };
    }

#endif