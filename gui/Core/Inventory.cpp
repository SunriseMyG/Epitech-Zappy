/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Inventory.hpp"
#include "../Factory/FactoryUI.hpp"

Zappy::Inventory::Inventory()
{
    FactoryUI &fUI = FactoryUI::GetInstance();
    this->_hidden = true;
    this->_itemsNbr = std::vector<unsigned int>(7, 0);
    this->_inventorySprite = fUI.createUI("Inventory");
    Vector2 pos = this->_inventorySprite->getPosition();
    for (int i = 0; i < 7; i++) {
        this->_itemSprites.push_back(fUI.createUI("Item" + std::to_string(i)));
        this->_itemText.push_back(fUI.createUI("ItemText"));
        this->_itemSprites[i].get()->setPosition(pos);
        this->_itemText[i].get()->setPosition(Vector2{pos.x + 120, pos.y + 120});
        pos.x += 160;
    }
    this->setItems(this->_itemsNbr);
    this->_infoText = fUI.createUI("ItemText");
    this->_infoText->setPosition(Vector2{10, 200});
}

Zappy::Inventory::~Inventory()
{

}

void Zappy::Inventory::drawInventory()
{
    if (this->_hidden) {
        return;
    }
    this->_inventorySprite.get()->draw();
    int index = 0;
    for (auto &icon: this->_itemSprites) {
        if (this->_itemsNbr[index] > 0) {
            icon->draw();
        }
        index++;
    }
    for (auto &text: this->_itemText) {
        text->draw();
    }
    this->_infoText->draw();
}

const std::vector<unsigned int> &Zappy::Inventory::getItems()
{
    return this->_itemsNbr;
}

void Zappy::Inventory::setItems(const std::vector<unsigned int> &items)
{
    this->_itemsNbr = items;
    int index = 0;
    for (auto &text: this->_itemText) {
        text.get()->setText(std::to_string(this->_itemsNbr[index]));
        index++;
    }
}

void Zappy::Inventory::setHidden(const bool &hidden)
{
    this->_hidden = hidden;
}

void Zappy::Inventory::setInfo(const std::string &info)
{
    this->_infoText->setText(info);
}
