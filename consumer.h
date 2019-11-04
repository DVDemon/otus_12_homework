#ifndef CONSUMER
#define CONSUMER

#include "commands.h"
namespace homework{
    /**
     * Интерфейс для наблюдателей, которые будут получть блок команд и куда-нибудь его писать.
     */
    struct Consumer{
        virtual void consume(Commands &) = 0;
    };
}
#endif