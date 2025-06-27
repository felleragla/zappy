/*
** EPITECH PROJECT, 2024
** G-CNA-400-COT-4-1-gameofstones-andy.sagbo
** File description:
** Error.hpp
*/

#pragma once
#ifndef _ERROR_HPP_
#define _ERROR_HPP_
#include <exception>
#include <stdexcept>

class Error : public std::exception
{
private:
    std::string message;
public:
    Error(std::string const& error = "Error") {
        message = error;
    }


    virtual const char *what() const throw() {
        return message.c_str();
    }
    
    virtual ~Error() throw() {};
};

#endif