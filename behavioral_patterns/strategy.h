#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>

namespace Strategy
{

class ISocialMediaStrategy
{
public:
	ISocialMediaStrategy() {}

	virtual void connectTo(const std::string& name) = 0;
};

class Context
{
	ISocialMediaStrategy* strategy;
public:
	Context(ISocialMediaStrategy* strategy)
	{
		this->strategy = strategy;
	}

	void set_strategy(ISocialMediaStrategy* strategy)
	{
		this->strategy = strategy;
	}

	void connect(const std::string& name)
	{
		this->strategy->connectTo(name);
	}
};

class FacebookStrategy : public ISocialMediaStrategy
{
public:
	FacebookStrategy() = default;

	void connectTo(const std::string& name) override
	{
		std::cout << "connect to " << name << " through Facebook" << std::endl;
	}
};

class TwitterStrategy : public ISocialMediaStrategy
{
public:
	TwitterStrategy() = default;

	void connectTo(const std::string& name) override
	{
		std::cout << "connect to " << name << " through Twitter" << std::endl;
	}
};

}

#endif // STRATEGY_H
