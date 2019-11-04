#ifndef CONSUMER_OUT
#define CONSUMER_OUT

#include "consumer.h"
#include <string>
#include <iostream>
#include <memory>

namespace homework{
    /**
     * Наблюдатель для вывода команд на экран.
     */
    class ConsumerOut : public Consumer{
        private:
            std::ostream &output_stream;
        public:
            ConsumerOut(std::ostream &stream);
            void consume(Commands &) override;
    };
}
#endif