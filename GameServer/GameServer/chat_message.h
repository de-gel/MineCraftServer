//
// chat_message.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>


//一个简单的消息结构。
class chat_message
{
public:
	enum { header_length = 4 };
	enum { max_body_length = 512 };

	chat_message()
		: body_length_(0)
	{
	}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}

	bool decode_header()
	{
		using namespace std; // For strncat and atoi.
		char header[header_length + 1] = "";
		strncat(header, data_, header_length);
		body_length_ = atoi(header);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}

		printf("decode_header success ,the head is [%s],length is [%d]", header, body_length_);

		return true;
	}

	void encode_header()
	{
		using namespace std; // For sprintf and memcpy.
		char header[header_length + 1] = "";
		//将body的长度格式化成4个字节
		sprintf(header, "%4d", static_cast<int>(body_length_));
		//4字节拷贝到data_结构中
		memcpy(data_, header, header_length);
	}

private:
	//消息体结构 4字节头， 512字节消息体
	char data_[header_length + max_body_length];
	size_t body_length_;
};




#endif // CHAT_MESSAGE_HPP