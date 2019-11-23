//
// Created by maya on 11/18/19.
//
#include "../include/Session.h"
#include "../include/json.hpp"
#include "../include/Watchable.h"
#include "../include/User.h"
#include <string>
#include <fstream>
#include <sstream>

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

        for (const auto& item : j["movies"].items()) {
            vector<string> tags;
            name = item.value()["name"];
            length = item.value()["length"];
            for (const auto& tag : item.value()["tags"].items())
                tags.push_back(tag.value());
            movie = new Movie(id ,name, length, tags);
            id++;
            content.push_back(movie);
        }
        //run over the tv_series and add them to the content
        for (const auto& item : j["tv_series"].items()){
            vector<string> tags;
            name = item.value()["name"];
            length = item.value()["episode_length"];
            int NumOfSeason = 1;
            for (const auto& tag : item.value()["tags"].items())
                tags.push_back(tag.value());
            for (const auto& season : item.value()["seasons"].items()) {
                for (int currentEpisode = 1; currentEpisode<= season.value(); currentEpisode++){
                    episode = new Episode(id ,name, length , NumOfSeason , currentEpisode , tags);
                    content.push_back(episode);
                    id++;
                    episode->setNextEpisodeId(id);
                }
                NumOfSeason++;
            }
            episode->setNextEpisodeId(0);//last episode of a tv-series
        }
        activeUser = new LengthRecommenderUser("default");//create default user
    }
    //~Session();
    void Session::start()
    {
        cout << "SPLFLIX is now on!" << endl;

        cout << "Please enter action" << endl;
        getline(cin , action);
        while(action.compare("exit") != 0){
            string command = action.substr(0 , action.find(" "));
            if (command.compare("createuser") == 0){
                CreateUser* createUser = new CreateUser();
                createUser->act(*this);
                actionsLog.push_back(createUser);
            }
            else if (command.compare("changeuser") == 0){
                ChangeActiveUser* changeUser = new ChangeActiveUser();
                changeUser->act(*this);
                actionsLog.push_back(changeUser);
            }
            else if (command.compare("deleteuser") == 0){
                DeleteUser* deleteUser = new DeleteUser();
                deleteUser->act(*this);
                actionsLog.push_back(deleteUser);
            }
            else if (command.compare("dupuser") == 0){
                DuplicateUser* duplicateUser = new DuplicateUser();
                duplicateUser->act(*this);
                actionsLog.push_back(duplicateUser);
            }
            else if (command.compare("content") == 0){
                PrintContentList* printContentList = new PrintContentList();
                printContentList->act(*this);
                actionsLog.push_back(printContentList);
            }
            else if (command.compare("watch") == 0){
                Watch* watch = new Watch();
                watch->act(*this);
                actionsLog.push_back(watch);
            }
            else if (command.compare("watchhist") == 0){
                PrintWatchHistory* printWatchHistory = new PrintWatchHistory();
                printWatchHistory->act(*this);
                actionsLog.push_back(printWatchHistory);
            }
            else if (command.compare("log") == 0){
                PrintActionsLog* s = new PrintActionsLog();
                s->act(*this);
                actionsLog.push_back(s);
            }
            getline(cin , action);
        }
        //Exit session

    }

    void Session::setActiveUser(User* user){
        activeUser = user;
    }

    User* Session::getActiveUser(){
        return activeUser;
    }

    string Session::getUserAction(){
        return action;
    }

    void Session::setUserAction(string action){
        this->action = action;
    }

    vector<Watchable*> Session::getContent(){
        return content;
    }

    bool Session::contain(string name){
        if (userMap.find(name) == userMap.end())
            return false;
        return true;
    }

    User* Session::findUser(string name){
        unordered_map<string,User*>::const_iterator got = userMap.find (name);
        User* user = got->second;
        return user;
    }

    unordered_map<string,User*>* Session::getMap() {
        return &userMap;
    }

    vector<BaseAction*>* Session::getActionsLog() {
    return &actionsLog;
}




