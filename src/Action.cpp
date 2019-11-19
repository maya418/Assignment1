//
// Created by maya on 11/18/19.
//
#include <sstream>
#include "../include/Action.h"
#include "../include/User.h"
#include "../include/Session.h"

using namespace std;

BaseAction::BaseAction(){

}

void BaseAction::act(Session& sess){

}

ActionStatus BaseAction::getStatus()const{
    return status;
}

void BaseAction::complete(){
    status = COMPLETED;
}

void BaseAction::error(const std::string& errorMsg){
    status = ERROR;
}

string BaseAction::getErrorMsg() const{
    return errorMsg;
}

void CreateUser::act(Session& sess){
    string action = sess.getUserAction();
    result = splitTe
     string name = result[1];
     string preferredAlgo = result[2];
     if ((preferredAlgo.length() == 3 )&& (preferredAlgo == "len" | preferredAlgo == "rer" | preferredAlgo == "gen") && !sess.contain(name)){
         //pending
        if (preferredAlgo == "len")
            LengthRecommenderUser* newUser = new LengthRecommenderUser(name);
        else if(preferredAlgo == "rer")
            RerunRecommenderUser* newUser = new RerunRecommenderUser(name);
        else
            GenreRecommenderUser* newUser = new GenreRecommenderUser(name);
       complete();
     }
     else
         //error();
         cout << "you got a problem my friend";
}

void ChangeActiveUser::act(Session& sess){
    if (sess.contain(name))
}
/*
void DeleteUser::act(Session& sess){

}

void DuplicateUser::act(Session& sess){

}

void PrintContentList::act(Session& sess){

}

void PrintWatchHistory::act(Session& sess){

}
*/
void Watch::act(Session& sess){
    //found whatever user want lets say its:
    Watchable* found;
    sess.getActiveUser()->get_history().push_back(found);
}

//void PrintActionsLog::act(Session& sess){

//}

void Exit::act(Session& sess){

}

//string BaseAction::toString()const{

//}

vector<string> splitText(string action){
    vector<std::string> result;
    std::istringstream iss(action);
    for(std::string s; iss >> s; )
        result.push_back(s);
    return result;
}


