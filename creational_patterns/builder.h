#ifndef BUILDER_H
#define BUILDER_H

#include <string>
#include <memory>
#include <iostream>

class Car
{
	std::string m_color;
	std::string m_model;
	int m_seats_number;
	int m_max_speed;

public:
	void set_color(const std::string& color)
	{
		m_color = color;
	}

	void set_model(const std::string& model)
	{
		m_model = model;
	}

	void set_seats_number(int number)
	{
		m_seats_number = number;
	}

	void set_max_speed(int max_speed)
	{
		m_max_speed = max_speed;
	}

	~Car()
	{
		std::cout << "-----------------------Car destructed-----------------------" << std::endl;
	}

};

class Builder
{
public:
	virtual void build_color(const std::string& color) = 0;

	virtual void build_model(const std::string& model) = 0;

	virtual void build_seats(int number) = 0;

	virtual void build_max_speed(int max_speed) = 0;

	virtual void reset() = 0;

	virtual Car get_car() = 0;
};

class ToyotaBuilder : public Builder
{
	std::unique_ptr<Car> toyota_car;
public:

	ToyotaBuilder()
	{
		reset();
	}

	void build_color(const std::string& color)
	{
		toyota_car->set_color(color);
		std::cout << "Building " << color << " Toyota car" << std::endl;
	}

	void build_model(const std::string& model)
	{
		toyota_car->set_model(model);
		std::cout << "Building " << model << " Toyota car" << std::endl;
	}

	void build_seats(int number)
	{
		toyota_car->set_seats_number(number);
		std::cout << "Building Toyota car with " << number << " seats" << std::endl;
	}

	void build_max_speed(int max_speed)
	{
		toyota_car->set_max_speed(max_speed);
		std::cout << "Building Toyota car with " << max_speed << " km/h max speed" << std::endl;
	}

	void reset()
	{
		toyota_car = std::make_unique<Car>();
	}

	Car get_car()
	{
		Car car = *this->toyota_car;
		reset();
		return car;
	}
};

class Director
{
	Builder& m_builder;

public:
	Director(Builder& builder) : m_builder(builder)
	{}

	void change_builder(const Builder& builder)
	{
		m_builder = builder;
	}

	Car create_small_toyota_car()
	{
		m_builder.build_color("grey");
		m_builder.build_model("Camry");
		m_builder.build_seats(5);
		m_builder.build_max_speed(220);
		return m_builder.get_car();
	}
};

#endif // BUILDER_H
