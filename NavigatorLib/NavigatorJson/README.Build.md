NavigatorJson
=====

Сборка
------
Всё на CMake и работает отлично.

### Зависимости
* [`boost`](http://www.boost.org) 1.63 - complex C++ library. This program depends 
only on `filesystem`, `system` and `rexex` modules. This library must be installed
on system level.
* `rapidjson` - header only json serializer/deserializer. The library is already stored in this project.

#### Boost
Если вы под Линуксом - вы счастливчик. Вопрос решается одной коммандой типа:
    
    sudo apt-get install boost-dev

или для Arch Linux

    sudo pacman -S boost

Подробнее подскажет утка или другой поисковик.

##### Boost on Windows
Это может стать довольно неприятной проблемой. Собирать придётся самостоятельно. 
Следуйте [мануалу](http://www.boost.org/doc/libs/1_63_0/more/getting_started/windows.html).
Я здесь оставлю порядок действий в одном своём частном случае, может поможет. 
Рекомендую работать в терминале `git bash` или `MinGW msys` или `Cygwin`.
```
# добавить MinGW/bin в PATH если это ещё не сделано. SETX добавляет перманентно
> setx PATH  %PATH%;C:\devel\mingw-w64\x86_64-6.2.0-posix-seh-rt_v5-rev0\mingw64\bin
# проверить 
> gcc --version
gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 6.2.0
...

> cd /path/to/boost_1_63_0
> ./bootstrap.bat gcc
> ./b2.exe toolset=gcc variant=release install --prefix=/g/devel/lib
# Идем пить кофе. Чтобы ускорить процедуру собирайте только то, что необходимо. 
# Используйте --with-filesystem --with-system --with-regex.

> setx CMAKE_PREFIX_PATH /g/devel/lib  
# CMAKE_PREFIX_PATH также можно установить в CLion или ~/.bash.rc
```
