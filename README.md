ДЗ
=============================

Файлы
------------
1) **main.c** – в нем содержится  `int main()`, с которого начинается работа. В ней идет вход в учетку (поключается в файл *users.csv*) и у кого какие права (если есть права на оба - то предоставляется выбор), в такое меню входит
2) **header.h** – в этом файле записанны:
    * библиотеки, которые использует программа;
    * define'ы / настройки программы;
    * обьявление всех функций из всех файлов и написание их прототипов.
    * обьявление структур хранение информации для книг и студентов.
3) **books.c** – в этом файле содержится вся работа с книгами, которую мне было необходимо реализовать согласно моему варианту
4) **students.c** – в этом файле содержится вся работа со студентами, которую мне было необходимо реализовать согласно моему варианту
5) **functions.c** – в данном файле содератся доп. функцииё
5) **log.c** – в данном файле функции для логирования

#Define'ы
------------
CSV директории

      books_csv           -- default: "csv/books.csv"
                             Директория для файла с книгами
      users_csv           -- default:"csv/users.csv"
                             Директория для файла с пользователями
      student_books_csv   -- default:"csv/student_books.csv"
                             Директория для файла со взятами книгами
      students_csv        -- default:"csv/students.csv"
                             Директория для файла со студентами

Другие директории

      log_file            -- default: "library.log"
                             Директория для лог-файла
      backup_derictory    -- default: "_backups/"
                             Директория, где лежат бэкапы и куда они будут сохраняться
Настройки логирования
      
      log_write           -- default: 1
                             Параметр для включения логирования (1 для вкл, 0 для выкл)
      log_params          -- default: 1
                             Параметр для включения параметров (1 для вкл, 0 для выкл)

Настройки логирования сообщений ("сообщение" для включения, NULL для выключения)

      log_before_start    -- default: "BeforeStart"
                             Сообщение начала старта программы
      log_login           -- default: "StartSystem"
                             Сообщение о входе
      log_login_failed    -- default: "loginFailed"
                             Сообщение о неудачном входе
      log_shutdown        -- default: "ShutdownSystem"
                             Сообщение о выходе
      log_enter_books     -- default: "EnterBooks"
                             Сообщение о входе в систему книг
      log_enter_students  -- default: "EnterStudents"
                             Сообщение о входе в систему студентов
      log_cant_open_file  -- default: "CantOpenFile"
                             Сообщение об отсутсвии файла (в параметрах указан путь файла)
      log_dup_ISBN        -- default: "IsbnDuplication"
                             Сообщение о повторении ISBN книги
      log_EOF_detected    -- default: "EOFDetected"
                             Сообщение о получении от пользователя ввода Ctrl^D или другую EOF комманду
                             
Цветовое оформление консольного вывода + Цветные сообщения

      COLOR_CLEAR         -- "\x1b[0m"
                             Удаление цвета 
      COLOR_RED           -- "\x1b[31m"
                             Цвет: крассный
      COLOR_CYAN          -- "\x1b[36m"
                             Цвет: циан
      COLOR_YELLOW        -- "\x1b[33m"
                             Цвет: желтый
      COLOR_BOLD          -- "\x1b[1m"
                             Жирный текст
      ERROR               -- "[\x1b[1m\x1b[31mERROR\x1b[0m]"
                             Сообщение: Ошибка
      WARNING             -- "[\x1b[1m\x1b[33mWARNING\x1b[0m]"
                             Сообщение: Предупрждение
      INFO                -- "[\x1b[1m\x1b[36mINFO\x1b[0m]"
                             Сообщение: Инфо
            
Функции фалйа "books.c" 
------------
* **Структура хранения книг:**
```c
struct Book{
    unsigned long long ISBN;
    char Author[128];
    char Name[128];
    int  NumAll;
    int  NumUsed;
};
```
* **Вход в меню книг:** в данной функции реализованно загрузка из файла в структуру данных, подсчет строк в `LineCount` и выбор действий
```C
void Books_start(void);
```

* **Выход из меню книг:** в данной функции реализованно сохранение из структуры в файл данных
```C
void Books_exit (struct Book *Books, int LineCount);
```

* **Добавление книг:** в данной функции реализованно добавление книги. Если такой ISBN сущетвует, то пользователю предлагается ввести его заного
```C
struct Book* Books_add(struct Book *Books, int LineCount);
```

* **Удаление книг:** в данной функции реализованно удаление книги. Если эта книга на руках у какого-то студента, программа не дает ее удалить
```C
void Books_delete(struct Book *Books, int LineCount);
```

* **Показ всех книг:** в данной функции реализованн показ всех книг из библиотеки с сортировкий (использован алгоритм [быстрой сортировки](https://ru.wikipedia.org/wiki/Быстрая_сортировка))
```C
void Books_showall(struct Book *Books, int LineCount);
```

* **Поиск книги:** в данной функции реализованн показ всей информации книги. Для поиска нужно знать ISBN
```C
void Books_find(struct Book *Books, int LineCount);
```

* **У каких студентов эта кина:** в данной функции реализованн показ студентов и их информация по определенной киниге (по ISBN), которую они взяли
```C
void Books_onhands(FILE *BookFile, struct Book *Books, int LineCount);
```

Функции фалйа "students.c" 
------------
* **Структура хранения информации студента:**
```c
struct Student{
    char RecBook[10];
    char Name[32];
    char SName[32];
    char OName[32];
    char Faculty[10];
    char Spec[1024];
};
```
* **Вход в меню студента:** в данной функции реализованно загрузка из файла в структуру данных, подсчет строк в `LineCount` и выбор действий
```C
void Students_start(void);
```

* **Выход из меню студента:** в данной функции реализованно сохранение из структуры в файл данных
```C
void Students_exit(struct Student *Students, int LineCount);
```

* **Добавление студента:** в данной функции реализованно добавление студента. Если такая зачетка сущетвует, то пользователю предлагается ввести ее заного
```C
struct Student* Students_add(struct Student *Students, int LineCount);
```

* **Удаление студента:** в данной функции реализованно удаление студента. Если он не сдал все книги, программа не дает его удалить
```C
void Students_delete(struct Student *Students, int LineCount);
```

* **Сделать бэкап файла со студентами:** в данной функции реализованн механизм создание бэкапа и добавление в название файла дату создания
```C
void Students_backup_save(struct Student *Students, int LineCount);
```

* **Востановить из бэкапа информацию студентов:** в данной функции реализованн механизм востановление информации студентов из бэкапа. Так же есть проверка на ввод пути файла, есть 2-я проверка файла вне дериктории бэкапа. Если система не может открыть или найти файл, послбзователю выводит информацию о потециальных бэкап-файлах
```C
struct Student* Students_backup_upload(struct Student *Students, int LineCount, FILE *StudentsFile);
```

* **Поиск студента:** в данной функции реализованн поиск студдента и вывод его инормации
```C
void Students_search(struct Student *Students, int LineCount);
```

* **Показ книг у студента:** в данной функции реализованн показ книг, которые взял студент. Поиск студента осущетсвлется по студ. книжке
```C
void Students_showall(struct Student *Students, int LineCount);
```

Функции фалйа "functions.c" 
------------
* **Аналог функции `scanf("%s")`**
```C
char *scan(char EndSymb);
```

* **Вывод текста - предупрждения**
```C
void p_warn(char text[]);
```

* **Вывод текста - ошибки**
```C
void p_err(char text[]);
```

* **Вывод текста - информации**
```C
void p_info(char text[]);
```

* **Проверка на открытый файл:** открыт ли файл или нет, если нет - то запись в лог-файл об этом с детальной информацией
```C
void check_fopen(FILE *test_file, char filename[]);
```

* **Функция уведомления:** Данная функция позволяет детально уведомить пользовтеля, записать при необходимости информацию в лог-файл и необходимые параметры и/или завершить экстренно работу. Так же есть инфомация [по ошибкам](#EXITcodes)
```C
void notify(char mode[], char text[], int exitcode, char *params, _Bool silent);
```

* **Начальная провека файлов:** Если нет какого то из фалов - программа не запускается, уведомлет пользователя об отсутвиии и записывается информация в лог-файл
```C
void checkfile(void);
```

* **Сортировка - свап-функция:** необходима для *быстрой сортировки*
```C
void swap(struct Book *a, struct Book *b);
```

* **Сортировка - алгоритм быстрой сортировки**
```C
void quick_sort_struct_book_by_isbn(struct Book *Books, int left, int right);
```

Функции фалйа "log.c" 
------------
* **Запись глобальной переменной `_Bool write_log` в файле *log.c***
```C
void write_log_act(_Bool do_write_log);
```

* **Запись глобальной переменной `char User[]` в файле *log.c*** 
```C
void setup_user(char user[]);
```

* **Запись строк в лог-файл:** в данной функции реализованно построчная запись в лог-файл любых записей с параметрами, настроку которых вы можете найти выше выше
```C
void add_log(char activity[], char params[]);
```

Запуск и использование
------------
* **Запуск через make**: make
* **Запуск через компилятор *clang***: clang ./main.c ./books.c ./header.h ./functions.c ./students.c ./log.c -lm; ./a.out; rm ./a.out; clear;
* **Запуск через компилятор *gcc***: gcc ./main.c ./books.c ./header.h ./functions.c ./students.c ./log.c -lm; ./a.out; rm ./a.out; clear;
*Программа предназначена для использования на clang компиляторе. При использовании другого компилятора исправить в Makefile в строке №2 "clang" на свой.*


<a name="EXITcodes">EXIT Коды</a>
------------
* 1-я цифра:
    * 1: from main
    * 2: from books
    * 3: from student
    * 4: from log library
    * 5: from function library
    * 9: from other
* 2-я цифра:
    * 0: critical ???
    * 1: unexpecting logic
    * 2: file access
    * 3: file syntax
    * 3: memory
    * 4: variable
    * 9: unknown

