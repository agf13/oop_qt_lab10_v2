#include "validatordog.h"

void ValidatorDog::validate(std::string name, std::string breed, int age, std::string photograph)
{
    if (name.empty() || breed.empty() || age < 0 || photograph.empty())
    {
        throw ValidatorError();
    }
}

void ValidatorDog::validate(std::string name, std::string breed, std::string age, std::string photograph)
{
    if (name.empty() || breed.empty() || photograph.empty())
        throw ValidatorError();
    try
    {
        int age_int = std::stoi(age);
    }
    catch (std::invalid_argument e)
    {
        throw ValidatorError();
    }
}

void ValidatorDog::validate(Dog dog)
{
    validate(dog.getName(), dog.getBreed(), dog.getAge(), dog.getPhotograph());
}
void ValidatorDog::validate(Dog* dog)
{
    validate(*dog);
}
