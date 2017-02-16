***Внимание! Это - зарисовочка, блокнот.***

То что здесь написано - это принципы и примеры, идеи в программировании и постороении софта.
То как он будет строится зависит от всех и каждого членов команды.

Тема
----
- event-driven coding и лямбда-выражения. `std::function` - класс функтор. замыкания, захват переменных
* [`C++11,14`](http://en.cppreference.com/w/) и [ru](http://en.cppreference.com/w/)
- SQL и базы данных. В частности база данных `SQLite`
* кольцевой буфер (ring buffer),
- streams (потоки),
* многопоточность (multi tread),
- hardware abstraction layer,
* [диаграмма классов и UML](https://ru.wikipedia.org/wiki/%D0%94%D0%B8%D0%B0%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B0_%D0%BA%D0%BB%D0%B0%D1%81%D1%81%D0%BE%D0%B2)

Конкрентно
----------
1. Многопоточная среда выполнения. Синхронизация потоков, общие ресурсы. Разграничение. Потоки-работяги (Workers).
2. Микросервис - независимая самостоятельная единица приложения. В нашем случае разделение потоков.
3. Node.js и js в целом - наиболее собитийно-ориентированный язык и фреймворк. Лямбда выражения. Спагетти код. С# тоже хорош.
4. Boost. Надо ли? Кратко: да, иногда. Boost::asio - кроссплатформенный асинхронный сетевой API. Многие фичи из boost попали в С++11,14. 
5. Будут конкретные вопросы по Android HW API и iOS HW API.
8. Рабочее окружение. Проект, система сборки.
6. Юнит-тесты.
6. Дальше в будущее - тесты, надёжности, устойчивости, производительности. Множественные, договременные, автоматизированные 

 


### Event-driven coding

Добавляет *event listener* на событие *receive data*.
```
myConnection.EventOnReceive += [&](const char data[], size_t siz){
            cout<<data<<endl; 
            return 0;
        };
```
Такая запись популярна в `С#`. `C++` не отстаёт.




References
------------
[Modern C++ API for SQLite](https://github.com/aminroosta/sqlite_modern_cpp) - 
красивая и удобная обёртка вокруг SQLite  

[Lambda expressions](http://en.cppreference.com/w/cpp/language/lambda) (since C++11) - 
Constructs a closure: an unnamed function object capable of capturing variables in scope.  

[RingBuffer-cpp](https://bitbucket.org/qyw/ringbuffer-cpp/src/b6a6460687a7983212fa9e392352e6e5daff0c88/RingBuffer.hpp?at=master&fileviewer=file-view-default) - 
Реализация кольцевого буффера с расширенными возможностями. Один из прошлых коммитов работает под нагрузкой в железе 
уже несколько лет. Требуются расширение до event-driven и экранирование некоторых действий в многопоточной среде.  

[Circular buffer](https://en.wikipedia.org/wiki/Circular_buffer). A circular buffer, circular queue, cyclic buffer or ring buffer is a data structure ...



Tools
-----
[TeamViewer QuickJoin](https://www.teamviewer.com/en/download) для просмотра презентации 

[PlantUML integration
 for IntelliJ IDEA](https://plugins.jetbrains.com/idea/plugin/7017-plantuml-integration)
установить через `settings->plugins`
