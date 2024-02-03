#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <string>
#include <boost/asio.hpp>
#include <json.hpp>

using namespace boost::asio;
using json = nlohmann::json;


class TCPClient {
public:
    TCPClient(io_service& ioService, const std::string& serverIP, short port);
	explicit TCPClient(ip::tcp::socket socket);

    void Connect();
    void Send(const json& message);
    json Receive();
    void CloseSocket();

private:
    ip::tcp::socket socket_;
    ip::tcp::endpoint endpoint_;
};

#endif // USER_CONTROLLER_H
