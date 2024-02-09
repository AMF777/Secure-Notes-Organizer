#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <boost/asio.hpp>
#include <iostream>
#include "json.hpp"
using boost::asio::ip::tcp;
using json = nlohmann::json;

class ClientConnection
{
public:
    ClientConnection(const std::string& server_address, const std::string& server_port);
    void Send(const json& message);
    json Receive();
    void closeConnection();

private:
    std::string server_address_;
    std::string server_port_;
    boost::asio::io_context io_context_;
    tcp::socket socket_;
};

#endif // CLIENTCONNECTION_H
