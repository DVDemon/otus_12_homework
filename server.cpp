#include "server.h"
#include "session.h"

homework::Server::Server(boost::asio::io_context &io_context, short port,size_t bulk)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), processor(bulk){
    do_accept();
}

void homework::Server::do_accept(){
    static size_t session_id=0;
    size_t sid = ++session_id;
    acceptor_.async_accept(
        [this,sid](boost::system::error_code ec, tcp::socket socket) {
            if (!ec)
            {
                std::make_shared<Session>(std::move(socket),processor,session_id)->start();
            }

            do_accept();
        });
}