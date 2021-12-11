Долгосрочное домашнее задание (игра "Шашки")

Задание
Цель: Разработать приложение для игры в "Шашки".
Описание задания:

Приложение должно быть построено по клиент-серверной архитектуре.
Клиентская часть состоит из двух модулей: отрисовка событий, связанных с графическими объектами, и взаимодействие с сервером.
Серверная часть должна быть реализована с помощью предоставленного базового класса многопоточного TCP-сервера

Данные должны передаваться в формате json. Структуру пакета определяет команда разработчиков.


Клиентская и серверная части
Далее перечислены основные пункты задания на разработку приложения:
Графическая часть:

Отрисовка доски и фигур на экране
Выделение фигуры(рамки вокруг фигуру) после нажатия на неё
Выделение доступных клеток для совершения хода(реализация одного из правил игры)
Перемещения фигур на доступные для хода клетки
Удаление фигуры с доски после успешного хода противника(реализация одного из правил игры)
Реализация фигуры "Дамка"

Клиентская часть:

Создание отдельного потока взаимодейсвия с сервером и обработка его ответов(накапливание в очереди объектов для чтения, реализация потоко безопасной очереди на основе queue библиотеки stl)
Отправка запроса на создание игры по сети и обработка ответа
Отправка событий перемещения фигур противнику и обработка ответных событий
Реализация алгоритма определения конца игры
Запрос статистики своих игр с сервера и её визуализация
Восстановление игры при переподключении

Серверная часть:

Разработка базы данных(таблицы,связи между таблицами). Реализация функций создания таблиц, вставки данных, удаления данных и поиска данных
Регистрация пользователя при первом подключении и добавление в базу данных зарегистрированных пользователей
Хранение списка текущих подключений и отслеживание состояния подключения пользователя
Реализация алгоритма создания игры между пользователями и хранение списка текущих игр
Сохранение результатов игры в базу данных
Восстановление игры при потере соединения одним из пользователей(задержку установить в 20 секунд)


Индивидуальные задания
Каждому участнику команды будет необходимо выполнить по 6 заданий.
Первый участник команды выполняет следующие задания:

Отрисовка доски и фигур на экране (графическая)
Регистрация пользователя при первом подключении и добавление в базу данных зарегистрированных пользователей (серверная)
Перемещения фигур на доступные для хода клетки (графическая)
Отправка событий перемещения фигур противнику и обработка ответных событий (клиентская)
Сохранение результатов игры в базу данных (серверная)
Восстановление игры при переподключении (клиентская)

Второй участник команды выполняет следующие задания:

Создание отдельного потока взаимодейсвия с сервером и обработка его ответов(накапливание в очереди объектов для чтения, реализация потокобезопасной очереди на основе queue библиотеки stl) (клиентская)
Выделение фигуры(рамки вокруг фигуру) после нажатия на неё (графическая)
Хранение списка текущих подключений и отслеживание состояния подключения пользователя (серверная)
Реализация алгоритма определения конца игры (клиентская)
Удаление фигуры с доски после успешного хода противника(реализация одного из правил игры) (графическая)
Восстановление игры при потере соединения одним из пользователей(задержку установить в 20 секунд) (серверная)

Третий участник команды выполняет следующие задания:

Разработка базы данных(таблицы,связи между таблицами). Реализация функций создания таблиц, вставки данных, удаления данных и поиска данных (серверная)
Выделение доступных клеток для совершения хода(реализация одного из правил игры) (графическая)
Реализация алгоритма создания игры между пользователями, перенаправления данных(во время игры сервер выступает посредником между пользователями) и хранение списка текущих игр (серверная)
Отправка запроса на создание игры по сети и обработка ответа (клиентская)
Запрос статистики своих игр с сервера и её визуализация (клиентская)
Реализация фигуры "Дамка" (графическая)

Задания на каждом этапе связаны. Выполнение следующего задания начинается только после того, как все участники команды закроют своё задание на текущем этапе.
