#ifndef STATE_H
#define STATE_H

#include <string>
#include <iostream>

namespace State
{

class AlertStateContext;

class MobileAlertState
{
public:
	virtual void alert(AlertStateContext* ctx) = 0;
};

class AlertStateContext
{
	MobileAlertState* current_state;
public:
	AlertStateContext(MobileAlertState* state) : current_state(state)
	{}

	void set_state(MobileAlertState* state)
	{
		this->current_state = state;
	}

	void alert()
	{
		this->current_state->alert(this);
	}
};

class Vibration : public MobileAlertState
{
public:
	Vibration() = default;

	virtual void alert(AlertStateContext* ctx) override
	{
		std::cout << "vibration..." << std::endl;
	}
};

class Silent : public MobileAlertState
{
public:
	Silent() = default;

	virtual void alert(AlertStateContext* ctx) override
	{
		std::cout << "Silent..." << std::endl;
	}
};

class Sound : public MobileAlertState
{
public:
	Sound() = default;

	virtual void alert(AlertStateContext* ctx) override
	{
		std::cout << "Sound..." << std::endl;
	}
};

}

#endif // STATE_H
