#ifndef EVENT_PROCESSOR_H
#define EVENT_PROCESSOR_H
#include <deque>
#include <string>
#include <atomic>
#include <mutex>
#include <future>
#include <utility>
#include <memory>
#include <map>
#include "producer.h"

namespace homework{
    /**
     * Обработчик команд
     */
    class EventProcessor{
    private:
        /**
         * Размер блока команд
         */
        std::size_t             bulk;

        /**
         * Синхронизатор для работы с очередью команд
         */
        std::mutex              guard_mutex;

        /**
         * Результат окончания работы цикла обработки сообщений, используем его для корректного завершения потоков
         */
        std::future<void>       loop;

        /**
         * Признак работы цикла обработки сообщений. Атомарный что бы не мучаться с синхронизацией
         */
        std::atomic_bool        running;

        /**
         * Очередь сообщений
         */
        std::deque<std::pair<std::string,size_t>> events;

        /**
         * Запуск обработчика сообщений
         */
        void process();

        /**
         * Завершение обработки очереди команд и остановка обработчика со слиянием потоков
         */
        void stop();

        /**
         * Для одновременной рботы с несколькими сессиями сделаем кеш producer-ов к привязке к сессиям
         */
        std::map<size_t,std::shared_ptr<Producer>> session_cache;

        /**
         * Ленивое созданеи producer-ов/получение их из кеша
         */
        std::shared_ptr<Producer> get_producer(size_t session_id);
    public:
        EventProcessor(std::size_t b);

        /**
         * Добавление сообщения в очередь
         */
        void add_event(std::string,size_t);
        ~EventProcessor();

    };
}
#endif