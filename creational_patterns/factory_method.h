#ifndef FACTORY_METHOD_H
#define FACTORY_METHOD_H

#include <iostream>
#include <vector>
#include <memory>

class Room
{
	int walls_number;
	std::string room_name;
public:
	Room() {}

	virtual void connect(const Room& room) = 0;

	void set_walls_number(int walls_number)
	{
		this->walls_number = walls_number;
	}

	int get_walls_number() const
	{
		return get_walls_number();
	}

	void set_room_name(const std::string& room_name)
	{
		this->room_name = room_name;
	}

	std::string get_room_name() const
	{
		return this->room_name;
	}

	virtual ~Room()
	{
		//std::cout << "Room destructor was called" << std::endl;
	}
};

class MagicRoom : public Room
{
public:
	MagicRoom(const std::string& room_name)
	{
		set_walls_number(15);
		set_room_name(room_name);
	}

	void connect(const Room& room)
	{	
		std::cout << "Magic Room: " << this->get_room_name()
				  << " is connected to: " << room.get_room_name() << std::endl;
	}

	virtual ~MagicRoom()
	{
		//std::cout << "MagicRoom destructor was called" << std::endl;
	}
};

class OrdinaryRoom : public Room
{
public:
	OrdinaryRoom(const std::string& room_name)
	{
		set_walls_number(4);
		set_room_name(room_name);
	}

	void connect(const Room& room)
	{
		std::cout << "Ordinary Room: " << this->get_room_name()
				  << " is connected to: " << room.get_room_name() << std::endl;
	}

	virtual ~OrdinaryRoom()
	{
		//std::cout << "OrdinaryRoom destructor was called" << std::endl;
	}
};

class MazeGameFactory
{
public:

	std::vector<std::unique_ptr<Room>> design_maze_game(int number_of_rooms)
	{
		std::vector<std::unique_ptr<Room>> rooms;
		for(int i = 0; i < number_of_rooms; i++)
		{
			std::unique_ptr<Room> room = make_room("room #" + std::to_string(i+1));
			if(i > 0)
			{
				room->connect(*rooms[i-1]);
			}
			rooms.emplace_back(std::move(room));
		}

		return std::move(rooms);
	}

	virtual std::unique_ptr<Room> make_room(const std::string& room_name) = 0;

	virtual ~MazeGameFactory(){};
};

class MagicMazeGame : public MazeGameFactory
{
public:

	std::unique_ptr<Room> make_room(const std::string& room_name)
	{
		//std::cout << "create a magic room" << std::endl;

		std::unique_ptr<MagicRoom> magic_room =
				std::make_unique<MagicRoom>(room_name);
		return magic_room;
	}
};

class OrdinaryMazeGame : public MazeGameFactory
{
public:
	std::unique_ptr<Room> make_room(const std::string& room_name)
	{
		//std::cout << "create an ordinary room" << std::endl;

		std::unique_ptr<OrdinaryRoom> ordinary_room =
				std::make_unique<OrdinaryRoom>(room_name);
		return ordinary_room;
	}
};
#endif // FACTORY_METHOD_H
