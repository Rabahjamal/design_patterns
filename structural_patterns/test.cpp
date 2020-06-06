#include "adapter.h"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

using namespace std;

TEST_CASE("Adapter")
{
	using namespace Adapter;

	EnemyRobot robot;
	unique_ptr<EnemyAttacker> enemy_attacker = make_unique<EnemyRobotAdapter>(robot);

	client(*enemy_attacker);
}
