/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Core
*/

#include "Core.hpp"
#include "../Graphics/Sprite.hpp"
#include "../Graphics/Object.hpp"
#include "../Graphics/SoundManager.hpp"
#include "../Factory/FactoryUI.hpp"

Zappy::Core::Core(std::string hostName, int port) :
    _client(hostName, port)
{
    this->_window = std::make_shared<Graphic::MyWindow>(1920, 1080);
    this->_camera = std::make_shared<Graphic::MyCamera>();

    this->_commands["msz"] = &Zappy::Core::mszCommand;
    this->_commands["pnw"] = &Zappy::Core::pnwCommand;
    this->_commands["bct"] = &Zappy::Core::bctCommand;
    // this->_commands["pex"] = &Zappy::Core::pexCommand;
    this->_commands["ppo"] = &Zappy::Core::ppoCommand;
    this->_commands["pin"] = &Zappy::Core::pinCommand;
    this->_commands["pdi"] = &Zappy::Core::pdiCommand;
    this->_commands["plv"] = &Zappy::Core::plvCommand;
    this->_commands["pic"] = &Zappy::Core::picCommand;
    this->_commands["pie"] = &Zappy::Core::pieCommand;
    this->_commands["seg"] = &Zappy::Core::segCommand;
    this->_commands["enw"] = &Zappy::Core::enwCommand;
    this->_commands["ebo"] = &Zappy::Core::eboCommand;
    this->_commands["edi"] = &Zappy::Core::ediCommand;
    this->_commands["pfk"] = &Zappy::Core::pfkCommand;

    this->_client.sendServer("GRAPHIC");
    std::string answer = this->_client.getServer(true);
    if (answer.empty()) {
        throw ErrorException("Server is connected but not responding");
    }
    answer = this->_client.getServer(true);
    manageCommand(answer);
    this->askApplyCommand("msz");

    Vector3 middlePos = this->_tiles.at((this->_tiles.size() - 1) / 2)->getPosition();
    this->_camera->setPosition((Vector3){middlePos.x, 300.0f, middlePos.z + 200});
    this->_camera->setTarget((Vector3){middlePos.x, 0, middlePos.z});

    this->_inventory = std::make_unique<Zappy::Inventory>();
    this->_teamColors = {RED, BLUE, YELLOW, MAGENTA};

    this->_victoryText = FactoryUI::GetInstance().createUI("VictoryText");
    this->_victoryText->setPosition(Vector2{0, 800});
    this->_gameEnd = false;
    this->_playerJustDied = false;
}

Zappy::Core::~Core()
{
    CloseAudioDevice();
    CloseWindow();
}

void Zappy::Core::askApplyCommand(std::string command)
{
    this->_client.sendServer(command);
    std::string message = this->_client.getServer(true);

    if (!message.empty()) {
        manageCommand(message);
    }
}


void Zappy::Core::displayLoop()
{
    std::string message;
    std::clock_t timer = std::clock();
    SoundManager::GetInstance().playAudio("Music");
    while (this->_window->isOpen()) {
        //passive command getter
        message = this->_client.getServer(false);
        if (!message.empty()) {
            manageCommand(message);
        }
        this->_camera->moveCamera();
        if (!this->checkPlayerSelect()) {
            this->checkTileSelect();
        }
        this->_window->beginDrawing();
        this->_camera->begin3D();
        this->drawMap();
        if (!this->_gameEnd && (std::clock() - timer) > 30000) {
            checkUpdatePlayers();
            if (!this->_playerJustDied) {
                this->askApplyCommand("mct");
            } else {
                this->_playerJustDied = false;
            }
            timer = std::clock();
        }
        this->_camera->end3D();
        if (this->_gameEnd) {
            this->_victoryText->draw();
        }
        this->_inventory->drawInventory();
        this->_window->endDrawing();
    }
}


void Zappy::Core::drawMap()
{
    for (auto &tile : this->_tiles) {
        tile->drawTile();
    }
    for (auto &player : this->_players) {
        player.second->drawPlayer();
    }
    for (auto &egg : this->_eggs) {
        egg.second->drawEgg();
    }
}

void Zappy::Core::checkUpdatePlayers()
{
    for (auto &player : this->_players) {
        if (this->_players.count(player.first) != 0) {
            this->askApplyCommand("ppo " + std::to_string(player.first));
        }
    }
}

bool Zappy::Core::checkTileSelect()
{
    if (!this->_window->isMousePressed()) {
        return false;
    }
    this->_window->computeMouseWorldRay(this->_camera.get());
    bool res = false;
    for (auto &tile : this->_tiles) {
        if (this->_window->isMouseCloseToPosition(tile->getPosition(), this->_camera.get())) {
            continue;
        }
        if (this->_window->isHitboxSelectedByMouse(tile->getHitbox())) {
            this->_inventory->setHidden(false);
            this->_inventory->setInfo(tile->getInfo());
            this->_inventory->setItems(tile->getItems());
            res = true;
        }
    }
    this->_inventory->setHidden(!res);
    return res;
}

bool Zappy::Core::checkPlayerSelect()
{
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        return false;
    }
    this->_window->computeMouseWorldRay(this->_camera.get());
    for (auto &player : this->_players) {
        if (this->_window->isHitboxSelectedByMouse(player.second->getHitbox())) {
            this->askApplyCommand("pin " + std::to_string(player.first));
            this->askApplyCommand("plv " + std::to_string(player.first));
            this->_inventory->setHidden(false);
            this->_inventory->setItems(player.second->getInventory());
            this->_inventory->setInfo(player.second->getInfo());
            return true;
        }
    }
    this->_inventory->setHidden(true);
    return false;
}

void Zappy::Core::checkAddTeamColor(int colorNbr)
{
    std::srand(std::time(nullptr));
    if (colorNbr >= this->_teamColors.size()) {
        Color newColor {0, 0, 0, 255};
        newColor.r = std::rand() % 255;
        newColor.g = std::rand() % 255;
        newColor.b = std::rand() % 255;
        this->_teamColors.push_back(newColor);
    }
}

void Zappy::Core::manageCommand(std::string message)
{
    std::regex reg2("\n");
    auto begin = std::sregex_token_iterator(message.begin(), message.end(), reg2, -1);
    auto end = std::sregex_token_iterator();
    std::vector<std::string> commandList(begin, end);
    for (auto &command : commandList) {
        std::regex reg("\\ ");
        begin = std::sregex_token_iterator(command.begin(), command.end(), reg, -1);
        end = std::sregex_token_iterator();
        std::vector<std::string> res(begin, end);
        std::string type(res[0]);
        res.erase(res.begin());
        if (this->_commands.count(type) != 0) {
            (this->*_commands[type])(res);
        }
    }
}

void Zappy::Core::mszCommand(std::vector<std::string> args)
{
    this->_mapSize.x = std::stoi(args[0]);
    this->_mapSize.y = std::stoi(args[1]);
    for (float i = 0; i < _mapSize.y; i++) {
        for (float j = 0; j < _mapSize.x; j++) {
            this->_tiles.push_back(std::make_shared<Zappy::MapTile>(Vector3{j * POS_DIFF, 0, i * POS_DIFF}));
        }
    }
}

void Zappy::Core::pnwCommand(std::vector<std::string> args)
{
    this->_players[std::stoi(args[0])] = std::make_shared<Zappy::Player>(args);

    int i = 0;
    for (auto e: this->_teamNames) {
        if (e == args[5]) {
            this->checkAddTeamColor(i);
            this->_players[std::stoi(args[0])].get()->setColor(this->_teamColors[i]);
            return;
        }
        i++;
    }
    this->checkAddTeamColor(i);
    this->_teamNames.push_back(args[5]);
    this->_players[std::stoi(args[0])].get()->setColor(this->_teamColors[this->_teamNames.size() - 1]);
}

void Zappy::Core::bctCommand(std::vector<std::string> args)
{
    int tileNbr = std::stoi(args[0]) + (std::stoi(args[1]) * this->_mapSize.x);
    std::vector<unsigned int> ressources;
    for (int i = 2; i < args.size(); i++) {
        ressources.push_back(std::stoi(args[i]));
    }
    this->_tiles.at(tileNbr)->setItems(ressources);
}

void Zappy::Core::pdiCommand(std::vector<std::string> args)
{
    SoundManager::GetInstance().playAudio("Death");
    this->_playerJustDied = true;
    if (this->_players.count(std::stoi(args[0])) == 0) {
        return;
    }
    this->_players.erase(std::stoi(args[0]));
}

void Zappy::Core::ppoCommand(std::vector<std::string> args)
{
    if (this->_players.count(std::stoi(args[0])) == 0) {
        return;
    }
    this->_players[std::stoi(args[0])].get()->setMapPosition(std::stoi(args[1]), std::stoi(args[2]));
    this->_players[std::stoi(args[0])].get()->setOrientation(std::stoi(args[3]));
}

void Zappy::Core::pinCommand(std::vector<std::string> args)
{
    if (this->_players.count(std::stoi(args[0])) == 0) {
        return;
    }
    std::vector<unsigned int> newInventory;
    for (int i = 3; i < args.size(); i++) {
        newInventory.push_back(std::stoi(args[i]));
    }
    this->_players[std::stoi(args[0])].get()->setInventory(newInventory);
}

void Zappy::Core::plvCommand(std::vector<std::string> args)
{
    if (this->_players.count(std::stoi(args[0])) == 0) {
        return;
    }
    this->_players[std::stoi(args[0])].get()->setLevel(std::stoi(args[1]));
}

void Zappy::Core::picCommand(std::vector<std::string> args)
{
    SoundManager::GetInstance().playAudio("IncantationStart");
    for (int i = 3; i < args.size(); i++) {
        this->_players[std::stoi(args[i])]->setIncantation(true);
    }
}
void Zappy::Core::pieCommand(std::vector<std::string> args)
{
    if (args[2] == "ok") {
        SoundManager::GetInstance().playAudio("IncantationEnd");
    }
    for (auto &player : this->_players) {
        player.second->setIncantation(false);
    }
}

void Zappy::Core::segCommand(std::vector<std::string> args)
{
    this->_gameEnd = true;
    this->_victoryText->setText("Team " + args[0] + " wins!");
}

void Zappy::Core::enwCommand(std::vector<std::string> args)
{
    SoundManager::GetInstance().playAudio("EggSpawn");
    this->_eggs[std::stoi(args[0])] = std::make_shared<Zappy::Egg>(args);
    if (this->_players.count(std::stoi(args[1])) == 0) {
        return;
    }
    this->_players[std::stoi(args[1])]->setFork(false);
}

void Zappy::Core::eboCommand(std::vector<std::string> args)
{
    SoundManager::GetInstance().playAudio("Spawn");
    this->_eggs.erase(std::stoi(args[0]));
}

void Zappy::Core::ediCommand(std::vector<std::string> args)
{
    SoundManager::GetInstance().playAudio("EggDeath");
    this->_eggs.erase(std::stoi(args[0]));
}

void Zappy::Core::pfkCommand(std::vector<std::string> args)
{
    SoundManager::GetInstance().playAudio("Fork");
    if (this->_players.count(std::stoi(args[0])) == 0) {
        return;
    }
    this->_players[std::stoi(args[0])]->setFork(true);
}
