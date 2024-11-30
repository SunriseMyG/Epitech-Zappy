/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef CORE_H_
    #define CORE_H_

    #include "../ServerClient/ServerClient.hpp"
    #include "MapTile.hpp"
    #include "Player.hpp"
    #include "Inventory.hpp"
    #include "Egg.hpp"
    #include "../Graphics/MyCamera.hpp"
    #include "../Graphics/MyWindow.hpp"

    namespace Zappy
    {
        class Core
        {
            public:
                typedef void(Zappy::Core::*FnPtr)(std::vector<std::string>);

                Core(std::string hostName, int port);
                ~Core();
                void displayLoop();
                void drawMap();
                void checkUpdatePlayers();
                bool checkTileSelect();
                void checkAddTeamColor(int colorNbr);
                bool checkPlayerSelect();
                void askApplyCommand(std::string command);
                void manageCommand(std::string message);
                void moveCamera();
                void mszCommand(std::vector<std::string> args);
                void pnwCommand(std::vector<std::string> args);
                void bctCommand(std::vector<std::string> args);
                void pdiCommand(std::vector<std::string> args);
                void ppoCommand(std::vector<std::string> args);
                void pinCommand(std::vector<std::string> args);
                void plvCommand(std::vector<std::string> args);
                void picCommand(std::vector<std::string> args);
                void pieCommand(std::vector<std::string> args);
                void segCommand(std::vector<std::string> args);
                void enwCommand(std::vector<std::string> args);
                void eboCommand(std::vector<std::string> args);
                void ediCommand(std::vector<std::string> args);
                void pfkCommand(std::vector<std::string> args);

            private:
                Vector2 _windowResolution;
                std::shared_ptr<Graphic::MyCamera> _camera;
                std::shared_ptr<Graphic::MyWindow> _window;
                ServerClient _client;

                Vector2 _mapSize;
                std::vector<std::shared_ptr<Zappy::MapTile>> _tiles;
                std::map<int, std::shared_ptr<Zappy::Player>> _players;
                std::map<int, std::shared_ptr<Zappy::Egg>> _eggs;
                std::shared_ptr<Inventory> _inventory;
                std::shared_ptr<Graphic::IUI> _victoryText;
                // std::unique_ptr<Graphic::IUI> _infoText;
                std::map<std::string, FnPtr> _commands;
                std::vector<Color> _teamColors;
                std::vector<std::string> _teamNames;
                std::vector<std::string> _commandArg; //used by command functions
                bool _gameEnd;
                bool _playerJustDied;

        };
    }

#endif