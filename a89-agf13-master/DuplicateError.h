#ifndef DUPLICATEERROR_H
#define DUPLICATEERROR_H
#pragma once

#include <exception>

struct DuplicateError : public std::exception
{
        const char* what() const throw()
        {
                return "Duplicate found";
        }
};

#endif // DUPLICATEERROR_H
