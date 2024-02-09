#include "clientconnection.h"

ClientConnection::ClientConnection(const std::string& server_address, const std::string& server_port)
    : server_address_(server_address), server_port_(server_port),
      io_context_(), socket_(io_context_)
{
    try
    {
        tcp::resolver resolver(io_context_);
        auto endpoints = resolver.resolve(server_address_, server_port_);
        boost::asio::connect(socket_, endpoints);
        std::cout<<"connected"<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void ClientConnection::Send(const json& message) {
    boost::asio::write(socket_, boost::asio::buffer(message.dump() + "\n"));
}

json ClientConnection::Receive() {
    try {
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket_, buffer, '\n');
        std::string messageStr = boost::asio::buffer_cast<const char*>(buffer.data());
        return json::parse(messageStr);
    } catch (const boost::system::system_error& e) {
        return json(); // or any appropriate value indicating an error
    }
}


void ClientConnection::closeConnection()
{
    socket_.close();
}
