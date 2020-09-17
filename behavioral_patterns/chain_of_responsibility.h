#ifndef CHAIN_OF_RESPONSIBILITY_H
#define CHAIN_OF_RESPONSIBILITY_H

#include <iostream>
#include <string>
#include <memory>

namespace Chain_Of_Responsibility
{

struct User
{
	std::string id;
	std::string name;
	std::string email;
};

class UserChecker
{
	UserChecker* next_checker;
public:
	void then(UserChecker* next_checker)
	{
		this->next_checker = next_checker;
	}

	bool next_check(User user)
	{
		if(this->next_checker != nullptr)
		{
			return this->next_checker->check_user(user);
		}
	}

	virtual bool check_user(User user) = 0;
};

class UserIdChecker : public UserChecker
{
public:
	virtual bool check_user(User user)
	{
		if(!user.id.empty()) {
			return this->next_check(user);
		} else {
			std::cerr << "User ID is not valid" << std::endl;
			return false;
		}
	}
};

class UserNameChecker : public UserChecker
{
public:
	virtual bool check_user(User user)
	{
		if(!user.name.empty()) {
			return this->next_check(user);
		} else {
			std::cerr << "User Name is not valid" << std::endl;
			return false;
		}
	}
};

class UserEmailChecker : public UserChecker
{
public:
	virtual bool check_user(User user)
	{
		if(!user.email.empty()) {
			return this->next_check(user);
		} else {
			std::cerr << "User Email is not valid" << std::endl;
			return false;
		}
	}
};

} // Chain_Of_Responsibility namespace

#endif // CHAIN_OF_RESPONSIBILITY_H
