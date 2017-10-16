#include "IntervalService.hpp"

IntervalService::IntervalService(boost::asio::io_service &ioService, std::size_t seconds, Handler handler)
        : AIntervalService(ioService, seconds), _handler(handler)
{}

void IntervalService::service(boost::system::error_code const &ec) {
  this->_handler(ec);
}
