#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "event_processor.h"
namespace homework
{
/**
   * Сессия для работы с конкретным клиентом
   */
class Session : public std::enable_shared_from_this<Session>
{
public:
  Session(tcp::socket socket, EventProcessor &prc, size_t session_id);
  /**
   * Старт взаимодействия
   */
  void start();

private:
  /**
   * Считывание данных из потока
   */
  void do_read();

  /**
   * Сокет соединения с клиентом
   */

  tcp::socket socket_;
  /**
   * Обработчик событий
   */
  EventProcessor &processor;
  size_t session_id;
  enum
  {
    max_length = 1024
  };
  char data_[max_length];
};
} // namespace homework

#endif