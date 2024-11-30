/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** FactoryObject
*/

#include "FactoryUI.hpp"
#include "../Graphics/Sprite.hpp"
#include "../Graphics/Text.hpp"

FactoryUI::FactoryUI()
{
    _sprites["InventorySlots"] = LoadTexture("./assets/slots_inventory.png");
    _sprites["Item0"] = LoadTexture("./assets/item0.png");
    _sprites["Item1"] = LoadTexture("./assets/item1.png");
    _sprites["Item2"] = LoadTexture("./assets/item2.png");
    _sprites["Item3"] = LoadTexture("./assets/item3.png");
    _sprites["Item4"] = LoadTexture("./assets/item4.png");
    _sprites["Item5"] = LoadTexture("./assets/item5.png");
    _sprites["Item6"] = LoadTexture("./assets/item6.png");

    _allUIs["Item0"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Sprite>(_sprites["Item0"], 160, 160); };
    _allUIs["Item1"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Sprite>(_sprites["Item1"], 160, 160); };
    _allUIs["Item2"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Sprite>(_sprites["Item2"], 160, 160); };
    _allUIs["Item3"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Sprite>(_sprites["Item3"], 160, 160); };
    _allUIs["Item4"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Sprite>(_sprites["Item4"], 160, 160); };
    _allUIs["Item5"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Sprite>(_sprites["Item5"], 160, 160); };
    _allUIs["Item6"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Sprite>(_sprites["Item6"], 160, 160); };
    _allUIs["Inventory"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Sprite>(_sprites["InventorySlots"], 1136, 176); };
    _allUIs["ItemText"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Text>("0", 50); };
    _allUIs["VictoryText"] = [&]() -> std::unique_ptr<Graphic::IUI> { return std::make_unique<Graphic::Text>("0", 150); };
}


FactoryUI &FactoryUI::GetInstance()
{
    static FactoryUI instance;
    return instance;
}

std::unique_ptr<Graphic::IUI> FactoryUI::createUI(const std::string UIName)
{
    if (_allUIs.count(UIName) == 0) {
        throw ErrorException("This UI element does not exist in the factory");
    }
    return _allUIs[UIName]();
}