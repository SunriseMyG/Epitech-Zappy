/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Egg.hpp"
#include "../Factory/FactoryObject.hpp"

Zappy::Egg::Egg(std::vector<std::string> eggInfo)
{
    FactoryObject &fObject = FactoryObject::GetInstance();
    this->_eggObject = fObject.createObject("Egg");
    this->_eggObject->setScale(Vector3{20,20,20});
    this->_playerID = std::stoi(eggInfo[1]);
    this->_eggObject->setPosition(Vector3{std::stoi(eggInfo[2]) * POS_DIFF, POS_DIFF * 1.3, std::stoi(eggInfo[3]) * POS_DIFF});
}

Zappy::Egg::~Egg()
{

}

void Zappy::Egg::drawEgg()
{
    this->_eggObject->draw();
}

const int &Zappy::Egg::getPlayerID()
{
    return this->_playerID;
}
