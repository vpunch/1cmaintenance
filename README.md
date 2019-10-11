# Регулярное обслуживание баз данных 1C

Используйте удобную, кроссплатформенную программу с графическим пользовательским интерфейсом _1CMaintenance_, чтобы автоматизировать процесс обслуживания ваших баз данных.
При желании, вы можете воспользоваться набором сценариев в каталоге `scripts`.

## Поддерживаемые версии 1С

- 8.3.15

## Установка

### Windows

Имя пользователя должно быть на английском, иначе возникнут проблемы с кодировкой во время сборки.

- Установите [MSYS2](https://www.msys2.org/).

- В среде _MSYS2 MSYS_ выполните `pacman -S git mingw-w64-i686-cmake mingw-w64-i686-gdb mingw-w64-i686-qt mingw-w64-i686-qt-creator`, затем получите исходный код проекта командой `git clone`.

- Добавьте `mingw32\bin` в `PATH`, чтобы _IDE_ смогла определить необходимые инструменты для сборки.

- Запустите _qtcreator_ из _cmd_ или добавьте ярлык на рабочий стол.

- Перейдите в `Help -> About Plugins...` и отключите плагины _ClangTools_ и _ClangCodeModel_.

- Откройте проект и укажите путь к `CMakeLists.txt`.

- Соберите проект.

## Почему вам не нужно использовать Обновлятор

Это стоит безопасности. 
_Обновлятор_ является закрытым программным обеспечением.
Это значит, что вы не имеете доступ к его исходному коду и не можете быть уверенным, что программа не делает ничего нежелательного для вас.
Вам остается только верить разработчику на слово, что ваши данные скрытно не передаются на сторонние сервера.

Это стоит денег.
_Обновлятор_ - не бесплатная программа. 
Бесплатное использование имеет множество неприятных ограничений.

Перегруженный интерфейс.
Пользователю тяжело интуитивно разобраться в программе.

_Обновлятор_ не поддерживается в GNU/Linux системах.
