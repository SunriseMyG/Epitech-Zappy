/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ServerClient
*/

#include "ServerClient.hpp"

ServerClient::ServerClient(std::string hostName, int port)
{
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socket == -1) {
        throw ErrorException("Socket failed");
    }
    this->_sockaddr.sin_family = AF_INET;
    this->_sockaddr.sin_port = htons(port);
    // this->_sockaddr.sin_addr.s_addr = inet_addr(hostName.c_str());
    if (inet_pton(AF_INET, hostName.c_str(), &this->_sockaddr.sin_addr) == -1) {
        throw ErrorException("Inet failed");
    }
    if (connect(this->_socket, (struct sockaddr *)&this->_sockaddr, sizeof(this->_sockaddr)) == -1) {
        throw ErrorException("Connection failed");
    }
    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
    FD_SET(this->_socket, &readFds);
    FD_SET(this->_socket, &writeFds);
    std::cout << "Client Setup!" << std::endl;
}

ServerClient::~ServerClient()
{
    close(this->_socket);
}

void ServerClient::sendServer(std::string message)
{
    message += "\n";
    write(this->_socket, message.c_str(), message.length());
}

std::string ServerClient::getServer(bool previousWrite)
{
    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);
    FD_SET(this->_socket, &readFds);
    FD_SET(this->_socket, &writeFds);
    std::vector<char> buffer(16386);
    std::string message;
    struct timeval tv;
    tv.tv_sec = 0.1f;
    tv.tv_usec = 0;
    int res;
    if(previousWrite) {
        res = select(FD_SETSIZE, &readFds, &writeFds, NULL, &tv);
    } else {
        res = select(FD_SETSIZE, &readFds, NULL, NULL, &tv);
    }
    if (res == 0) {
        message.clear();
        return (message);
    }
    read(this->_socket, &(buffer[0]), 16385);
    message.assign(&(buffer[0]), buffer.size());
    buffer.clear();
    return (message);
}