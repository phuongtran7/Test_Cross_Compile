#pragma once
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include "fmt/format.h"
#include <thread>
#include <mutex>
#include "flatbuffers/flexbuffers.h"

using boost::asio::ip::udp;

class SocketHelper
{
private:
	struct InData
	{
		float AoA;
	};

	boost::asio::io_context io_context_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint remote_endpoint_;
	unsigned char data_[50]{};
	std::thread io_thread;
	std::mutex mutex_;
	float angle_of_attack_;
public:
	SocketHelper(unsigned short port) :
		io_context_(),
		socket_(io_context_, udp::endpoint(udp::v4(), port)),
		mutex_{},
		angle_of_attack_{}
	{
		// Prevent io_context from returning when there is no more work
		// This is nessesary if the run() is called from the background thread before the async process is started
		boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard = boost::asio::make_work_guard(io_context_);

		io_thread = std::thread([this]
			{
				io_context_.run();
			});

		StartReceive();
	}

	~SocketHelper() {
		shutdown();
	}

	float Get_AoA() {
		std::scoped_lock lock(mutex_);
		return angle_of_attack_;
	}

private:
	void StartReceive()
	{
		socket_.async_receive_from(boost::asio::buffer(data_), remote_endpoint_,
			boost::bind(&SocketHelper::HandleReceive, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}

	void shutdown() {
		if (!io_context_.stopped()) {
			socket_.shutdown(udp::socket::shutdown_both);
			socket_.close();
			io_context_.stop();
			if (io_thread.joinable()) {
				io_thread.join();
			}
		}
	}

	void HandleReceive(const boost::system::error_code& error, std::size_t bytes_recvd)
	{
		if (!error)
		{
			std::scoped_lock lock(mutex_);
			//fmt::print("Received: {} bytes.\n", bytes_recvd);
			const auto recieved = flexbuffers::GetRoot(data_, bytes_recvd).AsFloat();
			angle_of_attack_ = recieved;
			StartReceive();
		}
		else {
			fmt::print("{}", error.message());
		}
	}
};