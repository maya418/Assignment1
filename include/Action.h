#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>
#include <vector>

class Session;

enum ActionStatus{
	PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
	BaseAction();
	ActionStatus getStatus() const;
	virtual void act(Session& sess)=0;
	void complete();
	void error(const std::string& errorMsg);
	std::string getErrorMsg() const;
    virtual std::string toString() const=0;
    private:
	std::string errorMsg;
	ActionStatus status;
};

class CreateUser  : public BaseAction {
public:
    CreateUser(std::string name , std::string algorithm);
	virtual void act(Session& sess);
	virtual std::string toString() const;

private:
    std::string name;
    std::string algorithm;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser(std::string name);
	virtual void act(Session& sess);
	virtual std::string toString() const;

private:
    std::string name;
};

class DeleteUser : public BaseAction {
public:
    DeleteUser(std::string name);
	virtual void act(Session & sess);
	virtual std::string toString() const;

private:
    std::string name;
};


class DuplicateUser : public BaseAction {
public:
    DuplicateUser(std::string otherName , std::string myName);
	virtual void act(Session & sess);
	virtual std::string toString() const;


private:
    std::string otherName;
    std::string myName;
};

class PrintContentList : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
    Watch(std::string id);
	virtual void act(Session& sess);
	virtual std::string toString() const;

private:
    std::string id;
};


class PrintActionsLog : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class Exit : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};
#endif
