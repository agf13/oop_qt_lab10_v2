#ifndef VALIDATORDOG_H
#define VALIDATORDOG_H

#pragma once

#include <string>

#include "dog.h"
#include "InputError.h"
#include "ValidatorError.h"
//#include "Validator.h"


class ValidatorDog
{
public:
    static void validate(std::string name, std::string breed, int age, std::string photograph);
    static void validate(std::string name, std::string breed, std::string age, std::string photograph);
    static void validate(Dog dog);
    static void validate(Dog* dog);
};



#endif // VALIDATORDOG_H
