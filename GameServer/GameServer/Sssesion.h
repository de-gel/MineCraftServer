#pragma once


#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "chat_message.h"

using boost::asio::ip::tcp;

//----------------------------------------------------------------------
//ssesion��
//�̳�enable_shared_from_this,�������ü���
class session : public boost::enable_shared_from_this<session>
{
public:
	session(boost::asio::io_service& io_service)
		: socket_(io_service)
	{
		memset(data_, 0, max_length);
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	void start()
	{

		//����data���棬һ�������ݷ��͹�����ֱ�ӵ���handle_read
		socket_.async_read_some(boost::asio::buffer(data_, max_length),
			boost::bind(&session::handle_read, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
		
		printf("start the data is [%s]\n", data_);
	}


	void send(const char* data)
	{
		chat_message msg;
		msg.body_length(strlen(data));
		memcpy(msg.body(), data, msg.body_length());
		msg.encode_header();

		socket_.async_send(boost::asio::buffer(msg.data(), msg.length()),
			boost::bind(&session::handle_send, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

	//void async_write_some(char* data)
	//{
	//	boost::asio::async_write(socket_,
	//		boost::asio::buffer(data,
	//		strlen(data)),
	//		boost::bind(&session::handle_write, this,
	//		boost::asio::placeholders::error));
	//}



private:
	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			//handler_read�ȴ���ָ��ָ���ֽ�data_�ܳ��ȵĶ�ȡ��
			//Ȼ��bytes_transferred�ֽ�д��ʣ�����ݵ�data_
			//����handle_write
			printf("handle_read the data is [%s]��byte transferd is [%d]\n", data_, bytes_transferred);
			boost::asio::async_write(socket_,
				boost::asio::buffer(data_, bytes_transferred),
				boost::bind(&session::handle_write, this,
				boost::asio::placeholders::error));
		}
		else
		{
			delete this;
		}
	}

	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			//�ٴζ�ȡdata_������
			printf("handle_write the data is [%s]\n", data_);
			socket_.async_read_some(boost::asio::buffer(data_, max_length),
				boost::bind(&session::handle_read, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			delete this;
		}
	}

	void handle_send(const boost::system::error_code& error, size_t bytes_transferred)
	{
		if (!error)
		{
			//�ٴζ�ȡdata_������
			printf("handle_send the data is [%d]\n", bytes_transferred);
			//socket_.async_read_some(boost::asio::buffer(data_, max_length),
			//	boost::bind(&session::handle_read, this,
			//	boost::asio::placeholders::error,
			//	boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			delete this;
		}
	}

	tcp::socket socket_;
	enum { max_length = 10 };
	char data_[max_length];
};


typedef boost::shared_ptr<session> chat_session_ptr;

//----------------------------------------------------------------------
