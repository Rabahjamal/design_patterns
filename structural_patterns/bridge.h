#ifndef BRIDGE_H
#define BRIDGE_H

#include <string>
#include <iostream>

namespace Bridge
{

class Renderer
{
public:
	Renderer() {}

	virtual void render_circle(float x, float y, float radius) const = 0;

	virtual void render_rectangle(float x, float y, float width, float height) const = 0;

	virtual ~Renderer() = default;
};

class RasterRenderer : public Renderer
{
public:
	RasterRenderer() {}

	void render_circle(float x, float y, float radius) const
	{
		std::cout << "Raster rendering of a circle at: " << x << ", " << y << " - radius = "
				  << radius << std::endl;
	}

	void render_rectangle(float x, float y, float width, float height) const
	{
		std::cout << "Raster rendering of a rectangle at: " << x << ", " << y <<
					 " - width = " << width << ", height = " << height << std::endl;
	}
};

class VectorRenderer : public Renderer
{
public:
	VectorRenderer() {}

	void render_circle(float x, float y, float radius) const
	{
		std::cout << "Vector rendering of a circle at: " << x << ", " << y << " - radius = "
				  << radius << std::endl;
	}

	void render_rectangle(float x, float y, float width, float height) const
	{
		std::cout << "Vector rendering of a rectangle at: " << x << ", " << y <<
					 " - width = " << width << ", height = " << height << std::endl;
	}
};

class Shape
{
protected:
	const Renderer& m_renderer;
public:
	Shape() = default;

	Shape(const Renderer& renderer) : m_renderer(renderer) {}

	virtual void render() = 0;

	virtual ~Shape() {}
};

class Rectangle : public Shape
{
	float _width;
	float _height;
	float _x;
	float _y;
public:
	Rectangle(float width, float height, float x, float y, const Renderer& renderer) :
		Shape(renderer), _width(width), _height(height), _x(x), _y(y) {}

	void render() override
	{
		m_renderer.render_rectangle(this->_x, this->_y, this->_width, this->_height);
	}

};

class Circle : public Shape
{
	float _radius;
	float _x;
	float _y;
public:
	Circle(int radius, float x, float y, const Renderer& renderer) :
		Shape (renderer), _radius(radius), _x(x), _y(y) {}

	void render() override
	{
		m_renderer.render_circle(this->_x, this->_y, this->_radius);
	}

};
}

#endif // BRIDGE_H
