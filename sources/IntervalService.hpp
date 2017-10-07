#include <functional>

#include "AIntervalService.hpp"

class IntervalService : public AIntervalService {
public:
    using Handler = std::function<void(boost::system::error_code const &ec)>;

public:
    IntervalService(boost::asio::io_service &ioService, std::size_t seconds, Handler handler);

private:
    void service(boost::system::error_code const &ec);

private:
    Handler _handler;
};
