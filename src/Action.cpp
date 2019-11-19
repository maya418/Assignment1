//
// Created by maya on 11/18/19.
//
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

    //sess.addUser();
     //string name = sess.action.substr(sess.action.find(" ") , sess.action.find(" "));
     //cout << sess.action;
   //if (type.compare)
}
/*
void ChangeActiveUser::act(Session& sess){

}

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

