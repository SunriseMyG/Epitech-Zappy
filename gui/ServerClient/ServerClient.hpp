/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

#ifndef SERVER_CLIENT_H_
    #define SERVER_CLIENT_H_

    #include "../includes/Headers.hpp"

    class ServerClient
    {
        typedef struct payload_header_s {
            int size;
            int type; // TO BE CAST TO ENUM type : )
        } payload_header_t;

        public:
            ServerClient(std::string hostName, int port);
            ~ServerClient();
            void sendServer(std::string message);
            std::string getServer(bool previousWrite);

        private:
            int _socket;
            struct sockaddr_in _sockaddr;
            fd_set readFds;
            fd_set writeFds;
    };

#endif