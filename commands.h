#ifndef COMMANDS
#define COMMANDS


#include <string>
#include <vector>

namespace homework{
    /**
     * Класс для хранения блока команд. Он хранит список команд и время появления первой команды.
     */
    class Commands{
        private:
            std::vector<std::string> commands;
            std::string time;
        public:
        /**
         * Сохранение команды в блок.
         */
            Commands & operator << (std::string);
        /**
         * Итератор на первую команду в блоке.
         */
            std::vector<std::string>::const_iterator begin();
        /**
         * Итератор на конец массива команд.
         */
            std::vector<std::string>::const_iterator end();

        /**
         * Запоминаем вермя появления первой команды в блоке.
         */

            void set_current_time();
        /**
         * Получаем время первой команды вблоке.
         */
            const char*  get_time();

        /**
         * Очищаем блок команд.
         */
            void clear();
        /**
         * Проверяем нато, не пустой ли блок.
         */
            bool empty();
    };
}
#endif