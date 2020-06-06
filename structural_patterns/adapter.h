#ifndef ADAPTER_H
#define ADAPTER_H

#include <string>
#include <iostream>

namespace Adapter
{

class EnemyAttacker
{
public:
	EnemyAttacker() {}

	virtual void fire_weapon() const = 0;

	virtual void drive_forward() const = 0;

	virtual void assign_driver(const std::string& driver_name) const = 0;

	virtual ~EnemyAttacker() = default;
};

class EnemyRobot
{
public:
	EnemyRobot() {}

	void smash() const
	{
		int damage = std::rand() % 10 + 1;
		std::cout << "Enemy Robot Causes " << damage << " Damage" << std::endl;
	}

	void walk_forward() const
	{
		int movement = std::rand() % 10 + 1;
		std::cout << "Enemy Robot Walks Forward " << movement << " spaces" << std::endl;
	}

	void react_to_human(const std::string& driver_name) const
	{
		std::cout << "Enemy Robot reacts with " << driver_name << std::endl;
	}
};

class EnemyRobotAdapter : public EnemyAttacker
{
	EnemyRobot enemy_robot;
public:
	EnemyRobotAdapter(const EnemyRobot& enemy_robot)
	{
		this->enemy_robot = enemy_robot;
	}

	void fire_weapon() const
	{
		enemy_robot.smash();
	}

	void drive_forward() const
	{
		enemy_robot.walk_forward();
	}

	void assign_driver(const std::string& driver_name) const
	{
		enemy_robot.react_to_human(driver_name);
	}
};

void client(const EnemyAttacker& enemy_attacker)
{
	enemy_attacker.fire_weapon();
	enemy_attacker.drive_forward();
	enemy_attacker.assign_driver("John");
}

} // namespace Adapter

#endif // ADAPTER_H
