#include "service.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

Service::Service(Repository<Dog>* repo)
{
    this->repository = repo;
}

Service::~Service()
{
    delete this->repository;
}

int Service::getLength()
{
    return this->repository->getLength();
}

int Service::getCapacity()
{
    return this->repository->getCapacity();
}

bool Service::add(Dog* dog)
{
    //validate the dog
    if (!dog->validateDog())
        return false;
    try
    {
        ValidatorDog::validate(dog);
    }
    catch (ValidatorDog e)
    {
        delete dog;
        throw ValidatorDog();
    }

    //check for duplicates
    int indexDog = this->repository->getIndex(dog);
    if (indexDog != -1)
    {
        throw DuplicateError();
    }

    //add the dog
    return this->repository->add(dog); //repository->add always returns true
}

bool Service::update(Dog* dog)
{
    try
    {
        ValidatorDog::validate(dog);
    }
    catch (ValidatorError e)
    {
        delete dog;
        throw ValidatorError();
    }
    //dog validation is not necessary
    return this->repository->update(dog);
}

bool Service::remove(int index)
{
    return this->repository->remove(index);
}

bool Service::remove(std::string name)
{
    int index = this->getDogIndex(name);
    if (index == -1)
        throw UnexistingElement();
    else
        return this->repository->remove(index);
}

Dog* Service::get(int index)
{
    return this->repository->get(index);
}

std::vector<Dog*> Service::getAll()
{
    return this->repository->getAll();
}

std::vector<Dog*> Service::filter(int age, std::string breed)
{
    std::vector<Dog*> elements = this->repository->getAll();
    std::vector<Dog*> filtered(elements.size());

    util_initVectorOfPointers_withNULL(filtered, elements.size());

    std::copy_if(elements.begin(), elements.end(), filtered.begin(), [age, breed](Dog* current) {
        if (current->getAge() > age && age != 0) //if age is greater, do not store this dog
            return false;
        if (breed.empty()) //if the breed is empty, it means we don't care about it. Store this dog.
            return true;
        if (current->getBreed() != breed) //if dog's breed is different, do not store this dog
            return false;
        return true; //if this line is reached, store this dog
        });
    filtered.shrink_to_fit();
    return filtered;
}

Dog* Service::getDog(std::string name)
{
    std::vector<Dog*> dogList = this->repository->getAll();

    for (Dog* current : dogList)
    {
        if (current->getName() == name)
            return current;
    }
    return NULL;
}

int Service::getDogIndex(std::string name)
{
    int i = 0;
    std::vector<Dog*> dogList = this->repository->getAll();
    for (Dog* current : dogList)
    {
        if (current->getName() == name)
            return i;
        i++;
    }
    return -1;
}

void Service::initRepositoryFromFile(std::string fileName)
{
    this->repository->initFromFile();
}

void Service::util_initVectorOfPointers_withNULL(std::vector<Dog*> vector, int size)
{
    for (int i = 0; i < size; i++)
    {
        vector[i] = NULL;
    }
}
