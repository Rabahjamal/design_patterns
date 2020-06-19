#include "adapter.h"
#include "bridge.h"

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

TEST_CASE("Bridge")
{
	using namespace Bridge;

	unique_ptr<Renderer> raster_renderer = make_unique<RasterRenderer>();
	vector<unique_ptr<Shape>> shapes;

	shapes.emplace_back(make_unique<Circle>(10, 2, 15, *raster_renderer));
	shapes.emplace_back(make_unique<Rectangle>(5, 12, 30, 34, *raster_renderer));

	shapes[0]->render();
	shapes[1]->render();

	unique_ptr<Renderer> vector_renderer = make_unique<VectorRenderer>();

	shapes.emplace_back(make_unique<Circle>(12, 15, 5, *vector_renderer));
	shapes.emplace_back(make_unique<Rectangle>(18, 7, 8, 10, *vector_renderer));

	shapes[2]->render();
	shapes[3]->render();
}
