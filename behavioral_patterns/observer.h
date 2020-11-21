#ifndef OBSERVER_H
#define OBSERVER_H

#include <set>
#include <string>
#include <iostream>

namespace ObserverPattern
{

class Observer
{
public:
	virtual void update(const std::string& message) = 0;
};

class Subject
{
public:
	virtual void attach(Observer* observer) = 0;
	virtual void detach(Observer* observer) = 0;
	virtual void notify(const std::string& message) = 0;
};

class MessagePublisher : public Subject
{
	std::set<Observer*> observers;
public:

	void attach(Observer* observer) override
	{
		observers.insert(observer);
	}

	void detach(Observer* observer) override
	{
		observers.erase(observer);
	}

	void notify(const std::string& message) override
	{
		for(auto observer : observers)
		{
			observer->update(message);
		}
	}
};

class MessageSubscriberOne : public Observer
{
public:
	void update(const std::string& message) override
	{
		std::cout << "MessageSubscriberOne: " << message << std::endl;
	}
};

class MessageSubscriberTwo : public Observer
{
public:
	void update(const std::string& message) override
	{
		std::cout << "MessageSubscriberTwo: " << message << std::endl;
	}
};

class MessageSubscriberThree : public Observer
{
public:
	void update(const std::string& message) override
	{
		std::cout << "MessageSubscriberThree: " << message << std::endl;
	}
};

} // namespace ObserverPattern

#endif // OBSERVER_H
