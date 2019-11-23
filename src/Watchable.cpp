//
// Created by maya on 11/18/19.
//
#include "../include/Watchable.h"
#include "../include/Session.h"

using namespace std;

Watchable::Watchable(long id, int length, const std::vector<std::string>& tags):id(id), length(length), tags(tags) {

}

string Watchable::toString() const{
    return " ";
}

Watchable* Watchable::getNextWatchable(Session& sess) const{

}

int Watchable::getLength(){
    return length;
}
Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags) : name(name) , Watchable(id, length , tags) {

}

Watchable* Movie::getNextWatchable(Session& sess) const {
    Watchable* next;
    return next;
}


string Movie::toString() const {
    return name;
}

Episode::Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags) : seriesName(seriesName) , Watchable(id, length , tags){

}

Watchable* Episode::getNextWatchable(Session& sess) const {
    Watchable* next;
    return next;
}


string Episode::toString() const {
    return seriesName;
}
