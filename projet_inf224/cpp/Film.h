#ifndef FILM_H
#define FILM_H

#include "Video.h"

class Film : public Video {
private:
	// Attributes
	float* chaptersDurations {};
	int numChapters{};

public: 
	// Constructors
	Film() : Video() {}
	Film(std::string objectName, std::string pathName) : Video(objectName, pathName) {}
	Film(std::string objectName, std::string pathName, float duration) : Video(objectName, pathName, duration) {}
	Film(std::string objectName, std::string pathName, float duration, float* chaptersDurations, int numChapters)
		: Video(objectName, pathName, duration) {
			setChaptersDurations(chaptersDurations, numChapters);
	}

	// Copy constructor
	Film(const Film &from) : Film(from.getPathName(), from.getObjectName(), from.getDuration(), from.getChaptersDurations(), from.getNumChapters()) { }
	Film& operator=(const Film& from) {
    this->setPathName(from.getPathName());
    this->setObjectName(from.getObjectName());
    this->setDuration(from.getDuration());
    this->setChaptersDurations(from.getChaptersDurations(), from.getNumChapters());

    return *this;
}


	// Destructor
	~Film() {
		if (chaptersDurations != nullptr)
			delete[] this->chaptersDurations;
	}

	// Getters
	float* const getChaptersDurations() const { return chaptersDurations; }
	int getNumChapters() const { return numChapters; }

	// Setters
	void setChaptersDurations(float* chaptersDurations, int numChapters) {
		if (chaptersDurations != nullptr) delete[] this->chaptersDurations;
		this->chaptersDurations = new float[numChapters]();
		this->numChapters = numChapters;
		if (this->chaptersDurations && chaptersDurations) {
			for (int i = 0; i < numChapters; i++) {
				this->chaptersDurations[i] = chaptersDurations[i];
			}
		} else {
			if (chaptersDurations != nullptr) delete[] this->chaptersDurations;
			this->numChapters = 0;
		}
	}
	void setNumChapters(int numChapters) { this->numChapters = numChapters; }

	void print(std::ostream& os) const override {
		os << "Film (Name = \"" << getObjectName() << "\", pathname = \"" << getPathName() << "\", duration=" << getDuration() << ",";
		os << "Chapters durations : [";
		for (int i = 0; i < numChapters; i++) {
			os << " " << chaptersDurations[i] << "seconds ,";
		}
		os << "])";
	}

	virtual void serialize(std::ostream& os) const override {
		os << "Film ";
		Video::serializeWithoutType(os);
		os << numChapters << ";";
		for (int i = 0; i < numChapters; i++) {
			os << chaptersDurations[i] << ";";
		}
	}

	virtual void deserialize(std::istream& is) override {
		Video::deserialize(is);
		std::string numChaptersStr;
		std::getline(is, numChaptersStr, ';');
		numChapters = std::stoi(numChaptersStr);
		chaptersDurations = new float[numChapters]();
		for (int i = 0; i < numChapters; i++) {
			std::string chaptersDurationsStr;
			std::getline(is, chaptersDurationsStr, ';');
			chaptersDurations[i] = std::stof(chaptersDurationsStr);
		}
	}
};

#endif // FILM_H