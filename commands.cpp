#include "commands.h"
#include <chrono>

homework::Commands & homework::Commands::operator << (std::string val){
    commands.push_back(val);
    return *this;
}

std::vector<std::string>::const_iterator homework::Commands::begin(){
    return commands.begin();
}

std::vector<std::string>::const_iterator homework::Commands::end(){
    return commands.end();
}
void homework::Commands::set_current_time(){
    std::chrono::time_point<std::chrono::system_clock> now_time = std::chrono::system_clock::now();
    std::time_t epoch_time = std::chrono::system_clock::to_time_t(now_time);
    time = std::to_string(epoch_time);
}

const char*  homework::Commands::get_time(){
    return time.c_str();
}

void homework::Commands::clear(){
    time.clear();
    commands.clear();
}

bool homework::Commands::empty(){
    return commands.empty();
}