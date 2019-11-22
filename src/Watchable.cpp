//
// Created by maya on 11/18/19.
//
#include "../include/Watchable.h"
#include "../include/Session.h"
#include "../include/User.h"

using namespace std;

Watchable::Watchable(long id, int length, const std::vector<std::string>& tags):id(id), length(length), tags(tags) {

}

string Watchable::toString() const{
    return " ";
}

Watchable* Watchable::getNextWatchable(Session& s) const{

}

int Watchable::getLength(){
    return length;
}

const long Watchable::getId(){
    return id;
}

Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags) : name(name) , Watchable(id, length , tags) {

}

Watchable* Movie::getNextWatchable(Session& s) const {
    Watchable* next = s.getActiveUser()->getRecommendation(s);
    return next;
}


string Movie::toString() const {
    return name;
}

Episode::Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags) : seriesName(seriesName) , Watchable(id, length , tags){

}

Watchable* Episode::getNextWatchable(Session& s) const {
    Watchable* next;
    return next;
}


string Episode::toString() const {
    return seriesName;
}
