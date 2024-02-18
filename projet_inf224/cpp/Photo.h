#ifndef PHOTO_H
#define PHOTO_H

#include "Multimedia.h"

class Photo : public Multimedia {
private:
	// Attributes
	int latitude{};
	int longitude{};

public:
	// Constructors
	Photo() : Multimedia() {}
	Photo(std::string objectName, std::string pathName) : Multimedia(objectName, pathName) { }
	Photo(std::string objectName, std::string pathName, int latitude, int longitude) : Multimedia(objectName, pathName) {
		this->latitude = latitude;
		this->longitude = longitude;
	}
	
	// Getters
	int getLatitude() const { return latitude; }
	int getLongitude() const { return longitude; }

	// Setters
	void setLatitude(int latitude) { this->latitude = latitude; };
	void setLongitude(int longitude) { this->longitude = longitude; }

	void print(std::ostream &os) const override {
		os << "Photo (Name = \"" << getObjectName() << "\", pathname = \"" << getPathName() << "\", latitude=" << getLatitude() << ", longitude=" << getLongitude() <<")";
	};

	const void play() override {
		std::string command = "imagej \"" + getPathName() + "\" &";
		system(command.c_str());
	}

	friend class DataManager;

	void serialize(std::ostream& os) const override {
		os << "Photo ";
		Multimedia::serialize(os);
		os << latitude << ";" << longitude << ";";
	}

	void deserialize(std::istream& is) override {
		Multimedia::deserialize(is);
		std::string latitudeStr, longitudeStr;
		std::getline(is, latitudeStr, ';');
		std::getline(is, longitudeStr, ';');
		latitude = std::stoi(latitudeStr);
		longitude = std::stoi(longitudeStr);
	}
};

#endif // PHOTO_H