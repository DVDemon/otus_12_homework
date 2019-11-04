#include "session.h"
#include <iostream>
#include <memory>
#include <string>

homework::Session::Session(tcp::socket socket,EventProcessor &prc,size_t sid) : 
socket_(std::move(socket)),processor(prc),session_id(sid){

}

void homework::Session::start(){
    do_read();
}

void homework::Session::do_read(){
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
                            [this, self](boost::system::error_code ec, std::size_t length) {
                                if (!ec)
                                {
                                    processor.add_event(std::string(data_,length),session_id);
                                }
                            });
}
