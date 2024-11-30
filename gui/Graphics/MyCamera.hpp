/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef MYCAMERA_H_
    #define MYCAMERA_H_

    #include "../includes/GraphicLibrary.hpp"

    namespace Graphic
    {
        class MyCamera
        {
            public:
                MyCamera();
                ~MyCamera();
                void setTarget(const Vector3 &target);
                void setPosition(const Vector3 &position);
                const Camera &getCoreCamera();
                void moveCamera();
                void begin3D();
                void end3D();

            private:
                Camera _camera;

        };
    }

#endif