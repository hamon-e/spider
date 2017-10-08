#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class AIntervalService {
public:
    AIntervalService(boost::asio::io_service &ioService, std::size_t seconds);

public:
    virtual ~AIntervalService() = default;

public:
    void start();
    void stop();

private:
    void run();
    virtual void service(boost::system::error_code const &ec) = 0;
private:
    bool _started;
    boost::asio::deadline_timer _timer;
    boost::posix_time::seconds _interval;
};
