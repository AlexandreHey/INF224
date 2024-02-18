#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <memory>
#include <string>
#include <iostream>

class Multimedia {
private: 
	// Attributes
	std::string objectName{};
	std::string pathName{};

public: 
	// Constructors
	Multimedia();
	Multimedia(std::string objectName, std::string pathName);

	// Destructor
	virtual ~Multimedia();

 	// Getters
	std::string getObjectName() const;
	std::string getPathName() const;

	// Setters
	void setObjectName(std::string objectName);
	void setPathName(std::string pathName);

	virtual void print(std::ostream& os) const;

	virtual const void play() = 0;

	virtual void serialize(std::ostream& os) const;

	virtual void deserialize(std::istream& is);
};

typedef std::shared_ptr<Multimedia> DataPtr;

#endif // MULTIMEDIA_H