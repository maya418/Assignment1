//
// Created by maya on 11/18/19.
//
#include "../include/Session.h"
#include "../include/json.hpp"
#include "../include/Watchable.h"
#include "../include/User.h"
#include <fstream>

using namespace std;

    Session::Session(const string &configFilePath) {
        using json = nlohmann::json;
        json j;
        const string file = configFilePath;
        ifstream reader(file);
        reader >> j;
        reader.close();

        Movie* movie;
        Episode* episode;
        string name;
        int length;
        long id = 1;
        vector<string> tags;

        for (const auto& item : j["movies"].items()) {
            name = item.value()["name"];
            length = item.value()["length"];
            id++;
            for (const auto& tag : item.value()["tags"].items())
                tags.push_back(tag.value());
            movie = new Movie(id ,name, length, tags);
            content.push_back(movie);
        }
        id = 1;
        for (const auto& item : j["tv_series"].items()){
            name = item.value()["name"];
            length = item.value()["episode_length"];
            id++;
            //episode = new Episode(id , length ,id ,name, length, tags);
            //content.push_back(episode);
        }
    }
    //~Session();
    void Session::start()
    {
        cout << "SPLFLIX is now on!" << endl;
        activeUser = new LengthRecommenderUser("default");//create default user
        cout << "Please enter action" << endl;
        string action;
        cin >> action;
        while(action.compare("exit") != 0){
            string command = (action.substr(0, action.find(" ")));
            if (command.compare("createuser") == 0){
                CreateUser* createUser;
                createUser->act(*this);
                actionsLog.push_back(createUser);
            }
            else if (command.compare("changeuser") == 0){
                cout << "change user" << endl;
            }
            else if (command.compare("deleteuser") == 0){
                cout << "delete user" << endl;
            }
            else if (command.compare("createuser") == 0){
                cout << "creating a user" << endl;
            }
            else if (command.compare("dupuser") == 0){
                cout << "duplicate user" << endl;
            }
            else if (command.compare("content") == 0){
                cout << "print content" << endl;
            }
            cin >> action;
        }
        //Exit session
    }

    void Session::setActiveUser(User user){
        activeUser = &user;
    }

    User* Session::getActiveUser(){
        return activeUser;
    }






