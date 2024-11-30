/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef TEXT_H_
    #define TEXT_H_

    #include "AUIText.hpp"

    namespace Graphic
    {
        class Text : public Graphic::AUIText
        {
            public:
                Text(std::string text, float size);
                ~Text() = default;

            private:

        };
    }

#endif