#include "builder.h"
#include "factory_method.h"
#include "abstract_factory.h"
#include "prototype.h"
#include "singleton.h"

#include <thread>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace std;


TEST_CASE("builder")
{
	Builder::ToyotaBuilder builder;

	Builder::Director d(builder);

	Builder::Car c1 = d.create_small_toyota_car();

	Builder::Car c2 = d.create_small_toyota_car();
}

void print_maze_game(const vector<unique_ptr<FactoryMethod::Room>>& rooms)
{
	for(const auto& room : rooms)
	{
		cout << room->get_room_name() << endl;
	}
}

TEST_CASE("factory method")
{
	// create a magic maze game
	unique_ptr<FactoryMethod::MazeGameFactory> magic_maze_creator = std::make_unique<FactoryMethod::MagicMazeGame>();
	std::vector<unique_ptr<FactoryMethod::Room>> magic_rooms1 = magic_maze_creator->design_maze_game(3);
	print_maze_game(magic_rooms1);

	// create another magic maze game using the same creator
	vector<unique_ptr<FactoryMethod::Room>> magic_rooms2 = magic_maze_creator->design_maze_game(2);
	print_maze_game(magic_rooms2);

	// create your magic maze game by calling the factory method directly
	unique_ptr<FactoryMethod::Room> first_room = magic_maze_creator->make_room("first magic room");
	unique_ptr<FactoryMethod::Room> second_room = magic_maze_creator->make_room("second magic room");
	second_room->connect(*first_room);

	// create an ordinary maze game
	unique_ptr<FactoryMethod::MazeGameFactory> ordinary_maze_creator = std::make_unique<FactoryMethod::OrdinaryMazeGame>();
	std::vector<unique_ptr<FactoryMethod::Room>> ordinary_rooms = ordinary_maze_creator->design_maze_game(3);
	print_maze_game(ordinary_rooms);

	// create your ordinary maze game by calling the factory method directly
	first_room = magic_maze_creator->make_room("first ordinary room");
	second_room = magic_maze_creator->make_room("second ordinary room");
	second_room->connect(*first_room);
}

TEST_CASE("abstract factory")
{
	cout << "Please choese an option: \n1. Windows\n2. Linux\n";

	int opt;

	cin >> opt;

	using namespace AbstractFactory;

	if(opt == 1)
	{
		unique_ptr<WinFactory> factory = make_unique<WinFactory>();
		create_ui(*factory);
	}
	else if(opt == 2)
	{
		unique_ptr<LinuxFactory> factory = make_unique<LinuxFactory>();
		create_ui(*factory);
	}
	else
	{
		cout << "Enter either 1 or 2" << endl;
	}

}


TEST_CASE("prototype")
{
	using namespace Prototype;

	unique_ptr<Shape> circle = make_unique<Circle>(30, "red");
	unique_ptr<Shape> circle_copy = circle->clone();

	unique_ptr<Shape> rectangle = make_unique<Rectangle>(20, 40, "blue");
	unique_ptr<Shape> rectangle_copy = rectangle->clone();

	ShapesRegistry registry;

	registry.add_shape(*circle);
	registry.add_shape(*circle_copy);
	registry.add_shape(*rectangle);
	registry.add_shape(*rectangle_copy);

	registry.print();

	cout << "_____________________________________________" << endl;

	ShapesRegistry registry_copy(registry);

	registry_copy.print();

	cout << "_____________________________________________" << endl;

	cout << circle->get_color() << endl;
	cout << circle_copy->get_color() << endl;
	cout << rectangle->get_color() << endl;
	cout << rectangle_copy->get_color() << endl;
}


TEST_CASE("singleton")
{
	Singleton::print_number_of_instances();

	Singleton* resource;

	vector<thread> threads(100);

#pragma omp parallel for
	for(size_t i = 0; i < 100; i++)
	{
		resource = Singleton::get_resource();
//		thread t([&]()
//		{
//			resource = Singleton::get_resource();
//		});
//		threads[i] = std::move(t);
	}

//	for(size_t i = 0; i < threads.size(); i++)
//	{
//		threads[i].join();
//	}


	Singleton::print_number_of_instances();
}
