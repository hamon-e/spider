//
// HttpsRestApi.cpp for cpp_spider in sources/server
//
// Made by Nicolas Goudal
// Login   <nicolas.goudal@epitech.eu>
//
// Started on  Sun Oct 08 18:38:49 2017 Nicolas Goudal
// Last update Mon Oct 09 00:34:48 2017 Nicolas Goudal
//

#include "MongoDB.hpp"
#include "HttpServer.hpp"

int main() {
    MongoDB mongo;
    HttpServer server(&mongo, 1234);

    server.start();

    server.join();

    return 0;
}
