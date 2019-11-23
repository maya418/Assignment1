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
    cout << "complete";
}

void BaseAction::error(const std::string &errorMsg) {
    status = ERROR;
}

string BaseAction::getErrorMsg() const {
    return errorMsg;
}

void CreateUser::act(Session &sess) {
    cout << "pending" << "\n";
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
        //error();
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
        //error();
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
        //error
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
        cout << (i + 1) << ". " << sess.getActiveUser()-> get_history()[i]-> toString() << "\n";
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
    vector<BaseAction *> *k = sess.getActionsLog();
    CreateUser* createUser = new CreateUser();
    BaseAction* t = createUser;
    t->toString();
    t = *k[0];
    for (int i = k->size()-1; i >= 0; i--) {
        cout << k[i].size() << " " << "\n";
    }
}



void Exit::act(Session &sess) {

}

vector<string> BaseAction::splitText(string action) {
    vector<std::string> result;
    std::istringstream iss(action);
    for (std::string s; iss >> s;)
        result.push_back(s);
    return result;
}


// ToString for evryaction start here:


string CreateUser :: toString() const {

    return "printing";
}

string DeleteUser :: toString() const {

    return "printing";
}

string DuplicateUser :: toString() const {

    return "printing";
}
string PrintWatchHistory :: toString() const {

    return "printing";
}

string ChangeActiveUser :: toString() const {

    return "printing";
}

string PrintContentList :: toString() const {

    return "printing";
}

string Watch :: toString() const {

    return "printing";
}

string PrintActionsLog :: toString() const {

    return "printing";
}
string Exit :: toString() const {

    return "printing";
}
