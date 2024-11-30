/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** ErrorException
*/

#pragma once

class ErrorException : public std::exception {
    public:
        ErrorException(const std::string &message) : _message(message) {}
        ~ErrorException() = default;
        const char *what() const noexcept override { return _message.c_str(); }

    private:
        std::string _message;
};