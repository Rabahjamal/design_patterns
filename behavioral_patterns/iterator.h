#ifndef ITERATOR_H
#define ITERATOR_H

#include <string>
#include <vector>
#include <memory>
#include <any>

namespace Iterator
{

struct Message
{
	int message_id;
	std::string message_content;
};

class Iterator
{
public:
	virtual bool has_next() = 0;

	virtual std::any next() = 0;
};

class MessageIterator : public Iterator
{
	size_t current_pos = 0;
	std::vector<Message> messages;
public:
	MessageIterator(const std::vector<Message>& messages)
	{
		this->messages = messages;
	}

	bool has_next()
	{
		return current_pos < messages.size();
	}

	std::any next()
	{
		Message msg = messages[current_pos];
		current_pos++;

		return msg;
	}
};

class Collection
{
public:
	virtual Iterator* create_iterator() = 0;
};

class MessageCollection : public Collection
{
	std::vector<Message> messages;
public:

	void add_message(const Message& msg)
	{
		messages.emplace_back(msg);
	}

	Iterator* create_iterator()
	{
		return new MessageIterator(messages);
	}
};

} // namespace Iterator

#endif // ITERATOR_H
