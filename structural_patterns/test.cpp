#include "adapter.h"
#include "bridge.h"
#include "composite.h"
#include "decorator.h"

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

TEST_CASE("Composite")
{
	using namespace Composite;

	unique_ptr<Folder> folder1 = make_unique<Folder>("home");
	unique_ptr<Folder> folder2 = make_unique<Folder>("rabah");

	unique_ptr<File> file1 = make_unique<File>("file1");
	unique_ptr<File> file2 = make_unique<File>("file2");

	folder1->add(file1.get());
	folder2->add(file2.get());
	folder1->add(folder2.get());

	folder1->copy();
}

TEST_CASE("Decorator")
{
	using namespace Decorator;

	unique_ptr<DataSource> data_source(new FileDataSource("koko.txt"));

	data_source->write_data(vector<char>());

	cout << "------------------------------------------------" << endl;

	unique_ptr<DataSource> enc_decorator(new EncryptionDecorator(data_source.get()));

	enc_decorator->write_data(vector<char>());

	cout << "------------------------------------------------" << endl;

	unique_ptr<DataSource> compress_decorator(new CompressionDecorator(enc_decorator.get()));

	compress_decorator->write_data(vector<char>());

	cout << "------------------------------------------------" << endl;

	compress_decorator->read_data();

	cout << "------------------------------------------------" << endl;

	enc_decorator->read_data();

	cout << "------------------------------------------------" << endl;

	data_source->read_data();


}
