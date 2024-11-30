/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef EGG_H_
    #define EGG_H_

    #include "../includes/Headers.hpp"
    #include "../Interfaces/IObject.hpp"

    namespace Zappy
    {

        class Egg
        {
            public:
                Egg(std::vector<std::string> eggInfo);
                ~Egg();
                void drawEgg();

                const int &getPlayerID();


            private:
                std::shared_ptr<Graphic::IObject> _eggObject;
                int _playerID;
        };
    }

#endif