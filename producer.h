#ifndef PRODUCER
#define PRODUCER

#include <vector>
#include <memory>
#include <string>


#include "consumer.h"

namespace homework{

    /**
     * Класс для обработки команд и их группировки в блоки.
     */
    class Producer{
        private:
            /**
             * Текущее состояние обработки. Нам интересна глубина вложенности скобок и количество команд в блоке.
             */
            struct State{
                int braces{0};
                size_t count{0};
             };
            //Текущее состояние обработки команд
            State    state;
            // Максимальное количество команд в блоке
            size_t   bulk_size;
            // Текущий блок команд
            Commands next_command;
            // Ссылки на наблюдателей
            std::vector<Consumer*> consumers;
            // Метод для уведомления наблюдателей
            void notify_bulk();
        public:
            Producer(size_t size);
            // Подписать еще одного наблюдателя
            void add_customer(Consumer*);
            // Обработать еще одну команду
            void produce(std::string str);
            // Принудительно дослать все команды в буффере
            void flush();
            ~Producer();

    };
} 

#endif