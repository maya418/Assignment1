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
} // just return the status (compled , panding , error)

void BaseAction::complete() {
    status = COMPLETED;
} // if the commend has been successful we change the status to COMPLETED

void BaseAction::error(const std::string &errorMsg) {
    this->errorMsg = errorMsg;
    status = ERROR;
} // here we will init the errorMsg string variable if there is any error.

string BaseAction::getErrorMsg() const {
    return errorMsg;
}

CreateUser::CreateUser(string name, string algorithm) : name(name), algorithm(algorithm) {

} // here we init the field variables of User (name , algorithm)

void CreateUser::act(Session &sess) {
    if ((algorithm.length() == 3) &&
        (algorithm == "len" | algorithm == "rer" | algorithm == "gen")) {
        if (!sess.contain(name)) {
            if (algorithm == "len") {
                LengthRecommenderUser *newUser = new LengthRecommenderUser(name);
                sess.getMap()->insert({name, newUser});
            } else if (algorithm == "rer") {
                RerunRecommenderUser *newUser = new RerunRecommenderUser(name);
                sess.getMap()->insert({name, newUser});
            } else {
                GenreRecommenderUser *newUser = new GenreRecommenderUser(name);
                sess.getMap()->insert({name, newUser});
            }
            complete();
        } else {
            error("user already exist");
        } // if sess already contain the name thet was given we add error massage that the username is already been taken
    } else
        error("wrong algorithm name");
    // if we get to this else its means we did`nt pass the first if what`s means
    // that ether he did`nt enter 3 char algorithm or the user did`nt enter one of the 3 algorithm to chose from

} // this function acttuley build the new user depending on the algorithm that was given to us

ChangeActiveUser::ChangeActiveUser(string name) : name(name) {

}

void ChangeActiveUser::act(Session &sess) {
    if (sess.contain(name)) {
        sess.setActiveUser(sess.findUser(name));
        complete();
    } // first we chack if such user exist , if so we will change our active user veribale to the given one.

    else {
        error("this user doesn't exist");
    }// if we get to this else its mean`s that we did`nt find the user in our Usermap date base.
}

DeleteUser::DeleteUser(string name) : name(name) {

}//we init the veribale name

void DeleteUser::act(Session &sess) {
    if (sess.contain(name)) {
        delete sess.findUser(name); // first we delete the user himself by User destrector.
        sess.getMap()->erase(name); // secondly we delete the user from our map.
        complete();
    }
    else {
        error("didn't find a user with this name to delete");
    } // if we get to this else its mean`s that we did`nt find the user in our Usermap date base.
}

DuplicateUser::DuplicateUser(string otherName, string myName) : otherName(otherName), myName(myName) {

}

void DuplicateUser::act(Session &sess) {
    if (sess.contain(otherName)) {
        if (!sess.contain(myName)) {
            User *original_user = sess.findUser(otherName);
            if (original_user->getAlgorithm() == "len") {
                LengthRecommenderUser *newUser = new LengthRecommenderUser(myName);
                sess.getMap()->insert({myName, newUser});
            } else if (original_user->getAlgorithm() == "rer") {
                RerunRecommenderUser *newUser = new RerunRecommenderUser(myName);
                sess.getMap()->insert({myName, newUser});
            } else if (original_user->getAlgorithm() == "gen") {
                GenreRecommenderUser *newUser = new GenreRecommenderUser(myName);
                sess.getMap()->insert({myName, newUser});
            } // createing a
            complete();
        } else
            error("user already exist");
    } else {
        error("this user to duplicate from doesn't exist");
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
    complete();
}

void PrintWatchHistory::act(Session &sess) {
    cout << "watch history for " << sess.getActiveUser()->getName() << "\n";
    for (int i = 0; i < sess.getActiveUser()->get_history().size(); i++) {
        cout << (i + 1) << ". " << sess.getActiveUser()->get_history()[i]->toString() << "\n";
    }
    complete();
}

Watch::Watch(string id) : id(id) {

}

void Watch::act(Session &sess) {
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
            id = to_string(next->getId());
            act(sess);
        } else complete();
    } else complete();
}


void PrintActionsLog::act(Session &sess) {
    vector<BaseAction *> actionLog = sess.getActionsLog();
    for (int i = (actionLog.size() - 1); i >= 0; i--) {
        cout << actionLog[i]->toString() + " ";
        ActionStatus status = actionLog[i]->getStatus();
        if (status == COMPLETED)
            cout << "complete";
        else if (status == PENDING)
            cout << "PENDING";
        else if (status == ERROR)
            cout << actionLog[i]->getErrorMsg();
        cout << "\n";
    }
    complete();
}  //Printing all user action logs from end to start



void Exit::act(Session &sess) {
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