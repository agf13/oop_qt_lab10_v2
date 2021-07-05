#include "dog.h"
#include <sstream>
#include <iostream>

#include "InputError.h"

Dog::Dog()
{
    this->age = -1;
    this->name = "";
    this->breed = "";
    this->photograph = "";
}

Dog::Dog(std::string name, std::string breed, int age, std::string photograph)
{
    this->name = name;
    this->age = age;
    this->breed = breed;
    this->photograph = photograph;
}

Dog::Dog(std::string text)
{
    std::stringstream is(text);

    std::string ageAsString, entireLine;
    std::getline(is, entireLine, '\n');
    if (entireLine.empty())
    {
        throw InputError();
    }

    std::stringstream lineStream(entireLine);
    std::getline(lineStream, this->name, ',');
    std::getline(lineStream, this->breed, ',');
    std::getline(lineStream, ageAsString, ',');
    std::getline(lineStream, this->photograph);


    this->age = std::stoi(ageAsString);
}

Dog::~Dog()
{

}

bool Dog::setName(std::string name)
{
    bool validationResult = this->validateName(name);
    if (validationResult == false)
        return validationResult;
    this->name = name;
    return validationResult;
}

bool Dog::setBreed(std::string breed)
{
    bool validationResult = this->validateBreed(breed);
    if (validationResult == false)
        return validationResult;
    this->breed = breed;
    return validationResult;
}

bool Dog::setAge(int age)
{
    bool validationResult = this->validateAge(age);
    if (validationResult == false)
        return validationResult;
    this->age = age;
    return validationResult;
}

bool Dog::setPhotograph(std::string photo)
{
    bool validationResult = this->validatePhotograph(photo);
    if (validationResult == false)
        return validationResult;
    this->photograph = photo;
    return validationResult;
}

std::string Dog::getName()
{
    return this->name;
}

std::string Dog::getBreed()
{
    return this->breed;
}

int Dog::getAge()
{
    return this->age;
}

std::string Dog::getPhotograph()
{
    return this->photograph;
}



bool Dog::validateName(std::string name)
{
    if (name.size() < 1)
        return false;
    return true;
}

bool Dog::validateBreed(std::string breed)
{
    if (breed.size() < 1)
        return false;
    return true;
}

bool Dog::validateAge(int age)
{
    if (age < 0)
        return false;
    return true;
}

bool Dog::validatePhotograph(std::string photograph)
{
    if (photograph.size() < 1)
        return false;
    return true;
}

bool Dog::validateDog()
{
    return (this->validateAge(this->age) && this->validateBreed(this->breed) && this->validateName(this->name) && this->validatePhotograph(this->photograph));
}

bool Dog::validateAll(std::string name, std::string breed, int age, std::string photograph)
{
    return (Dog::validateAge(age) && Dog::validateBreed(breed) && Dog::validateName(name) && Dog::validatePhotograph(photograph));
}

bool Dog::checkId(std::string id)
{
    return this->name == id;
}

std::string Dog::toString()
{
    std::string output = "";
    output += "name: " + this->name + ",";
    output += "breed: " + this->breed + ",";
    output += "age: " + std::to_string(this->age) + ",";
    output += "photograph: " + this->photograph;
    return output;
}

std::string Dog::toHtmlTableLine()
{
    std::string htmlLine = "<tr>";
    htmlLine += "<td align=center>" + this->name + "</td>";
    htmlLine += "<td align=center>" + this->breed + "</td>";
    htmlLine += "<td align=center>" + std::to_string(this->age) + "</td>";
    htmlLine += "<td align=center>" + this->photograph + "</td>";
    htmlLine += "</td>";

    return htmlLine;
}

std::string Dog::getHtmlTableHeaders()
{
    std::string headers = "<th align=center> name </th>";
    headers += "<th align=center> breed </th>";
    headers += "<th align=center> age </th>";
    headers += "<th align=center> photograph link </th>";

    return headers;
}

std::string Dog::toCsvLine()
{
    std::string csvLine = "";
    csvLine += this->name + ",";
    csvLine += this->breed + ",";
    csvLine += std::to_string(this->age) + ",";
    csvLine += this->photograph;

    return csvLine;
}



Dog& Dog::operator=(Dog& other)
{
    this->name = other.name;
    this->breed = other.breed;
    this->age = other.age;
    this->photograph = other.photograph;
    return *this;
}

bool Dog::isNumber(std::string token)
{
    int lenght = token.size();
    for (int i = 0; i < lenght; i++)
    {
        if (!isdigit(token[i]) && !(i == 0 && token[i] == '-'))
            return false;
    }
    return true;
}


bool operator==(const Dog& leftDog, const Dog& rightDog)
{
    return (leftDog.name == rightDog.name);
}

std::istream& operator>>(std::istream& is, Dog& dog)
{
    std::string ageAsString, entireLine;
    std::getline(is, entireLine, '\n');
    if (entireLine.empty())
    {
        throw InputError();
    }

    std::stringstream lineStream(entireLine);
    std::getline(lineStream, dog.name, ',');
    std::getline(lineStream, dog.breed, ',');
    std::getline(lineStream, ageAsString, ',');
    std::getline(lineStream, dog.photograph);


    dog.age = std::stoi(ageAsString);


    return is;
}

std::ostream& operator<<(std::ostream& os, Dog& dog)
{
    std::string coma = ",";

    //char age_asChars[10];
    //_itoa_s(dog.age, age_asChars, 10);
    //age_asChars[9] = '\0';
    //std::string age_asString(age_asChars);

    os << dog.name << coma << dog.breed << coma << std::to_string(dog.age) << coma << dog.photograph;

    return os;
}
