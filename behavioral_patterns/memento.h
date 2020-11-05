#ifndef MEMENTO_H
#define MEMENTO_H

#include <string>
#include <iostream>
#include <memory>

namespace Memento
{

class ArticleMemento
{
	int id;
	std::string title;
	std::string content;
public:
	ArticleMemento(int id, const std::string& title, const std::string& content) :
		id(id), title(title), content(content)
	{}

	int get_id()
	{
		return id;
	}

	std::string get_title()
	{
		return title;
	}

	std::string get_content()
	{
		return content;
	}
};

class Article
{
	int id;
	std::string title;
	std::string content;
public:
	Article(int id, const std::string& title, const std::string& content) :
		id(id), title(title), content(content)
	{}

	void set_title(const std::string& title)
	{
		this->title = title;
	}

	void set_content(const std::string& content)
	{
		this->content = content;
	}

	std::unique_ptr<ArticleMemento> create_memento()
	{
		return std::make_unique<ArticleMemento>(this->id, this->title, this->content);
	}

	void restore(const std::unique_ptr<ArticleMemento>& memento)
	{
		this->id = memento->get_id();
		this->title = memento->get_title();
		this->content = memento->get_content();
	}

	friend std::ostream& operator<<(std::ostream& os, const Article& article);
};

std::ostream& operator<<(std::ostream& os, const Article& article)
{
	os << article.id << "-" << article.title << ": " << article.content << std::endl;
}

}

#endif // MEMENTO_H
