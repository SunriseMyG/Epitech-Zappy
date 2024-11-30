/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "../includes/Headers.hpp"
    #include "../Interfaces/IObject.hpp"

    namespace Zappy
    {

        enum class Orientation{
            NORTH = 1,
            EAST = 2,
            SOUTH = 3,
            WEST = 4
        };

        class Player
        {
            public:
                Player(std::vector<std::string> playerInfo);
                ~Player();
                // void update();
                void drawPlayer();
                void updateInfo();

                const int &getPlayerID();
                const unsigned int &getLevel();
                const std::vector<unsigned int> &getInventory();
                const std::string &getTeam();
                const std::string &getInfo();
                const BoundingBox& getHitbox();
                const bool& getIncantation();

                void setLevel(const unsigned int &level);
                void setColor(Color color);
                void setMapPosition(const int &x, const int &y);
                void setInventory(const std::vector<unsigned int> &inventory);
                void setOrientation(const int &orientation);
                void setIncantation(const bool &incantating);
                void setFork(const bool &forking);


            private:
                std::shared_ptr<Graphic::IObject> _playerObject;
                std::shared_ptr<Graphic::IObject> _incantationIconObject;
                std::shared_ptr<Graphic::IObject> _forkIconObject;
                unsigned int _level;
                std::vector<unsigned int> _inventory;
                int _playerID;
                std::string _teamName;
                Orientation _orientation;
                std::string _info;
                bool _isIncantation;
                float _rotationIcon;
                bool _isFork;
        };
    }

#endif