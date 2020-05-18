#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <string>
#include <iostream>
#include <mutex>

class Singleton
{

	static std::unique_ptr<Singleton> resource;
	static int number_of_instances;
	static std::once_flag resource_flag;

	Singleton()
	{
		number_of_instances++;
	}
public:

	Singleton(const Singleton& other) = delete;
	void operator=(const Singleton& other) = delete;

	static Singleton* get_resource()
	{

		std::call_once(resource_flag, [&](){resource = std::unique_ptr<Singleton>(new Singleton());});

		return resource.get();
	}

	static void print_number_of_instances()
	{
		std::cout << number_of_instances << std::endl;
	}

	~Singleton()
	{
		std::cout << "Singleton is destructed" << std::endl;
	}
};

std::unique_ptr<Singleton> Singleton::resource = nullptr;
int Singleton::number_of_instances = 0;
std::once_flag Singleton::resource_flag;


#endif // SINGLETON_H
