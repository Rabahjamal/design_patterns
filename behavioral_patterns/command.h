#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

namespace Command
{

// The receiver class
class Light
{
public:
	void turn_on()
	{
		std::cout << "Turn the light on" << std::endl;
	}

	void turn_off()
	{
		std::cout << "Turn the light off" << std::endl;
	}
};

// Command interface
class ICommand
{
public:
	virtual void execute() = 0;
};

class TurnOnCommand : public ICommand
{
	Light* light;
public:
	TurnOnCommand(Light* light)
	{
		this->light = light;
	}

	void execute() override
	{
		this->light->turn_on();
	}
};

class TurnOffCommand : public ICommand
{
	Light* light;
public:
	TurnOffCommand(Light* light)
	{
		this->light = light;
	}

	void execute() override
	{
		this->light->turn_off();
	}
};

// The invoker class
class Switch
{
	ICommand* command;
public:
	Switch(ICommand* command)
	{
		this->command = command;
	}

	void press()
	{
		this->command->execute();
	}
};
}	// namespace Command

#endif // COMMAND_H
