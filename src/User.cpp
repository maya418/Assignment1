//
// Created by maya on 11/18/19.
//
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"

using namespace std;

//constructor
User::User(const std::string& name):name(name) {

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
    lastRecommendedId = -1;
}

//find the next recommended content to watched based on Rerun Algorithm
Watchable* RerunRecommenderUser::getRecommendation(Session& s){
    if (lastRecommendedId == -1)/*first content user had watched*/ {
        lastRecommendedId = 0;
        return nullptr;
    }
    Watchable* next = history[lastRecommendedId];
    lastRecommendedId = (lastRecommendedId + 1)%history.size();
    return next;
}

//constructor
GenreRecommenderUser::GenreRecommenderUser(const std::string &name): User(name){

}

//this function return true if the user already watched a show or false if he hasn't.
bool User::hasWatched(Watchable* watch){
    for (int i = 0; i < history.size(); i++)
        if (history[i] == watch)
            return true;
    return false;
}

Watchable* GenreRecommenderUser::getRecommendation(Session& s){
    Watchable* a;
    return a;
}





