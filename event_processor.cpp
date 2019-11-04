#include "event_processor.h"

#include "consumer_file.h"
#include "consumer_out.h"

homework::EventProcessor::EventProcessor(std::size_t b) : bulk(b), running(true){
    process();
}

void homework::EventProcessor::add_event(std::string val,size_t session_id){
    std::lock_guard<std::mutex> lock(guard_mutex);
    events.push_back(std::make_pair(val,session_id));
}

std::shared_ptr<homework::Producer> homework::EventProcessor::get_producer(size_t session_id){
    static ConsumerOut consumer_out(std::cout);
    static ConsumerFile consumer_file;
    if(session_cache.find(session_id)==session_cache.end()){
        auto producer = std::make_shared<Producer>(bulk);
        producer->add_customer(&consumer_file);
        producer->add_customer(&consumer_out);
        session_cache[session_id] = producer;
    }

    return session_cache[session_id];
}

void homework::EventProcessor::process(){
    auto procedure = [this](){
/*        Producer producer(this->bulk);
        ConsumerOut consumer_out(std::cout);
        ConsumerFile consumer_file;

        producer.add_customer(&consumer_file);
        producer.add_customer(&consumer_out);*/


        std::string cmd;
        while(running){
            {
                std::lock_guard<std::mutex> lock(this->guard_mutex);
                if(!this->events.empty()){    
                    //std::pair<std::string,size_t> event =   *this->events.begin();
                    std::string s;
                    size_t session_id;
                    std::tie(s,session_id) = *this->events.begin();
                    std::shared_ptr<Producer> producer = get_producer(session_id);
                    this->events.pop_front();

                    // парсим строку
                    std::string delimiter = "\n";
                    size_t pos = 0;
                    std::string token;
                    while ((pos = s.find(delimiter)) != std::string::npos) {
                        token = s.substr(0, pos);
                        if(!token.empty()){
                            producer->produce(token);
                        }
                        s.erase(0, pos + delimiter.length());
                    }

                    if(!s.empty()){
                            producer->produce(s);
                        }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
           
        //producer.flush();
    };

    loop = std::async(procedure);

}

void homework::EventProcessor::stop(){
    bool empty=false;
    do{
       {
           std::lock_guard<std::mutex> lock(this->guard_mutex); 
           empty = events.empty();
       }
       if(!empty) std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }while(!empty);
    running = false;
    loop.wait();
}

homework::EventProcessor::~EventProcessor(){
    stop();
}