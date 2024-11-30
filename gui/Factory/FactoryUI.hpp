/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef FACTORY_UI_H_
    #define FACTORY_UI_H_

    #include "../Interfaces/IUI.hpp"

        class FactoryUI
        {
            public:
                static FactoryUI &GetInstance();
                std::unique_ptr<Graphic::IUI> createUI(const std::string UIName);

            protected:
                FactoryUI();
                FactoryUI(const FactoryUI&) = delete;
                FactoryUI& operator=(const FactoryUI&) = delete;

                std::map<std::string, std::function<std::unique_ptr<Graphic::IUI>()>> _allUIs;
                std::map<std::string, Texture2D> _sprites;

            private:

        };

#endif