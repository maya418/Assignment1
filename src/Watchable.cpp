//
// Created by maya on 11/18/19.
//
#include "../include/Watchable.h"

using namespace std;

Watchable::Watchable(long id, int length, const std::vector<std::string>& tags):id(id), length(length), tags(tags) {

}
/*
string Watchable::toString() const{
    return "a";
}

Watchable* Watchable::getNextWatchable(Session&) const{

}*/

Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags) : Watchable(id, length , tags) {

}

Episode::Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags) : Watchable(id, length , tags) {

}