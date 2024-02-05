#ifndef Connection_H
#define Connection_H

#include <string>
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include <json.hpp>

using namespace boost::asio;
using json = nlohmann::json;

class TCPServer {
public:
    TCPServer(io_service& ioService, short port);
    ~TCPServer();

private:
    io_service& ioService;
    ip::tcp::acceptor acceptor_;
    std::vector<std::thread> thread_pool_;
    bool acceptingConnections;

    void StartAccept();
    void HandleConnection(ip::tcp::socket&& clientSocket);
    void Send(const json& message, ip::tcp::socket&& clientSocket);
    json Receive(ip::tcp::socket&& clientSocket);
};

#endif // Connection_H
