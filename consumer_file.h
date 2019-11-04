#ifndef CONSUMER_FILE
#define CONSUMER_FILE

#include "consumer.h"
namespace homework{

    /**
     * Синхронизатор имен файлов. Делаем потокобезопасным.
     * Будет вызываться только из ConsumerFile так что делаем тут.
     */

    struct FileNameSynchronizer{
            static std::string get_unique_file_name(const std::string &time);
    };
    /**
     * Наблюдатель для записи блоков команд в файл.
     */
    class ConsumerFile : public Consumer{
            public:
                void consume(Commands &) override;   
    };
}
#endif