/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Player.hpp"
#include "../Factory/FactoryObject.hpp"

Zappy::Player::Player(std::vector<std::string> playerInfo)
{
    FactoryObject &fObject = FactoryObject::GetInstance();
    this->_playerObject = fObject.createObject("Player");
    this->_playerObject->setScale(Vector3{10,10,10});
    this->_playerID = std::stoi(playerInfo[0]);
    this->_playerObject->setPosition(Vector3{std::stoi(playerInfo[1]) * POS_DIFF, 0, std::stoi(playerInfo[2]) * POS_DIFF});
    this->_orientation = Orientation(std::stoi(playerInfo[3]));
    this->_level = std::stoi(playerInfo[4]);
    this->_teamName = playerInfo[5];
    this->_isIncantation = false;
    this->_isFork = false;
    this->_incantationIconObject = fObject.createObject("IncantationIcon");
    this->_incantationIconObject->setScale(Vector3{5,5,5});
    this->_forkIconObject = fObject.createObject("ForkIcon");
}

Zappy::Player::~Player()
{

}

void Zappy::Player::drawPlayer()
{
    this->_playerObject->draw();
    if (this->_isIncantation) {
        this->_incantationIconObject->draw();
        this->_incantationIconObject->setRotation(Vector3{0, _rotationIcon, 3.14159f});
        _rotationIcon += 0.05f;
    }
    if (this->_isFork) {
        this->_forkIconObject->draw();
        this->_forkIconObject->setRotation(Vector3{0, _rotationIcon, 4.71239f});
        _rotationIcon += 0.05f;
    }
}

const int &Zappy::Player::getPlayerID()
{
    return this->_playerID;
}

const unsigned int &Zappy::Player::getLevel()
{
    return this->_level;
}

const std::vector<unsigned int> &Zappy::Player::getInventory()
{
    return this->_inventory;
}

const std::string &Zappy::Player::getTeam()
{
    return this->_teamName;
}

const std::string &Zappy::Player::getInfo()
{
    this->updateInfo();
    return this->_info;
}

void Zappy::Player::updateInfo()
{
    this->_info.clear();
    this->_info += "PLAYER\n\nID: " + std::to_string(this->_playerID) + "\n";
    this->_info += "Team: " + this->_teamName + "\n";
    this->_info += "Level: " + std::to_string(this->_level) + "\n";
}

void Zappy::Player::setIncantation(const bool &incantating)
{
    this->_isIncantation = incantating;
}

void Zappy::Player::setFork(const bool &forking)
{
    this->_isFork = forking;
}

const bool& Zappy::Player::getIncantation()
{
    return this->_isIncantation;
}

const BoundingBox &Zappy::Player::getHitbox()
{
    return this->_playerObject.get()->getHitbox();
}

void Zappy::Player::setLevel(const unsigned int& level)
{
    this->_level = level;
}

void Zappy::Player::setColor(Color color)
{
    this->_playerObject.get()->setColor(color);
}

void Zappy::Player::setInventory(const std::vector<unsigned int> &inventory)
{
    this->_inventory = inventory;
}

void Zappy::Player::setOrientation(const int &orientation)
{
    this->_orientation = Orientation(orientation);
    float rotationValue = 0;
    switch (this->_orientation)
    {
        case Orientation::NORTH: rotationValue = 0; break;
        case Orientation::EAST: rotationValue = 4.71239f; break;
        case Orientation::WEST: rotationValue = 1.5708f; break;
        case Orientation::SOUTH: rotationValue = 3.14159f; break;
    }
    _playerObject.get()->setRotation(Vector3{0, rotationValue, 0});
}

void Zappy::Player::setMapPosition(const int &x, const int &y)
{
    this->_playerObject->setPosition(Vector3{x * POS_DIFF, POS_DIFF, y * POS_DIFF});
    this->_incantationIconObject->setPosition(Vector3{x * POS_DIFF, POS_DIFF * 3 , y * POS_DIFF});
    this->_forkIconObject->setPosition(Vector3{x * POS_DIFF, POS_DIFF * 3 , y * POS_DIFF});
}
