#ifndef INPUTERROR_H
#define INPUTERROR_H

#include <iostream>
#include <exception>

struct InputError : public std::exception
{
    const char* what() const throw()
    {
        return "Invalid input";
    }
};

#endif // INPUTERROR_H
