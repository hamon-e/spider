#include "AIntervalService.hpp"

AIntervalService::AIntervalService(boost::asio::io_service &ioService, std::size_t seconds)
        : _started(false), _timer(ioService), _interval(seconds)
{}

void AIntervalService::start() {
  if (this->_started) {
    return ;
  }
  this->_started = true;
  this->run();
}

void AIntervalService::run() {
  this->_timer.expires_from_now(this->_interval);
  this->_timer.async_wait([this](boost::system::error_code const &ec) {
      this->service(ec);
      this->run();
  });
}

void AIntervalService::stop() {
  this->_started = false;
  if (this->_started) {
    this->_timer.cancel();
  }
}
