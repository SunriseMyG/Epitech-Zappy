/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef Object_H_
    #define Object_H_

    #include "AObject.hpp"

    namespace Graphic
    {
        class Object : public Graphic::AObject
        {
            public:
                Object(std::string objFile);
                Object(Model newModel);
                Object(Model newModel, std::string objFile);
                Object(std::string objFile, Color color);
                Object(Model newModel, Color color);
                ~Object() = default;

            private:

        };
    }

#endif