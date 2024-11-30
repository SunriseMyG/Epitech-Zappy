/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** FactoryObject
*/

#include "FactoryObject.hpp"
#include "../Graphics/Object.hpp"

FactoryObject::FactoryObject()
{
    _models["Tile"] = LoadModel("./assets/Grass_Block.obj");
    _models["Player"] = LoadModel("./assets/minecraft_zombie.glb");
    _models["Egg"] = LoadModel("./assets/egg.glb");
    _models["Ingot"] = LoadModel("./assets/minecraft_iron_ingot.glb");
    _models["Diamond"] = LoadModel("./assets/minecraft_diamond.glb");
    _models["IncantationIcon"] = LoadModel("./assets/minecraft_emerald.glb");
    _models["ForkIcon"] = LoadModel("./assets/minecraft_egg.glb");
    _models["Apple"] = LoadModel("./assets/apple.glb");

    _allObjects["MapTile"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Tile"]); };
    _allObjects["Egg"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Egg"]); };
    _allObjects["Player"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Player"]); };
    _allObjects["IncantationIcon"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["IncantationIcon"]); };
    _allObjects["ForkIcon"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["ForkIcon"]); };
    _allObjects["Food"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Apple"]); };
    _allObjects["Linemate"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Ingot"], ORANGE); };
    _allObjects["Deraumere"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Ingot"]); };
    _allObjects["Sibur"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Ingot"], YELLOW); };
    _allObjects["Mendiane"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Diamond"]); };
    _allObjects["Phiras"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["IncantationIcon"]); };
    _allObjects["Thystame"] = [&]() -> std::unique_ptr<Graphic::IObject> { return std::make_unique<Graphic::Object>(_models["Ingot"], DARKGRAY); };
}

FactoryObject &FactoryObject::GetInstance()
{
    static FactoryObject instance;
    return instance;
}

std::unique_ptr<Graphic::IObject> FactoryObject::createObject(const std::string objectName)
{
    if (_allObjects.count(objectName) == 0) {
        throw ErrorException("This object does not exist in the factory");
    }
    return _allObjects[objectName]();
}