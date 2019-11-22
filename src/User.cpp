//
// Created by maya on 11/18/19.
//
#include "../include/User.h"
#include "../include/Watchable.h"
#include "../include/Session.h"

using namespace std;

User::User(const std::string& name):name(name) {

}

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

LengthRecommenderUser::LengthRecommenderUser(const string& name) : User(name) {

}

Watchable* LengthRecommenderUser::getRecommendation(Session& s){
    int sum = 0;
    for (int i = 0; i < history.size(); i++)
        sum += history[i]->getLength();
    int averageLength = sum / history.size();
    int bestLength = 0;
    int bestIndex = -1;
    for (int i = 0; i < s.getContent().size(); i++)
        if (!hasWatched(s.getContent()[i])) {
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

}

Watchable* RerunRecommenderUser::getRecommendation(Session& s){
    Watchable* a;
    return a;
}


GenreRecommenderUser::GenreRecommenderUser(const std::string &name): User(name){

}

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





