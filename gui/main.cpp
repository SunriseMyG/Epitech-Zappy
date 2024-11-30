/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** main
*/

#include "includes/Headers.hpp"
#include "Core/Core.hpp"
#include "Graphics/SoundManager.hpp"

int main(int argc, char* argv[])
{
    try {
        if (argc != 5 && argc != 1) {
            throw ErrorException("Invalid arguments");
        }
        int port = 4242;
        std::string host("127.0.0.1");
        for (int i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "-p") {
                port = std::atoi(argv[i + 1]);
            }
            if (std::string(argv[i]) == "-h") {
                host = argv[i + 1];
            }
        }
        Zappy::Core core(host, port);
        core.displayLoop();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }

    return 0;
}
