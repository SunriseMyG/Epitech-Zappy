/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef INVENTORY_H_
    #define INVENTORY_H_

    #include "../includes/Headers.hpp"
    #include "../Interfaces/IUI.hpp"

    namespace Zappy
    {
        class Inventory
        {
            public:
                Inventory();
                ~Inventory();
                void drawInventory();
                const std::vector<unsigned int> &getItems();

                void setItems(const std::vector<unsigned int> &items);
                void setHidden(const bool &hidden);
                void setInfo(const std::string &info);

            private:
                std::unique_ptr<Graphic::IUI> _inventorySprite;
                std::vector<std::unique_ptr<Graphic::IUI>> _itemSprites;
                std::vector<std::unique_ptr<Graphic::IUI>> _itemText;
                std::vector<unsigned int> _itemsNbr;
                std::unique_ptr<Graphic::IUI> _infoText;
                bool _hidden;

        };
    }

#endif