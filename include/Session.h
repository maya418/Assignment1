#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    Session(const Session &sess);
    ~Session();
    void start();
    void setActiveUser(User* user);

    User* getActiveUser();
    void setUserAction(std::string action);
    std::vector<Watchable*> getContent();

    bool contain(std::string name);
    User* findUser(std::string name);
    std::vector<std::string>splitText(std::string action);
    std::unordered_map<std::string,User*>* getMap();
    std::vector<BaseAction*> getActionsLog();
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
};
#endif