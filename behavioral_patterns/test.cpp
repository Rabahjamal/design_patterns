#include "chain_of_responsibility.h"
#include "command.h"
#include "iterator.h"
#include "mediator.h"
#include "memento.h"
#include "observer.h"
#include "state.h"
#include "strategy.h"
#include "template_method.h"
#include "visitor.h"

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

TEST_CASE("Observer")
{
	using namespace ObserverPattern;

	std::unique_ptr<Observer> ms1 = std::make_unique<MessageSubscriberOne>();
	std::unique_ptr<Observer> ms2 = std::make_unique<MessageSubscriberTwo>();
	std::unique_ptr<Observer> ms3_1 = std::make_unique<MessageSubscriberThree>();
	std::unique_ptr<Observer> ms3_2 = std::make_unique<MessageSubscriberThree>();

	unique_ptr<Subject> message_publisher = make_unique<MessagePublisher>();

	message_publisher->attach(ms1.get());
	message_publisher->attach(ms2.get());

	message_publisher->notify("koko");

	cout << "----------------------------------" << endl;

	message_publisher->detach(ms1.get());
	message_publisher->attach(ms3_1.get());

	message_publisher->notify("soso");

	cout << "----------------------------------" << endl;

	message_publisher->detach(ms2.get());
	message_publisher->attach(ms3_2.get());

	message_publisher->notify("fofo");

	cout << "----------------------------------" << endl;

	message_publisher->detach(ms3_1.get());

	message_publisher->notify("toto");

	cout << "----------------------------------" << endl;

	message_publisher->detach(ms3_2.get());

	message_publisher->notify("zozo");

}

TEST_CASE("State")
{
	using namespace State;

	unique_ptr<MobileAlertState> vibration_state = make_unique<Vibration>();
	unique_ptr<MobileAlertState> silent_state = make_unique<Silent>();
	unique_ptr<MobileAlertState> sound_state = make_unique<Sound>();

	AlertStateContext ctx(vibration_state.get());

	ctx.alert();

	ctx.set_state(silent_state.get());
	ctx.alert();

	ctx.set_state(sound_state.get());
	ctx.alert();


	 ctx.set_state(vibration_state.get());
	 ctx.alert();
}

TEST_CASE("Strategy")
{
	using namespace Strategy;

	unique_ptr<ISocialMediaStrategy> facebook_strategy = make_unique<FacebookStrategy>();
	unique_ptr<ISocialMediaStrategy> twitter_strategy = make_unique<TwitterStrategy>();

	Context ctx(facebook_strategy.get());

	ctx.connect("ahmed");

	cout << "----------------------------------------------" << endl;

	ctx.set_strategy(twitter_strategy.get());
	ctx.connect("ahmed");

	cout << "----------------------------------------------" << endl;

	ctx.set_strategy(facebook_strategy.get());
	ctx.connect("john");
}

TEST_CASE("Template Method")
{
	using namespace TemplateMethod;

	unique_ptr<DataMiner> data_miner = make_unique<PDFDataMiner>();

	data_miner->mine("pdf_file");

	cout << "----------------------" << endl;

	data_miner = make_unique<CSVDataMiner>();

	data_miner->mine("csv file");

	cout << "----------------------" << endl;

	data_miner = make_unique<DocxDataMiner>();

	data_miner->mine("docx file");
}

TEST_CASE("Visitor")
{
    using namespace Visitor;

    unique_ptr<RouterVisitor> linux_cfg = make_unique<LinuxConfig>();
    unique_ptr<RouterVisitor> windows_cfg = make_unique<WindowsConfig>();

    unique_ptr<Router> dlink_router = make_unique<DLinkRouter>();
    unique_ptr<Router> tplink_router = make_unique<TPLinkRouter>();

    dlink_router->accept(linux_cfg.get());
    dlink_router->accept(windows_cfg.get());

    tplink_router->accept(linux_cfg.get());
    tplink_router->accept(windows_cfg.get());
}
