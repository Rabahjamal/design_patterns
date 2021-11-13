#ifndef TEMPLATE_METHOD_H
#define TEMPLATE_METHOD_H

#include <string>
#include <iostream>

namespace TemplateMethod
{

class DataMiner
{
public:
	DataMiner() = default;

	virtual void mine(const std::string& path) final;

	virtual void open_file(const std::string& path) = 0;

	virtual void extract_data() = 0;

	virtual void parse_data() = 0;

	void analyze_data() {
		std::cout << "Data analysis" << std::endl;
	}

	void send_report() {
		std::cout << "Sending the analyzed report" << std::endl;
	}

	virtual void close_file() = 0;
};

void DataMiner::mine(const std::string& path) {
	this->open_file(path);
	this->extract_data();
	this->parse_data();
	this->analyze_data();
	this->send_report();
	this->close_file();
}

class PDFDataMiner : public DataMiner
{
public:
	PDFDataMiner() = default;

	void open_file(const std::string& path) {
		std::cout << "Open pdf file" << std::endl;
	}

	void extract_data() {
		std::cout << "Extract pdf data" << std::endl;
	}

	void parse_data() {
		std::cout << "Parse pdf data" << std::endl;
	}

	void close_file() {
		std::cout << "Close pdf file" << std::endl;
	}
};

class CSVDataMiner : public DataMiner
{
public:
	CSVDataMiner() = default;

	void open_file(const std::string& path) {
		std::cout << "Open CSV file" << std::endl;
	}

	void extract_data() {
		std::cout << "Extract CSV data" << std::endl;
	}

	void parse_data() {
		std::cout << "Parse CSV data" << std::endl;
	}

	void close_file() {
		std::cout << "Close CSV file" << std::endl;
	}
};

class DocxDataMiner : public DataMiner
{
public:
	DocxDataMiner() = default;

	void open_file(const std::string& path) {
		std::cout << "Open Docx file" << std::endl;
	}

	void extract_data() {
		std::cout << "Extract Docx data" << std::endl;
	}

	void parse_data() {
		std::cout << "Parse Docx data" << std::endl;
	}

	void close_file() {
		std::cout << "Close Docx file" << std::endl;
	}
};

}

#endif // TEMPLATE_METHOD_H
