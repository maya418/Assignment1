//
// Created by maya on 11/18/19.
//
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"
#include <map>

using namespace std;

//constructor
User::User(const std::string& name):name(name) {

}

string User::getAlgorithm(){

}

//copy constructor
User::User(const User* other , const std::string &name):name(name){
    for (int i=0; i<other->get_history().size(); i++)
        history.push_back(other->get_history()[i]);
}

const User& User::operator=(const User& other){
    if(this != &other) {
        for (int i=0; i<other.get_history().size(); i++)
            history.push_back(other.get_history()[i]);
    }
    return *this;
}

Watchable* User::getRecommendation(Session& s){
    return nullptr;
}

string User::getName()const{
    return name;
}

vector<Watchable*> User::get_history()const{
    return history;
}

void User::set_history(Watchable* watch){
    history.push_back(watch);
}

//constructor
LengthRecommenderUser::LengthRecommenderUser(const string& name) : User(name) {
    algorithm = "len";
}

LengthRecommenderUser::LengthRecommenderUser(User* user , const string& name) : User(user , name) {

}

string LengthRecommenderUser::getAlgorithm(){
    return algorithm;
}

//find the next recommended content to watched based on Length Algorithm
Watchable* LengthRecommenderUser::getRecommendation(Session& s){
    int sum = 0;
    for (int i = 0; i < history.size(); i++)//calculate the average length of previous content user had watched
        sum += history[i]->getLength();
    int averageLength = sum / history.size();
    int bestLength = 0;
    int bestIndex = -1;
    for (int i = 0; i < s.getContent().size(); i++)//find the content with the closest length to this average
        if (!hasWatched(s.getContent()[i]))/*if user hasn't watched this content yes*/ {
            if (abs(s.getContent()[i]->getLength() - averageLength) < abs(bestLength - averageLength)) {
                bestLength = s.getContent()[i]->getLength();
                bestIndex = i;
            }
        }
    if (bestIndex != -1)
        return (s.getContent()[bestIndex]);
    return nullptr;
}

RerunRecommenderUser::RerunRecommenderUser(const std::string& name): User(name){
    algorithm = "rer";
    lastRecommendedId = -1;
}


RerunRecommenderUser::RerunRecommenderUser(User* user , const string& name) : User(user , name) {

}

string RerunRecommenderUser::getAlgorithm(){
    return algorithm;
}


//find the next recommended content to watched based on Rerun Algorithm
Watchable* RerunRecommenderUser::getRecommendation(Session& s){
    if (lastRecommendedId == -1)/*first content user have watched*/ {
        lastRecommendedId = 0;
        return nullptr;
    }
    Watchable* next = history[lastRecommendedId];
    lastRecommendedId = (lastRecommendedId + 1)%history.size();
    return next;
}

//constructor
GenreRecommenderUser::GenreRecommenderUser(const std::string &name): User(name){
    algorithm = "gen";
}

GenreRecommenderUser::GenreRecommenderUser(User* user , const string& name) : User(user , name) {

}

string GenreRecommenderUser::getAlgorithm(){
    return algorithm;
}

Watchable* GenreRecommenderUser::getRecommendation(Session& s){
    if (history.size() != 0) {
        map<string, int> tagsCount;
        string tag;
        for (int i = 0; i < history.size(); i++) {//sum up the appearance of each tag
            for (int j = 0; j < history[i]->getTags().size(); j++) {
                tag = history[i]->getTags()[j];
                if (tagsCount.find(tag) == tagsCount.end())//tag does not exist already
                    tagsCount.insert({tag, 1});
                else {
                    tagsCount.find(tag)->second++;
                }
            }
        }

        string bestTag = getBestTag(tagsCount);
        tagsCount.erase(bestTag);

        while (bestTag != "") {
            for (int i = 0; i < s.getContent().size(); i++) {
                if (!hasWatched(s.getContent()[i]))/*if user hasn't watched this content yes*/ {
                    for (int j = 0; j < s.getContent()[i]->getTags().size(); j++)
                        if (s.getContent()[i]->getTags()[j] == bestTag)
                            return s.getContent()[i];
                }
            }
            bestTag = getBestTag(tagsCount);
            tagsCount.erase(bestTag);
        }
        //tagsCount.clear();
    }

    return nullptr;
}

string GenreRecommenderUser::getBestTag(map<string , int> tagsCount){
    string mostUsedTag = "";
    int usesOfBestTag = 0;
    for(auto it=tagsCount.begin();it!=tagsCount.end();it++) {
        if(it->second > usesOfBestTag){
            usesOfBestTag = it->second;
            mostUsedTag = it->first;
        }
    }
    return mostUsedTag;
}

//this function return true if the user already watched a show or false if he hasn't.
bool User::hasWatched(Watchable* watch){
    for (int i = 0; i < history.size(); i++)
        if (history[i] == watch)
            return true;
    return false;
}

User::~User() {
    history.clear();
}
