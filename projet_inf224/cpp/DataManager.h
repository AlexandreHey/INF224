#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <map>
#include <string>
#include <memory>

#include "Film.h"
#include "Group.h"
#include "Multimedia.h"
#include "Photo.h"
#include "Video.h"

typedef std::shared_ptr<Film> FilmPtr;
typedef std::shared_ptr<Group> GroupPtr;
typedef std::shared_ptr<Multimedia> MultimediaPtr;
typedef std::shared_ptr<Photo> PhotoPtr;
typedef std::shared_ptr<Video> VideoPtr;

typedef std::map<std::string, MultimediaPtr> MultimediaMap;
typedef std::map<std::string, GroupPtr> GroupMap;

class DataManager {
private:
    // Attributes
    MultimediaMap multimediaMap {};
    GroupMap groupMap {};

public:
    PhotoPtr addPhoto(std::string objectName, std::string pathName, int latitude = 0, int longitude = 0) {
        if(getObject(objectName)) {
            std::cerr << "Object named: " << objectName << " already exists\n";
            return nullptr;
        }
        PhotoPtr object {new Photo(objectName, pathName, latitude, longitude) };
        multimediaMap[objectName] = object;
        return object;
    }
    VideoPtr addVideo(std::string objectName, std::string pathName, float duration) {
        if(getObject(objectName)) {
            std::cerr << "Object named: " << objectName << " already exists\n";
            return nullptr;
        }
        VideoPtr object = std::make_shared<Video>(objectName, pathName, duration);
        multimediaMap[objectName] = object;
        return object;
    }
    FilmPtr addFilm(std::string objectName, std::string pathName, float duration, float* chaptersDurations, int numChapters) {
        if(getObject(objectName)) {
            std::cerr << "Object named: " << objectName << " already exists\n";
            return nullptr;
        }
        FilmPtr object = std::make_shared<Film>(objectName, pathName, duration, chaptersDurations, numChapters);
        multimediaMap[objectName] = object;
        return object;
    }
    GroupPtr addGroup(std::string groupName) {
        if(getObject(groupName)) {
            std::cerr << "Object named: " << groupName << " already exists\n";
            return nullptr;
        }
        GroupPtr object = std::make_shared<Group>(groupName);
        groupMap[groupName] = object;
        return object;
    }
    MultimediaPtr addObject(MultimediaPtr object) {
        if(getObject(object->getObjectName())) {
            std::cerr << "Object named: " << object->getObjectName() << " already exists\n";
            return nullptr;
        }
        multimediaMap[object->getObjectName()] = object;
        return object;
    }

    MultimediaPtr getObject(std::string objectName) {
        auto it = multimediaMap.find(objectName);
        if (it != multimediaMap.end()) return it->second;
        else return nullptr;
    }

    void printObject(std::string objectName, std::ostream& os) {
        auto itObject = multimediaMap.find(objectName);
        auto itGroup = groupMap.find(objectName);
        if (itObject != multimediaMap.end()) itObject->second->print(os);
        else if (itGroup != groupMap.end()) itGroup->second->print(os);
        else std::cerr << "Object named: " << objectName << " does not exist\n";
    }

    void playObject(std::string objectName) {
        auto it = multimediaMap.find(objectName);
        if (it != multimediaMap.end()) it->second->play();
        else std::cerr << "Object named: " << objectName << " does not exist\n";
    }

    void deleteObject(std::string objectName) {
        auto it = multimediaMap.find(objectName);
        if (it != multimediaMap.end()) multimediaMap.erase(it);
        else std::cerr << "Object named: " << objectName << " does not exist\n";
    }

    void print(std::ostream& os) {
        os << "Objects: ";
        for (auto it = multimediaMap.begin(); it != multimediaMap.end(); it++) {
            it->second->print(os);
            os << ", ";
        }
        os << ";";
        os << "Groups: ";
        for (auto it = groupMap.begin(); it != groupMap.end(); it++) {
            it->second->print(os);
            os << ", ";
        }
    }

    void serialize(std::ostream& os) {
        os << multimediaMap.size() << " ";
        for (auto it = multimediaMap.begin(); it != multimediaMap.end(); it++) {
            it->second->serialize(os);
        }
    }

    void deserialize(std::istream& is) {
        int nObjects;
        is >> nObjects;
        for (int i = 0; i < nObjects; i++) {
            std::string objectType;
            is >> objectType;

            MultimediaPtr object;
            if (objectType == "Photo") {
                object = std::make_shared<Photo>("", "", 0, 0);
            } else if (objectType == "Video") {
                object = std::make_shared<Video>("", "", 0);
            } else if (objectType == "Film") {
                object = std::make_shared<Film>("", "", 0, nullptr, 0);
            } else {
                std::cerr << "Unknown object type: " << objectType << "\n";
                return;
            }

            object->deserialize(is);
            addObject(object);
        }
    }

    void listNames(std::ostream& os) {
        os << "Objects: ";
        for (auto it = multimediaMap.begin(); it != multimediaMap.end(); it++) {
            os << it->first << ", ";
        }
        os << "Groups: ";
        for (auto it = groupMap.begin(); it != groupMap.end(); it++) {
            os << it->first << ", ";
        }
    }
};

#endif // DATA_MANAGER_H