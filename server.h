#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
using boost::asio::ip::tcp;
#include "event_processor.h"

namespace homework{
    class Server{
    public:
        Server(boost::asio::io_context &io_context, short port,size_t bulk);
    private:
        void do_accept();
        tcp::acceptor acceptor_;
        EventProcessor processor;
    };
}

#endif