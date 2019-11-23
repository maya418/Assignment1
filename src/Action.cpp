//
// Created by maya on 11/18/19.
//
#include <sstream>
#include <vector>
#include "../include/Action.h"
#include "../include/User.h"
#include "../include/Session.h"
#include "../include/Watchable.h"
#include <string>

using namespace std;

BaseAction::BaseAction() {


}

void BaseAction::act(Session &sess) {

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(const std::string &errorMsg) {
    this->errorMsg = errorMsg;
    status = ERROR;
}

string BaseAction::getErrorMsg() const {
    return errorMsg;
}

void CreateUser::act(Session &sess) {
    string action = sess.getUserAction();
    vector<std::string> result = splitText(action);
    const string name = result[1];
    string preferredAlgo = result[2];
    if ((preferredAlgo.length() == 3) &&
        (preferredAlgo == "len" | preferredAlgo == "rer" | preferredAlgo == "gen") && !sess.contain(name)) {
        if (preferredAlgo == "len") {
            LengthRecommenderUser *newUser = new LengthRecommenderUser(name);
            sess.getMap()->insert({name, newUser});
        } else if (preferredAlgo == "rer") {
            RerunRecommenderUser *newUser = new RerunRecommenderUser(name);
            sess.getMap()->insert({name, newUser});
        } else {
            GenreRecommenderUser *newUser = new GenreRecommenderUser(name);
            sess.getMap()->insert({name, newUser});
        }
        complete();
        //error();
        // cout << "you got a problem my friend";
    }
}

void ChangeActiveUser::act(Session &sess) {
    string action = sess.getUserAction();
    vector<std::string> result = splitText(action);
    string name = result[1];
    cout << sess.contain(name);
    if (sess.contain(name)) {
        sess.setActiveUser(sess.findUser(name));
        complete();
    } else {
        error("this user does`nt exsist");
    }
}

void DeleteUser::act(Session &sess) {
    string action = sess.getUserAction();
    vector<std::string> result = splitText(action);
    string name = result[1];
    if (sess.contain(name)) {
        sess.getMap()->erase(name);
        complete();
    } else {
        error("did`nt find this user to delete");
    }
}

void DuplicateUser::act(Session &sess) {
    string action = sess.getUserAction();
    vector<std::string> result = splitText(action);
    string original_name = result[1];
    string new_name = result[2];
    if (sess.contain(original_name) & !sess.contain(new_name)) {
        User *original_user = sess.findUser(original_name);
        //original_user = new
        //User* new_user = new User(original_user , new_name);
        //sess.getMap()->insert({new_name, new_user});
        complete();
    } else {
        error("this user does`nt exsist so we cant Duplicate");
    }
}

void PrintContentList::act(Session &sess) {
    for (int i = 0; i < sess.getContent().size(); i++) {
        Watchable *currentContent = sess.getContent()[i];
        cout << currentContent->getId() << ". " << currentContent->toString() << " " << currentContent->getLength()
             << " minutes [";
        for (int j = 0; j < currentContent->getTags().size(); j++) {
            cout << currentContent->getTags()[j];
            if (j < currentContent->getTags().size() - 1)
                cout << ", ";
        }
        cout << "]" << "\n";
    }
}

void PrintWatchHistory::act(Session &sess) {
    cout << "watch history for " << sess.getActiveUser()->getName() << "\n";
    for (int i = 0; i < sess.getActiveUser()->get_history().size(); i++) {
        cout << (i + 1) << ". " << sess.getActiveUser()->get_history()[i]->toString() << "\n";
    }
}

void Watch::act(Session &sess) {
    string action = sess.getUserAction();
    vector<std::string> result = splitText(action);
    string id = result[1];
    Watchable *watch = sess.getContent()[(std::stoi(id) - 1)];
    sess.getActiveUser()->set_history(watch);
    cout << "watching now " << watch->toString() << "\n";
    Watchable *next = watch->getNextWatchable(sess);
    if (next != nullptr) {
        cout << "We recommend watching " << next->toString() << ", continue watching? [y/n]" << "\n";
        string answer;
        getline(cin, answer);
        if (answer == "y") {
            complete();
            sess.setUserAction("watch " + std::to_string(next->getId()));
            act(sess);
        } else complete();
    } else complete();
}


void PrintActionsLog::act(Session &sess) {
    vector<BaseAction *> actionLog = sess.getActionsLog();
    for (int i = (actionLog.size() - 1); i >= 0; i--) {
        cout << actionLog[i]->toString() + " ";
        ActionStatus k = actionLog[i]->getStatus();
        if (k==COMPLETED)
            cout << "complete";
        else if (k==PENDING)
            cout << "PENDING";
        else if (k == ERROR)
            cout << actionLog[i]->getErrorMsg();
        cout <<  "\n";
    }
    complete();
}  //Printing all user action logs from end to start



void Exit::act(Session &sess) {
}

vector<string> BaseAction::splitText(string action) {
    vector<std::string> result;
    std::istringstream iss(action);
    for (std::string s; iss >> s;)
        result.push_back(s);
    return result;
}


// ToString for every action start here:

string BaseAction::toString() const {

}

string CreateUser::toString() const {
    return "CreateUser";
}

string DeleteUser::toString() const {

    return "DeleteUser";
}

string DuplicateUser::toString() const {

    return "DuplicateUser";
}

string PrintWatchHistory::toString() const {

    return "PrintWatchHistory";
}

string ChangeActiveUser::toString() const {

    return "ChangeActiveUser";
}

string PrintContentList::toString() const {

    return "PrintContentList";
}

string Watch::toString() const {

    return "Watch";
}

string PrintActionsLog::toString() const {

    return "PrintActionsLog";
}

string Exit::toString() const {

    return "Exit";
}
