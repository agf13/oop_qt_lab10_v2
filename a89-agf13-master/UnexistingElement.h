#ifndef UNEXISTINGELEMENT_H
#define UNEXISTINGELEMENT_H
#pragma once

#include "exception"

struct UnexistingElement : std::exception
{
    const char* what() const throw()
    {
        return "Unexisting element";
    }
};

#endif // UNEXISTINGELEMENT_H
