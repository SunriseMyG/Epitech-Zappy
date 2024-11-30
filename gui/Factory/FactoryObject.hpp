/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef FACTORY_OBJECT_H_
    #define FACTORY_OBJECT_H_

    #include "../Interfaces/IObject.hpp"

        class FactoryObject
        {
            public:
                static FactoryObject &GetInstance();
                std::unique_ptr<Graphic::IObject> createObject(const std::string objectName);

            protected:
                FactoryObject();
                FactoryObject(const FactoryObject&) = delete;
                FactoryObject& operator=(const FactoryObject&) = delete;

                std::map<std::string, std::function<std::unique_ptr<Graphic::IObject>()>> _allObjects;
                std::map<std::string, Model> _models;

        };

#endif