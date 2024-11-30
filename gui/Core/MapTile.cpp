/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "MapTile.hpp"
#include "../Factory/FactoryObject.hpp"

Zappy::MapTile::MapTile(Vector3 pos)
{
    FactoryObject &fObject = FactoryObject::GetInstance();
    this->_tileObject = fObject.createObject("MapTile");
    this->_tileObject->setScale(Vector3{10,10,10});
    this->_tileObject->setPosition(pos);
    this->_items = std::vector<unsigned int>(7, 0);
    this->_itemObjects.push_back(fObject.createObject("Food"));
    this->_itemObjects.at(0).get()->setPosition(Vector3{pos.x - 6, pos.y + POS_DIFF - 1.3f, pos.z - 7});
    this->_itemObjects.at(0).get()->setScale(Vector3{2, 2, 2});
    this->_itemObjects.at(0).get()->setRotation(Vector3{0, 3.1f, 1.5f});
    this->_itemObjects.push_back(fObject.createObject("Linemate"));
    this->_itemObjects.at(1).get()->setPosition(Vector3{pos.x, pos.y + POS_DIFF * 1.1f, pos.z - 7});
    this->_itemObjects.at(1).get()->setRotation(Vector3{-1.5f, 0, 0});
    this->_itemObjects.push_back(fObject.createObject("Deraumere"));
    this->_itemObjects.at(2).get()->setPosition(Vector3{pos.x + 7, pos.y + POS_DIFF * 1.1f, pos.z - 7});
    this->_itemObjects.at(2).get()->setRotation(Vector3{-1.5f, 0, 0});
    this->_itemObjects.push_back(fObject.createObject("Sibur"));
    this->_itemObjects.at(3).get()->setPosition(Vector3{pos.x - 7, pos.y + POS_DIFF * 1.1f, pos.z});
    this->_itemObjects.at(3).get()->setRotation(Vector3{-1.5f, 0, 0});
    this->_itemObjects.push_back(fObject.createObject("Mendiane"));
    this->_itemObjects.at(4).get()->setPosition(Vector3{pos.x, pos.y + POS_DIFF * 1.1f, pos.z + 3});
    this->_itemObjects.at(4).get()->setScale(Vector3{0.5f, 0.5f, 0.5f});
    this->_itemObjects.at(4).get()->setRotation(Vector3{1.5f, 1.5f, 3});
    this->_itemObjects.push_back(fObject.createObject("Phiras"));
    this->_itemObjects.at(5).get()->setPosition(Vector3{pos.x + 7, pos.y + POS_DIFF * 1.1f, pos.z});
    this->_itemObjects.at(5).get()->setRotation(Vector3{-1.5f, 0, 0});
    this->_itemObjects.push_back(fObject.createObject("Thystame"));
    this->_itemObjects.at(6).get()->setPosition(Vector3{pos.x - 7, pos.y + POS_DIFF * 1.1f, pos.z + 7});
    this->_itemObjects.at(6).get()->setRotation(Vector3{-1.5f, 0, 0});
}

Zappy::MapTile::~MapTile()
{

}

void Zappy::MapTile::drawTile()
{
    this->_tileObject->draw();
    int index = 0;
    for (auto &obj : this->_itemObjects) {
        if (this->_items.at(index) > 0) {
            obj->draw();
        }
        index++;
    }
}

const Vector3& Zappy::MapTile::getPosition()
{
    return this->_tileObject.get()->getPosition();
}

const std::vector<unsigned int> &Zappy::MapTile::getItems()
{
    return this->_items;
}

const BoundingBox &Zappy::MapTile::getHitbox()
{
    return this->_tileObject.get()->getHitbox();
}

void Zappy::MapTile::setItems(const std::vector<unsigned int> &items)
{
    this->_items = items;
}

const std::string &Zappy::MapTile::getInfo()
{
    this->updateInfo();
    return this->_info;
}

void Zappy::MapTile::updateInfo()
{
    this->_info.clear();
    this->_info += "TILE\n\nX: " + std::to_string((int)(this->getPosition().x / POS_DIFF)) + "\n";
    this->_info += "Y: " + std::to_string((int)(this->getPosition().z / POS_DIFF)) + "\n";
}