/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "MyCamera.hpp"

Graphic::MyCamera::MyCamera()
{
    this->_camera = { 0 };
    this->_camera.fovy = 45.0f;
    this->_camera.projection = CAMERA_PERSPECTIVE;
    this->_camera.up = Vector3{0,1,0};
    // UpdateCameraPro(&this->_camera, Vector3{0,0,0}, Vector3{0, 0, 30}, 0);

}

Graphic::MyCamera::~MyCamera()
{
    
}

void Graphic::MyCamera::setTarget(const Vector3 &target)
{
    this->_camera.target = target;
}

void Graphic::MyCamera::setPosition(const Vector3 &position)
{
    this->_camera.position = position;
}

void Graphic::MyCamera::moveCamera()
{
    UpdateCameraPro(&this->_camera,
            (Vector3){
                (IsKeyDown(KEY_UP))*3.0f - (IsKeyDown(KEY_DOWN))*3.0f,
                (IsKeyDown(KEY_RIGHT))*3.0f - (IsKeyDown(KEY_LEFT))*3.0f,
                0.0f
            }, Vector3{0, 0, 0},
            0.0f);
}

void Graphic::MyCamera::begin3D()
{
    BeginMode3D(this->_camera);
}

void Graphic::MyCamera::end3D()
{
    EndMode3D();
}

const Camera &Graphic::MyCamera::getCoreCamera()
{
    return this->_camera;
}
