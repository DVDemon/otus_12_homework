#include "producer.h"
#include "commands.h"

homework::Producer::Producer(size_t size) : bulk_size(size){
}

void homework::Producer::produce(std::string str){
 
        if(str.find('{')!= std::string::npos) {
            if(state.braces==0){
                notify_bulk();
            }
            state.braces++;
        }
        else
        if(str.find('}')!= std::string::npos) {
            state.braces--;
            if(state.braces==0) notify_bulk();
        }
        else{
            if(state.count==0) next_command.set_current_time();
            state.count ++;
            next_command << str; 
        }

        if(state.count>=bulk_size){
            if(state.braces==0)
                notify_bulk();
        }
    
}
void homework::Producer::add_customer(homework::Consumer* c){
    consumers.push_back(c);
}
void homework::Producer::notify_bulk(){
    if(state.braces==0)
    if(!next_command.empty()){
        for(auto c: consumers) c->consume(next_command);
        next_command.clear();
        state.count = 0;       
    }

}

void homework::Producer::flush(){
    notify_bulk();
}

homework::Producer::~Producer(){
    consumers.clear();
}