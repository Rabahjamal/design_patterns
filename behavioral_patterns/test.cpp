#include "chain_of_responsibility.h"
#include "command.h"
#include "iterator.h"
#include "mediator.h"
#include "memento.h"

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

TEST_CASE("command")
{
	using namespace Command;

	Light light;

	unique_ptr<ICommand> on_command = make_unique<TurnOnCommand>(&light);

	unique_ptr<Switch> light_switch = make_unique<Switch>(on_command.get());

	light_switch->press();

	unique_ptr<ICommand> off_command = make_unique<TurnOffCommand>(&light);
	light_switch = make_unique<Switch>(off_command.get());

	light_switch->press();
}

TEST_CASE("iterator")
{
	Iterator::MessageCollection mcl;

	mcl.add_message(Iterator::Message{1, "first message"});
	mcl.add_message(Iterator::Message{2, "second message"});
	mcl.add_message(Iterator::Message{3, "third message"});

	Iterator::Iterator* it = mcl.create_iterator();

	while(it->has_next())
	{
		Iterator::Message m = std::any_cast<Iterator::Message>(it->next());
		cout << m.message_id << ": " << m.message_content << endl;
	}

}


TEST_CASE("mediator")
{
	using namespace MediatorPattern;

	unique_ptr<Mediator> chat_room = make_unique<ChatRoom>();

	unique_ptr<User> user1 = make_unique<ChatUser>(chat_room.get(), "1", "Ali");
	unique_ptr<User> user2 = make_unique<ChatUser>(chat_room.get(), "2", "Ahmed");
	unique_ptr<User> user3 = make_unique<ChatUser>(chat_room.get(), "3", "Sami");
	unique_ptr<User> user4 = make_unique<ChatUser>(chat_room.get(), "4", "Sara");

	chat_room->add_user(user1.get());
	chat_room->add_user(user2.get());
	chat_room->add_user(user3.get());
	chat_room->add_user(user4.get());

	user1->send("Hello Ahmed", "2");
	user2->send("what's up bro", "1");
}

TEST_CASE("memento")
{
	using namespace Memento;

	Article article(1, "koko", "first article");

	cout << article << endl;

	unique_ptr<ArticleMemento> memento = article.create_memento();

	article.set_title("fofo");
	article.set_content("first article - modified");

	cout << article << endl;

	article.restore(memento);

	cout << article << endl;
}
