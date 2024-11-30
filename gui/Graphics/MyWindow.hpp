/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef MYWINDOW_H_
    #define MYWINDOW_H_

    #include "MyCamera.hpp"

    namespace Graphic
    {
        class MyWindow
        {
            public:
                MyWindow(int x, int y);
                ~MyWindow();
                bool isOpen();
                bool isMousePressed();
                void computeMouseWorldRay(Graphic::MyCamera *camera);
                bool isHitboxSelectedByMouse(BoundingBox hitbox);
                bool isMouseCloseToPosition(Vector3 position, Graphic::MyCamera *camera);
                void beginDrawing();
                void endDrawing();

            private:
                Vector2 _resolution;
                Ray _mouseRay;

        };
    }

#endif