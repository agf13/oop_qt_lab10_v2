#ifndef REPOSITORY_H
#define REPOSITORY_H

#pragma once

#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include "InputError.h"
#include "UnexistingElement.h"


template <class T>
class Repository
{
public:
    Repository(std::string fileName = "dogs.txt");
    ~Repository();

    int getLength();
    int getCapacity();

    bool add(T* element);
    bool update(T* updateElement);
    bool remove(T* removeElement);
    bool remove(int index);
    T* get(int index);


    int getIndex(T* element);
    void initFromFile();
    void updateFile();

    std::vector<T*> getAll();

    void readFromFile(std::string fileName = "programmers.txt");

private:
    std::vector<T*> elementList;
    std::string fileName;

};

template<class T>
inline Repository<T>::Repository(std::string fileName)
{
    this->fileName = fileName;
}

template<class T>
inline Repository<T>::~Repository()
{
    for (T* current : this->elementList)
    {
        delete current;
    }
}

template<class T>
inline int Repository<T>::getLength()
{
    return this->elementList.size();
}

template<class T>
inline bool Repository<T>::add(T* element)
{
    this->elementList.push_back(element);
    updateFile();
    return true;
}

template<class T>
inline bool Repository<T>::update(T* update)
{
    int index = getIndex(update);
    if (index == -1)
    {
        throw UnexistingElement();
    }
    delete this->elementList[index];
    this->elementList[index] = update;
    updateFile();
    return true;
}

template<class T>
inline bool Repository<T>::remove(T* removeElement)
{
    int index = getIndex(removeElement);
    if (index == -1)
    {
        throw UnexistingElement();
    }
    delete this->elementList[index];
    this->elementList[index] = this->elementList[elementList.size() - 1];
    this->elementList.pop_back();
    updateFile();
    return true;
}

template<class T>
inline bool Repository<T>::remove(int index)
{
    if (index < 0 || index >= this->elementList.size())
    {
        throw UnexistingElement();
    }
    delete this->elementList[index];
    this->elementList[index] = this->elementList[elementList.size() - 1];
    this->elementList.pop_back();
    updateFile();
    return true;
}

template<class T>
inline T* Repository<T>::get(int index)
{
    if (index >= (int)this->elementList.size() || index < 0)
        return NULL;
    return this->elementList[index];
}


template<class T>
inline int Repository<T>::getIndex(T* element)
{
    int index = 0;
    for (T* current : this->elementList)
    {
        if (*current == *element)
            return index;
        index++;
    }
    return -1;
}

template<class T>
inline int Repository<T>::getCapacity()
{
    return -1;
}

template<class T>
inline std::vector<T*> Repository<T>::getAll()
{
    return (this->elementList);
}

template<class T>
inline void Repository<T>::initFromFile()
{
    std::ifstream in{ this->fileName };
    T current;
    while (in.good())
    {
        try
        {
            in >> current;
            T* newElement = new T(current);
            this->elementList.push_back(newElement);
        }
        catch (InputError e)
        {
            continue;
        }
        catch (std::invalid_argument e)
        {
            std::cout << "\t*Invalid number found in file\n";
        }
    }
}

template<class T>
inline void Repository<T>::updateFile()
{
    std::ofstream out(this->fileName);
    for (T* element : this->elementList)
    {
        out << *element << "\n";
    }
}


#endif // REPOSITORY_H
