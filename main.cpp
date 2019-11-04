#include <iostream>
#include <cstdlib>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include "server.h"

using boost::asio::ip::tcp;

bool isPositiveInteger(const std::string&& s){
    return !s.empty() && 
           (std::count_if(s.begin(), s.end(), [](auto a){return (a>='0'&&a<='9');}) == (long)s.size());
}

auto main(int argc,char * argv[]) -> int{
  try
  {
    if(argc>2)
    if(isPositiveInteger(std::string(argv[1])))
    if(isPositiveInteger(std::string(argv[2])))
    {
        int    port_number = atoi(argv[1]);
        size_t bulk_size   = atoi(argv[2]);

        boost::asio::io_context io_context;
        homework::Server server(io_context,port_number,bulk_size);
        io_context.run();
        
        return 1;
    }

    std::cerr << "Usage: bulk_asynk <port> <bulk_size>\n";
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Exception: " << ex.what() << "\n";
  }
  return 0;
}