#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <iostream>
#include <string>
#include <map>
#include <memory>

namespace MediatorPattern
{

class User;

class Mediator
{
public:
	virtual void send_message(const std::string& message, const std::string& user_id) = 0;

	virtual void add_user(User* user) = 0;
};

class User
{
	std::string user_id;
	std::string user_name;
protected:
	Mediator* mediator;
public:
	User(Mediator* mediator, const std::string& user_id, const std::string& user_name) :
		mediator(mediator), user_id(user_id), user_name(user_name)
	{}

	virtual void send(const std::string& message, const std::string& user_id) = 0;

	virtual void receive(const std::string& message) = 0;

	std::string get_id() const
	{
		return this->user_id;
	}

	std::string get_name() const
	{
		return this->user_name;
	}
};

class ChatUser : public User
{
public:
	ChatUser(Mediator* mediator, const std::string& user_id, const std::string& user_name) :
		User(mediator, user_id, user_name)
	{}

	void send(const std::string& message, const std::string& user_id)
	{
		std::cout << this->get_name() << " --> Sending Message : " << message << std::endl;
		this->mediator->send_message(message, user_id);
	}

	void receive(const std::string& message)
	{
		std::cout << this->get_name() << " --> Received Message : " << message << std::endl;
	}
};

class ChatRoom : public Mediator
{
	std::map<std::string, std::unique_ptr<User>> users;
public:
	void send_message(const std::string& message, const std::string& user_id)
	{
		User* user = users[user_id].get();
		user->receive(message);
	}

	void add_user(User* user)
	{
		users[user->get_id()] = std::unique_ptr<User>(user);
	}
};

}

#endif // MEDIATOR_H
