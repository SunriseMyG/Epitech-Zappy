/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "MyWindow.hpp"

Graphic::MyWindow::MyWindow(int x, int y)
{
    InitWindow(x, y, "Trantor");
    this->_resolution.x = x;
    this->_resolution.y = y;
}

Graphic::MyWindow::~MyWindow()
{
    
}

bool Graphic::MyWindow::isOpen()
{
    return !WindowShouldClose();
}

bool Graphic::MyWindow::isMousePressed()
{
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Graphic::MyWindow::beginDrawing()
{
    BeginDrawing();
    ClearBackground(Color({0,200,200,255}));
}

void Graphic::MyWindow::endDrawing()
{
    EndDrawing();
}

void Graphic::MyWindow::computeMouseWorldRay(Graphic::MyCamera *camera)
{
    this->_mouseRay = GetScreenToWorldRay(GetMousePosition(), camera->getCoreCamera());
}

bool Graphic::MyWindow::isHitboxSelectedByMouse(BoundingBox hitbox)
{
    return GetRayCollisionBox(_mouseRay, hitbox).hit;
}

bool Graphic::MyWindow::isMouseCloseToPosition(Vector3 position, Graphic::MyCamera *camera)
{
    return !Vector2Distance(GetMousePosition(), GetWorldToScreenEx(position, camera->getCoreCamera(), 0, 0) ) > 2;
}