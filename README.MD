# PCTP - Parameter Change Testing Program

За каждый тик программа может либо прочитать из params_in.txt, обновить данные и вывести ответ в params_out.txt (если params_in.txt не пуст, а params_out.txt пуст), либо просто обновить данные и записать их params_out.txt. Если программа выбрала одно из двух действий, но не смогла получить доступ к файлам, то она пропускает данный тик и на следующем выбирает заново. У первого варианта больший приоритет.

## Запуск
Скомпилированная программа лежит в х64\Release\PCTP.exe.
Положите ее в любой каталог. При первом запуске программа в своей директории создаст файлы start.txt, config.txt, log.txt, а также папку params с файлами params_in.txt и params_out.txt.

Чтобы выйти из программы в консоли нажмите "q" обязательно в английской раскладке.

## start.txt
Содержит в себе начальные выходные данные программы. Положите в start.txt то, что хотели бы видеть в params_out.txt при запуске программы.

## config.txt
Содержит в себе начальные переменные программы. Пока в файле находятся 2 параметра:
delay=100
print_update_info=1
delay отвечает за задержку между тиками программы в миллисекундах.
print_update_info отвечате за вывод в консоль информации про обновление параметров в params_out.txt (не работает, если в данный тик был прочитан params_in.txt).

## log.txt
Содержит логи программы во время работы, некоторые логи дублируются в консоль.


# Внутренее устройство программы

Программы использует стандратные библиотеки Windows, в частности, для работы с файлами используется <fileapi.h>.


## Хранение данных
Данные храняться в объекте map<string, double>. В качестве ключа был выбран тип string, так как у него есть уже написанная функция сравнения объектов. Большинство функций для работы с данными написаны под map<string, double>.

Дискрипторы всех файлов хранятся в виде структур HANDLE из <windows.h>.


## Описание функций

### void print_all_data(std::map<std::string, double>& data)
Выводит всю информацию из data в консоль.

### void chararr_push_in_data(char* line, int size_of_line, std::map<std::string, double>& data)
Переносит из массива char* line информацию в data.

### void change_data(std::map<std::string, double>& data)
Отвечает за обновление данных в программе. Сейчас просто прибавляет 1 к значению первого ключа в data.

### void get_data_from_startfile(std::string path, std::map<std::string, double>& data, HANDLE& logfile)
Вызывается 1 раз при запуске программы для заполнения data данными из start.txt. Если start.txt не существует, то создает его и заполняет data и файл следующими значениями:
SomeParams=0.000000
testParams=0.000001

### void get_data_from_config(std::string path, int& delay, bool& print_update_info, HANDLE& logfile)
Вызывается 1 раз при запуске программы для получения значений переменных. Если config.txt  не существует, то ставит delay=100, print_update_info=1, создает и заполняет файл следующими значениями:
delay=100
print_update_info=1

### void logging(HANDLE& logfile, std::string info)
Выполняет логгирование в log.txt.

### bool read_data_from_infile(HANDLE& infile, HANDLE& logfile, std::map<std::string, double>& data, bool with_clear = false)
Читает данные из infile в data, если происходят ошибки, то логгирует их. Возвращает 1 если успешно прочитаны данные, иначе 0. Если поставить with_clear = true, то перед чтением очищает data.

### bool print_data_in_outfile(HANDLE& outfile, HANDLE& logfile, std::map<std::string, double>& data)
Записывает данные из data в outfile, если происходят ошибки, то логгирует их. Возвращает 1 если успешно записаны данные, иначе 0.

### char* data_in_chararr(std::map<std::string, double>& data)
Конверстирует информацию из data в char* и возвращает указатель на созданный массив.

### void clear_file(HANDLE& handle)
Очищает файл из дискриптора handle.

### void unlock_both_files(HANDLE& infile, HANDLE& outfile)
Разблокирует файлы из дискрипторов infile и outfile.

### bool file_empty(HANDLE& handle)
Возвращает 1 если файл из дискриптора handle пуст, иначе 0.

### bool lock_both_files(HANDLE& infile, HANDLE& outfile)
Блокирует файлы из дискрипторов infile и outfile. Возращает 1 если оба успешно заблокированны, иначе 0.

### std::string get_path_dir(char* full_path)
По полному пути к PCTP.exe возращает string, содержащий путь к директории, в которой находится исполняемый файл.

### HANDLE open_file(std::string path)
Возращает дискриптор файла с путем path, если получить дискриптор файла не удалось, то останавливает всю программу.


















