#ifndef VALIDATORERROR_H
#define VALIDATORERROR_H
#pragma once

#include <exception>

struct ValidatorError : public std::exception
{
    const char* what() const throw()
    {
        return "Invalid arguments";
    }
};

#endif // VALIDATORERROR_H
