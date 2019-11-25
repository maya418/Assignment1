#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <map>

class Watchable;
class Session;

class User{
public:
    User(const std::string& name);
    const User& operator=(const User &other);
    virtual ~User();
    User(const User* other , const std::string &name);
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
    void set_history(Watchable* watch);
    bool hasWatched(Watchable* watch);
    virtual std::string getAlgorithm();
protected:
    std::vector<Watchable*> history;
private:
    const std::string name;

};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    LengthRecommenderUser(User *user, const std::string &name);
    virtual Watchable* getRecommendation(Session& s);
    std::string getAlgorithm();
//    ~LengthRecommenderUser();
private:
    std::string algorithm;
};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);

    RerunRecommenderUser(User *user, const std::string &name);

    virtual Watchable* getRecommendation(Session& s);
    std::string getAlgorithm();
private:
    std::string algorithm;
    int lastRecommendedId;
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);

    GenreRecommenderUser(User *user, const std::string &name);

    virtual Watchable* getRecommendation(Session& s);
    std::string getAlgorithm();
    std::string getBestTag(std::map<std::string , int> tagsCount);
private:
    std::string algorithm;
};

#endif