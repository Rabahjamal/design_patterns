#ifndef DECORATOR_H
#define DECORATOR_H

#include <iostream>
#include <vector>

namespace Decorator
{

class DataSource
{
public:
	DataSource() {}

	virtual void write_data(const std::vector<char>& data) = 0;

	virtual std::vector<char> read_data() = 0;
};

class FileDataSource : public DataSource
{
	std::string file_name;
public:
	FileDataSource(const std::string& file_name) { this->file_name = file_name; }

	void write_data(const std::vector<char>& data) override
	{
		std::cout << "write data to file" << std::endl;
	}

	std::vector<char> read_data() override
	{
		std::cout << "read data from file" << std::endl;
		return std::vector<char>();
	}
};


class DataSourceDecorator : public DataSource
{
	DataSource* data_source;
public:
	DataSourceDecorator(DataSource* data_source) { this->data_source = data_source; }

	void write_data(const std::vector<char>& data) override
	{
		data_source->write_data(data);
	}

	std::vector<char> read_data() override
	{
		return data_source->read_data();
	}
};

class EncryptionDecorator : public DataSourceDecorator
{
public:
	EncryptionDecorator(DataSource* data_source) : DataSourceDecorator(data_source)
	{}

	void write_data(const std::vector<char>& data) override
	{
		std::cout << "encrypt data before writting" << std::endl;
		DataSourceDecorator::write_data(data);
	}

	std::vector<char> read_data() override
	{
		std::vector<char> data = DataSourceDecorator::read_data();
		std::cout << "decrypt data after reading it" << std::endl;
		return data;
	}
};

class CompressionDecorator : public DataSourceDecorator
{
public:
	CompressionDecorator(DataSource* data_source) : DataSourceDecorator(data_source)
	{}

	void write_data(const std::vector<char>& data) override
	{
		std::cout << "compress data before writting" << std::endl;
		DataSourceDecorator::write_data(data);
	}

	std::vector<char> read_data() override
	{
		std::vector<char> data = DataSourceDecorator::read_data();
		std::cout << "decompress data after reading it" << std::endl;
		return data;
	}
};

} // namespace Decorator

#endif // DECORATOR_H
