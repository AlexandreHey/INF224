#include "Multimedia.h"

// Constructors
Multimedia::Multimedia() {}
Multimedia::Multimedia(std::string objectName, std::string pathName) {
    this->objectName = objectName;
    this->pathName = pathName;
}

// Destructor
Multimedia::~Multimedia() {}

// Getters
std::string Multimedia::getObjectName() const { 
    return objectName; 
};
std::string Multimedia::getPathName() const { 
    return pathName; 
};

// Setters
void Multimedia::setObjectName(std::string objectName) { 
    this->objectName = objectName; 
}
void Multimedia::setPathName(std::string pathName) { 
    this->pathName = pathName; 
};

void Multimedia::print(std::ostream& os) const {
    os << "Multimedia object (Name = \"" << objectName << "\", pathname = \"" << pathName << "\");";
};

void Multimedia::serialize(std::ostream& os) const {
    os << objectName << ";" << pathName << ";";
};

void Multimedia::deserialize(std::istream& is) {
    std::getline(is, objectName, ';');
    std::getline(is, pathName, ';');
};
