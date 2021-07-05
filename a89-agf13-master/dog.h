#ifndef DOG_H
#define DOG_H
#pragma once

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <string>
#include <sstream>

class Dog
{
public:

    Dog();
    Dog(std::string name, std::string breed, int age, std::string photograph);
    Dog(std::string text);
    ~Dog();

    bool setName(std::string name);
    bool setBreed(std::string breed);
    bool setAge(int age);
    bool setPhotograph(std::string photo);

    std::string getName();
    std::string getBreed();
    int getAge();
    std::string getPhotograph();

    static bool validateName(std::string name);
    static bool validateBreed(std::string breed);
    static bool validateAge(int age);
    static bool validatePhotograph(std::string photograph);
    static bool validateAll(std::string name, std::string breed, int age, std::string photograph);
    bool validateDog();

    bool checkId(std::string id);

    std::string toString();
    std::string toHtmlTableLine();
    static std::string getHtmlTableHeaders();
    std::string toCsvLine();

    friend bool operator== (const Dog& leftDog, const Dog& rightDog);
    Dog& operator= (Dog& other);
    friend std::istream& operator>> (std::istream& is, Dog& dog);
    friend std::ostream& operator<< (std::ostream& os, Dog& dog);

private:
    std::string name;
    std::string breed;
    int age;
    std::string photograph;

    bool isNumber(std::string token);
};


#endif // DOG_H
