#include "consumer_file.h"
#include <iostream>
#include <fstream>
#include <mutex>

std::string homework::FileNameSynchronizer::get_unique_file_name(const std::string &time){
 static std::mutex mtx;
 std::lock_guard<std::mutex> lock(mtx);
 static std::string last_time{};
 static size_t      counter{};

 if(time!=last_time){
     last_time = time;
     counter   = 0;
     return last_time;
 } else {
     counter++;
     return last_time+std::string("-")+std::to_string(counter);
 }
}

void homework::ConsumerFile::consume(homework::Commands& cmd){
    std::string name=FileNameSynchronizer::get_unique_file_name(cmd.get_time());
    name+=".log";
    std::ofstream out_file(name, std::ofstream::out);
    std::cout << "Write file:" << name << std::endl;
    auto it = cmd.begin();
    if(it!=cmd.end()) {
        out_file << "bulk: ";
        out_file << *it;
        ++it;
    }
    for(;it!=cmd.end();++it)
        out_file  << ", " << *it;
    out_file << std::endl;

    out_file.close();
}