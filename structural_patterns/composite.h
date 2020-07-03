#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>

namespace Composite
{

class Data
{
public:
	Data() {}

	virtual void copy() = 0;

	virtual ~Data()
	{}
};

class Folder : public Data
{
	std::string name;
	std::vector<Data*> folder;
public:
	Folder() = default;

	Folder(const std::string& name)
	{
		this->name = name;
	}

	void add(Data* data)
	{
		folder.emplace_back(data);
	}

	virtual void copy() override
	{
		std::cout << "Copy Folder: " << name << std::endl;
		for(const auto& data : folder)
		{
			data->copy();
		}
	}

	~Folder()
	{
		std::cout << "Destroy Folder: " << name << std::endl;
	}
};

class File : public Data
{
	std::string name;
public:
	File() = default;

	File(const std::string& name)
	{
		this->name = name;
	}

	virtual void copy() override
	{
		std::cout << "Copy File: " << name << std::endl;
	}

	~File()
	{
		std::cout << "Destroy File: " << name << std::endl;
	}
};

}

#endif // COMPOSITE_H
