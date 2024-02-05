#include <iostream>
#include "Connection.h"
#include "ParseJsonMesssge.h"

TCPServer::TCPServer(io_service& ioService, short port)
    : ioService(ioService),
      acceptor_(ioService, ip::tcp::endpoint(ip::tcp::v4(), port)),
      acceptingConnections(true) {
    	StartAccept();
}	


TCPServer::~TCPServer() {
    acceptingConnections = false;
    acceptor_.close();
    ioService.stop();

    for (auto& thread : thread_pool_) {
        thread.join();
    }
}

void TCPServer::StartAccept() {
    std::cout << "Server listening \n";
    if (!acceptingConnections) {
        return;
    }

    auto clientSocket = std::make_shared<ip::tcp::socket>(ioService);
    acceptor_.async_accept(*clientSocket, [this, clientSocket](const boost::system::error_code& ec) {
        if (!ec) {
            std::cout << "New Client Connected \n";

            // Use the thread pool to handle the connection
            thread_pool_.emplace_back([this, clientSocket]() {
                HandleConnection(std::move(*clientSocket));
            });
        } else {
            std::cerr << "Error accepting connection: " << ec.message() << "\n";
        }

        // Continue accepting new connections
        StartAccept();
    });
}

void TCPServer::HandleConnection(ip::tcp::socket&& clientSocket) {
    try {
        while (true) {
            json message = Receive(std::move(clientSocket));
            json responseMessage;
            if(message.empty()){
                std::cout <<std::endl << "message is empty" <<std::endl;
                responseMessage["Response"] = "message is empty";
                Send(responseMessage, std::move(clientSocket));
                continue;
            }
            std::string action;
            try{
                action = message["Action"];
            }
            catch (const json::exception& e){

                std::cout << e.what() << '\n';
                std::string error = e.what();
                responseMessage["Response"] = error;
                Send(responseMessage, std::move(clientSocket));
                continue;
            }
            if (action == "close") {
                std::cerr <<std::endl << "Client closed the connection.\n";
                break;
            }
            // Process the received JSON message
            responseMessage = processJsonMessage(message);
            Send(responseMessage, std::move(clientSocket));
        }
    } catch (std::exception& e) {
        std::cerr << "Exception in connection handler: " << e.what() << "\n";
    }

    clientSocket.close();
}

void TCPServer::Send(const json& message, ip::tcp::socket&& clientSocket) {
    boost::asio::write(clientSocket, boost::asio::buffer(message.dump() + "\n"));
}

json TCPServer::Receive(ip::tcp::socket&& clientSocket) {
    try {
        boost::asio::streambuf buffer;
        boost::asio::read_until(clientSocket, buffer, '\n');
        std::string messageStr = boost::asio::buffer_cast<const char*>(buffer.data());
        return json::parse(messageStr);
    } catch (const boost::system::system_error& e) {
        return json(); // or any appropriate value indicating an error
    }
}

