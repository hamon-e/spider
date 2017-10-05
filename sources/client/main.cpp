#include <boost/asio.hpp>

#include "Client.hpp"

int main(int argc, char const *argv[]) {
    boost::asio::io_service ioService;

    if (argc < 3) {
        return 1;
    }

    Client client(ioService, argv[1], argv[2]);
    client.send("Nicolas", "111", "plain_text", "hello");
    client.start();

    ioService.run();
    return 0;
}
