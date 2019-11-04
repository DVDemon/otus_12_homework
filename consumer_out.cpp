#include "consumer_out.h"

homework::ConsumerOut::ConsumerOut(std::ostream &stream): output_stream(stream){

}

void homework::ConsumerOut::consume(Commands& cmd){
    auto it = cmd.begin();
    if(it!=cmd.end()) {
        output_stream << "bulk: ";
        output_stream << *it;
        ++it;
    }
    for(;it!=cmd.end();++it)
        output_stream  << ", " << *it;
    output_stream << std::endl;
}