/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef MAP_PIECE_H_
    #define MAP_PIECE_H_

    #include "../includes/Headers.hpp"
    #include "../Interfaces/IObject.hpp"

    namespace Zappy
    {
        class MapTile
        {
            public:
                MapTile(Vector3 pos);
                ~MapTile();
                // void updateTile();
                void drawTile();
                const Vector3& getPosition();
                const BoundingBox& getHitbox();
                const std::string &getInfo();
                const std::vector<unsigned int> &getItems();

                void setItems(const std::vector<unsigned int> &items);
                void updateInfo();

            private:
                std::unique_ptr<Graphic::IObject> _tileObject;
                std::vector<std::unique_ptr<Graphic::IObject>> _itemObjects;
                std::vector<unsigned int> _items;
                std::string _info;

        };
    }

#endif