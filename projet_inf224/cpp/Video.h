#ifndef VIDEO_H
#define VIDEO_H

#include "Multimedia.h"

class Video : public Multimedia {
private:
	// Attribute
	float duration{};

public:
	// Constructors
	Video() : Multimedia() {}
	Video(std::string objectName, std::string pathName) : Multimedia(objectName, pathName) {}
	Video(std::string objectName, std::string pathName, float duration) : Multimedia(objectName, pathName) { this->duration = duration; };

	// Getter and setter
	float getDuration() const { return duration; }
	void setDuration(float duration) { this->duration = duration; }

	void print(std::ostream& os) const override {
		os << "Video (Name = \"" << getObjectName() << "\", pathname = \"" << getPathName() << "\", duration=" << getDuration() << ")";
	};
	const void play() override {
		std::string command = "mpv \"" + getPathName() + "\" &";
		system(command.c_str());
	}

	void serialize(std::ostream& os) const override {
		os << "Video ";
		Multimedia::serialize(os);
		os << duration << ";";
	}

	void serializeWithoutType(std::ostream& os) const {
		Multimedia::serialize(os);
		os << duration << ";";
	}

	void deserialize(std::istream& is) override {
		Multimedia::deserialize(is);
		std::string durationStr;
		std::getline(is, durationStr, ';');
		duration = std::stof(durationStr);
	}
};

#endif // VIDEO_H