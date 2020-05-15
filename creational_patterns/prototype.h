#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace Prototype
{

class Shape
{
	std::string color;
public:
	Shape() = default;

	Shape(const std::string& color) : color(color) {}

	Shape(const Shape& shape)
	{
		this->color = shape.color;
	}

	std::string get_color()
	{
		return color;
	}

	virtual std::unique_ptr<Shape> clone() const = 0;

	virtual ~Shape() {}
};

class Rectangle : public Shape
{
	int width;
	int height;
public:
	Rectangle(int w, int h, const std::string& color) : Shape (color), width(w), height(h)  {}

	Rectangle(const Rectangle& rect) : Shape (rect)
	{
		this->width = rect.width;
		this->height = rect.height;
	}

	std::unique_ptr<Shape> clone() const
	{
		return std::make_unique<Rectangle>(*this);
	}
};

class Circle : public Shape
{
	int radius;
public:
	Circle(int r, const std::string& color) : Shape (color), radius(r) {}

	Circle(const Circle& circle) : Shape(circle)
	{
		this->radius = circle.radius;
	}

	std::unique_ptr<Shape> clone() const
	{
		return std::make_unique<Circle>(*this);
	}
};

class ShapesRegistry
{
	std::vector<std::unique_ptr<Shape>> shapes;
public:
	ShapesRegistry() {}

	ShapesRegistry(const ShapesRegistry& shape_registry)
	{
		for(const auto& shape : shape_registry.shapes)
		{
			this->shapes.emplace_back(shape->clone());
		}
	}

	void add_shape(const Shape& shape)
	{
		shapes.emplace_back(shape.clone());
	}

	void print()
	{
		for(const auto& shape : shapes)
		{
			std::cout << shape->get_color() << std::endl;
		}
	}
};

} // namespace Prototype

#endif // PROTOTYPE_H
