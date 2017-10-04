#include <boost/asio.hpp>

// #include "UdpClient.hpp"
#include "Client.hpp"
#include <sstream>
int main(int argc, char const *argv[]) {
    boost::asio::io_service ioService;

    if (argc < 3) {
        return 1;
    }

    Client client(ioService, argv[1], argv[2]);
    client.send("hello");
    client.start();

    // UdpClient client(ioService, argv[1], argv[2]);
    // client.send("hello");
    // sleep(1);
    // std::cout << "message" << client.receive() << std::endl;
    ioService.run();
    return 0;
}
