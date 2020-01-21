# otus_12_homework
# Условие
Основная цель переработать Задание 11 так, чтобы ввод данных
осуществлялся по сети.
Необходимо разработать асинхронный сервер, работающий с протоколом
аналогичным консоли, принимающий построчно команды. Дальнейшая
обработка остается без изменений - вывод на консоль и в файлы.
В качестве библиотеки сетевого взаимодействия можно использовать
boost.asio (можно использовать любую предоставляющую асинхронные
возможности).
Поскольку не предполагается отправка данных основное взаимодействие
будет вокруг методов async_read и async_accept.
Порядок запуска:

# bulk_server <port> <bulk_size>

где

• port – номер tcp порта для входящих соединений. Соединения должны
обслуживаться с произвольных интерфейсов.

• bulk_size – уже знакомый размер блока команд.

Опционально взять за основу вместо однопоточной версии из Задания 7
многопоточную реализацию из Задания 10.
Не должно быть искусственных ограничений на количество одновременно
подключенных клиентов. Команды полученные из разных соединений
должны смешиваться между собой, команды окружённые { и }
обрабатываются без смешивания.

Запуск команд:

# bulk_server 9000 3

и

# seq 0 9 | nc localhost 9000

(что означает формирование 10 строк с числами от 0 до 9 на каждой
строке и отправкой их по сети на локальный порт 9000) должны привести
к появлению в консоли:
bulk: 0, 1, 2

bulk: 3, 4, 5

bulk: 6, 7, 8

bulk: 9