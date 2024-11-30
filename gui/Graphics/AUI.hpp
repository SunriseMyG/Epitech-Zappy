/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef AUI_H_
    #define AUI_H_

    #include "../Interfaces/IUI.hpp"

    namespace Graphic
    {
        class AUI : public Graphic::IUI
        {
            public:
                AUI(std::string textureFile, int width, int height);
                AUI(Texture2D texture, int width, int height);
                ~AUI();
                void draw();
                const Vector2& getPosition() const;

                void setPosition(const Vector2& position);
                void setSpriteState(int stateID);
                void setText(const std::string& text);

            private:
                Texture2D _texture;
                Rectangle _sprite;
                Vector2 _position;
                bool _isAnimated;

        };
    }

#endif