#ifndef AANIMAL_HPP
#define AANIMAL_HPP

#include <string>

class AAnimal {
    public:
    AAnimal ();
    AAnimal (const std::string& type);
    AAnimal (const AAnimal& other);
    AAnimal& operator= (const AAnimal& other);
    virtual ~AAnimal ();
	virtual void makeSound() const = 0;
	virtual const std::string& getType() const;

    protected:
    std::string type;
};

#endif
