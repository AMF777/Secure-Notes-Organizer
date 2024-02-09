#include <iostream>
#include "Connection.h"
#include "DataController.h"

int main() {

    io_service ioService;
    short port = 12345;
    try {
        TCPServer server(ioService, port);
        // Run the IO service in the main thread
        ioService.run();
        
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
