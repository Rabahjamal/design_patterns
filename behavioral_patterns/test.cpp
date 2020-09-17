#include "chain_of_responsibility.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace std;

TEST_CASE("chain of responsibility")
{
	using namespace Chain_Of_Responsibility;

	User user1 {"134249753240375043", "ali", "ali.k@gmail.com"};

	unique_ptr<UserChecker> id_checker = std::make_unique<UserIdChecker>();
	unique_ptr<UserChecker> name_checker = std::make_unique<UserNameChecker>();
	unique_ptr<UserChecker> email_checker = std::make_unique<UserEmailChecker>();

	id_checker->then(name_checker.get());
	name_checker->then(email_checker.get());

	if(id_checker->check_user(user1))
	{
		cout << "all checks passed!" << endl;
	}
}
