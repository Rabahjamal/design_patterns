#include "builder.h"
#include "factory_method.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace std;


TEST_CASE("builder")
{
	ToyotaBuilder builder;

	Director d(builder);

	Car c1 = d.create_small_toyota_car();

	Car c2 = d.create_small_toyota_car();
}

void print_maze_game(const vector<unique_ptr<Room>>& rooms)
{
	for(const auto& room : rooms)
	{
		cout << room->get_room_name() << endl;
	}
}

TEST_CASE("factory method")
{
	// create a magic maze game
	unique_ptr<MazeGameFactory> magic_maze_creator = std::make_unique<MagicMazeGame>();
	std::vector<unique_ptr<Room>> magic_rooms1 = magic_maze_creator->design_maze_game(3);
	print_maze_game(magic_rooms1);

	// create another magic maze game using the same creator
	vector<unique_ptr<Room>> magic_rooms2 = magic_maze_creator->design_maze_game(2);
	print_maze_game(magic_rooms2);

	// create your magic maze game by calling the factory method directly
	unique_ptr<Room> first_room = magic_maze_creator->make_room("first magic room");
	unique_ptr<Room> second_room = magic_maze_creator->make_room("second magic room");
	second_room->connect(*first_room);

	// create an ordinary maze game
	unique_ptr<MazeGameFactory> ordinary_maze_creator = std::make_unique<OrdinaryMazeGame>();
	std::vector<unique_ptr<Room>> ordinary_rooms = ordinary_maze_creator->design_maze_game(3);
	print_maze_game(ordinary_rooms);

	// create your ordinary maze game by calling the factory method directly
	first_room = magic_maze_creator->make_room("first ordinary room");
	second_room = magic_maze_creator->make_room("second ordinary room");
	second_room->connect(*first_room);
}

