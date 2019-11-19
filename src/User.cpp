//
// Created by maya on 11/18/19.
//
#include "../include/User.h"
#include "../include/Watchable.h"

using namespace std;

User::User(const std::string& name):name(name) {

}
/*
Watchable* User::getRecommendation(Session& s){
    //Watchable* a;
    //return a;
}
*/
string User::getName()const{
    return name;
}

vector<Watchable*> User::get_history()const{
    return history;
}

LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {

}
/*
Watchable* LengthRecommenderUser::getRecommendation(Session& s){
    Watchable* a;
    return a;
}*/

RerunRecommenderUser::RerunRecommenderUser(const std::string &name): User(name){

}
/*
Watchable* RerunRecommenderUser::getRecommendation(Session& s){
    Watchable* a;
    return a;
}*/


GenreRecommenderUser::GenreRecommenderUser(const std::string &name): User(name){

}

/*Watchable* GenreRecommenderUser::getRecommendation(Session& s){
    Watchable* a;
    return a;
}*/





