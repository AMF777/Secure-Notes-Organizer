#include <iostream>
#include "userController.h"

TCPClient::TCPClient(io_service& ioService, const std::string& serverIP, short port)
    : socket_(ioService) {
    endpoint_ = ip::tcp::endpoint(ip::address::from_string(serverIP), port);
    Connect();
}

TCPClient::TCPClient(ip::tcp::socket socket) : socket_(std::move(socket)) {
	
}

void TCPClient::Connect() {
    socket_.connect(endpoint_);
}

void TCPClient::Send(const json& message) {
    std::string messageStr = message.dump();
    boost::asio::write(socket_, buffer(messageStr + "\n"));
}

json TCPClient::Receive() {
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket_, buffer, '\n');
    std::string messageStr = boost::asio::buffer_cast<const char*>(buffer.data());
    return json::parse(messageStr);
}

void TCPClient::CloseSocket() {
    if (socket_.is_open()) {
        socket_.close();
    }
}
