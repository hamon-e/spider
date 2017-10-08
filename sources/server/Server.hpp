#include "APacketServer.hpp"
#include "ServerCrypt.hpp"

class Server : public APacketServer {
public:
    Server(boost::asio::io_service &ioService, int port);

public:
    void send(std::string const &data,
              boost::asio::ip::udp::endpoint &clientEndpoint,
              std::string const &id,
              std::size_t size = Packet::defaultSize,
              bool force = false);
    void send(std::string const &data,
              boost::asio::ip::udp::endpoint &clientEndpoint,
              std::size_t size = Packet::defaultSize,
              bool force = false);
    void send(std::string const &data,
	      std::string const &cookie,
              std::size_t size = Packet::defaultSize,
              bool force = false);

private:
    bool requestCheck(boost::system::error_code &ec, std::string &req, boost::asio::ip::udp::endpoint &clientEndpoint);
    void packetHandler(Packet &packet);
    virtual void encryptor(Packet &packet);
    virtual void decryptor(Packet &packet);
    virtual bool isIgnited(boost::property_tree::ptree const &packet, boost::asio::ip::udp::endpoint const &clientEndpoint) const;

private:
    ServerCrypt _crypt;
};
