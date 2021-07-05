#ifndef SERVICE_H
#define SERVICE_H

#pragma once



#include "dog.h"
#include "repository.h"
#include "validatordog.h"

#include "InputError.h"
#include "ValidatorError.h"
#include "DuplicateError.h"



class Service
{
public:

    Service(Repository<Dog>* repo);
    ~Service();

    int getLength();
    int getCapacity();

    bool add(Dog* dog);
    bool update(Dog* dog);
    bool remove(int index);
    bool remove(std::string name);
    Dog* get(int index);
    std::vector<Dog*> getAll();

    /*
    *	def: Filter the dogs with the given age and breed and returns a std::vector of pointers to those dogs.
    */
    std::vector<Dog*> filter(int age = 0, std::string breed = "");

    /*
    *	def: returns the dog with the given name or NULL no dog found.
    */
    Dog* getDog(std::string name);

    /*
    *	def: returns the index of the dog with the given name, or -1 id none found
    */
    int getDogIndex(std::string name);


    /*
    *	def: init the repository form a file
    */
    void initRepositoryFromFile(std::string fileName = "dogs.txt");


private:
    //DynamicVector<Dog> repository;
    Repository<Dog>* repository;

    void util_initVectorOfPointers_withNULL(std::vector<Dog*> vector, int size);
};



#endif // SERVICE_H
