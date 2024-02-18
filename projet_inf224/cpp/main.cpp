//
// main.cpp
//

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>

#include "DataManager.h"
#include "Film.h"
#include "Group.h"
#include "Multimedia.h"
#include "Photo.h"
#include "tcpserver.h"
#include "Video.h"

using namespace std;

const int PORT = 3331;

int main(int argc, const char* argv[]) {
    float chaptersDurations[4]{2, 3, 1, 6};

    DataManager dataManager{};

    std::shared_ptr<Group> group = dataManager.addGroup("Test");

    group->push_back(dataManager.addPhoto("TourEiffel", "../Data/TourEiffel.png"));
    group->push_back(dataManager.addPhoto("Nadal", "../Data/Nadal.png"));
    group->push_back(dataManager.addVideo("Ski", "../Data/Ski.mp4", 10));
    group->push_back(dataManager.addFilm("Film", "../Data/Ski.mp4", 10, chaptersDurations, 4));

    dataManager.print(std::cout);

    // cree le TCPServer
    auto* server = new TCPServer([&](std::string const& request, std::string& response) {
        // the request sent by the client to the server
        std::cout << "request: " << request << std::endl;

        std::stringstream ss{request};

        std::string command {};  
        ss >> command;

        // The rest is the name of the object
        std::string name {};
        std::getline(ss, name);
        name.erase(0, 1);

        // For each command, we check if the object exists and then execute the command, and return the result in the response string
        if(command == "display") {
            if(dataManager.getObject(name) != nullptr) {
                std::stringstream stream{};
                dataManager.printObject(name, stream);
                response = stream.str();
            } else {
                response = "Object not found : " + name;
            }
        } else if(command == "play") {
            if(dataManager.getObject(name) != nullptr) {
                dataManager.playObject(name);
                response = "Playing object : " + name;
            } else {
                response = "Object not found : " + name;
            }
        } else if(command == "list") {
            std::stringstream stream{};
            dataManager.listNames(stream);
            response = stream.str();
        } else {
            response = "Unknown command : " + command;
        }

        // return false would close the connection with the client
        return true;
    });

    std::cout << "Starting Server on port " << PORT << std::endl;

    int status = server->run(PORT);

    if (status < 0) {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }

    return 0;
}