#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

#include <iostream>
#include <memory>

namespace AbstractFactory
{

class Button
{
public:
	Button() {}

	virtual void render() = 0;

	virtual ~Button() {};
};

class WinButton : public Button
{
public:
	WinButton() {}

	void render()
	{
		std::cout << "Windows Button" << std::endl;
	}
};

class LinuxButton : public Button
{
public:
	void render()
	{
		std::cout << "Linux Button" << std::endl;
	}
};

class Checkbox
{
public:
	virtual void render() = 0;

	virtual ~Checkbox() {};
};

class WinCheckbox : public Checkbox
{
public:

	void render()
	{
		std::cout << "Windows Checkbox" << std::endl;
	}
};

class LinuxCheckbox : public Checkbox
{
public:

	void render()
	{
		std::cout << "Linux Checkbox" << std::endl;
	}
};

class GUIFactory
{
public:
	virtual std::unique_ptr<Button> create_button() const = 0;

	virtual std::unique_ptr<Checkbox> create_checkbox() const = 0;

	virtual ~GUIFactory() {};
};

class WinFactory : public GUIFactory
{
public:

	std::unique_ptr<Button> create_button() const
	{
		return std::make_unique<WinButton>();
	}

	std::unique_ptr<Checkbox> create_checkbox() const
	{
		return std::make_unique<WinCheckbox>();
	}
};

class LinuxFactory : public GUIFactory
{
public:
	std::unique_ptr<Button> create_button() const
	{
		return std::make_unique<LinuxButton>();
	}

	std::unique_ptr<Checkbox> create_checkbox() const
	{
		return std::make_unique<LinuxCheckbox>();
	}
};

void create_ui(const GUIFactory& factory)
{
	std::unique_ptr<Button> button = factory.create_button();
	std::unique_ptr<Checkbox> checkbox = factory.create_checkbox();

	button->render();
	checkbox->render();
}
} // AbstractFactory namespace
#endif // ABSTRACT_FACTORY_H
