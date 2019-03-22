-> Литература <-
===============

# Что читать?
  * The Unix Programming Environment. Brian W. Kernighan, Rob Pike
  * Advanced Programming in the Unix Environment. W. Richard Stevens

---

-> Опрос #0 <-
==============

 * Кто поставил Linux после прошлой лекции?

---

-> Опрос #1 <-
==============

 * Кто добрался до командной строки после прошлой лекции?

---

-> В прошлых сериях <-
======================

# Operating System
  * [K]ernelspace
  * Syscalls
  * [U]serspace

# Процессы
  * Абстракция, используемая ядром, для выполнения работы
  * Модель монопольного владения ресурсами
  * Credentials
  * IPC
  * Ресурсы
  * Модель памяти
  * Syscalls для работы с процессами: fork, execve, waitpid, kill, exit
  * Zombie, orphan
  * Scheduler

---

-> Сегодня <-
=============

Поговорим о:
  * Железе
  * Файлах и правах доступа
  * Inode
  * Директории и иерархии
  * Устройства как файлы. Все есть файл.
  * Системные вызовы для всего этого
  * Файловые системы и точки монтирования
  * Немного о VFS

---

-> HDD <-
==================================
  * Картинка
  * Достоинства
    - Стоимость
    - Объем
  * Недостатки
    - Время доступа
    - Надежность

---

-> SSD <-
==================================
  * Достоинства
    - Время доступа
    - Надежность
  * Недостатки
    - Надежность
    - Стоимость
    - Объем
  * NVME

---

-> Общие соображения <-
=======================
 * Минимум информации - сектор - 512 байт -> 4096 байт
 * Чтение одного байта - чтение сектора с байтом
 * Запись одного байта - считать один сектор, заменить байт и записать один сектор
 * Аналогия - процессор-память - cacheline

---

-> Интересные числа <-
======================
 * Cycle
 * Main memory reference
 * Read 4K randomly from SSD
 * Read 1 MB sequentially from SSD
 * HDD Disk seek
 * Read 1 MB sequentially from HDD disk

---

-> Интересные числа <-
======================
 * Cycle                                      1     ns
 * Main memory reference                      100   ns
 * Read 4K randomly from SSD                  150   us
 * Read 1 MB sequentially from SSD            1     ms
 * Disk seek                                  10    ms
 * Read 1 MB sequentially from disk           20    ms

---

-> Выводы для HDD <-
============
 * Читать нужно последовательно
 * Обращения к диску следует минимизировать
 * Стоимость доступа сильно дороже передачи данных

---

-> Файл <-
==========

Что такое файл?
  * С точки зрения K: абстракция для данных
  * Последовательность байт
  * Формат не определен
  * Все есть файл
  * Типы файлов:
    - regular
    - directory
    - symlink
    - socket, fifo
    - character device, block device

---

-> Директории <-
================
 * Содержит имена находящихся в нем файлов
 * . и ..
 * Формирование дерева
 * filename vs pathname
 * Права:
  - eXecute - search
  - read - directory listing
  - write - changing directory(delete or create)
  - Темные директории
 * sticky bit
   - Удалять может тот, кто имеет право записи в директорию
   - Удалять может только root или владелец файла или владелец директории
   - /tmp
 * SGID
   - Группа создаваемого файла

---

-> Inode <-
===========
  * Номер
  * Индексный дескриптор, хранит служебную информацию
  * Атрибуты
    - Размер
    - atime, ctime, mtime
    - refcounting
    - Не содержит имени - разные пути
  * SUID, SGID: change User or Group
    - Безопасность
  * Права:
    - owner, group, other
    - read, write, execute
    - root может все
  * Inode корневой файловой системы фиксирован - 2
  * Vnode

---

-> Иерархия <-
==============
 * /
   - bin/
   - dev/
   - etc/
   - sbin/
   - home/
   - var/
   - usr/
   -  bin/
   -  sbin/
   - tmp

---

-> Аттрибуты процесса <-
=========================================
 * Файловые дескрипторы
 * cwd
 * Таблица файловых дескрипторов per process
 * Глобальная таблица открытых файлов
 * Глобальная таблица vnode

-> Файловые системы <-
======================
 * VFS
 * Сетевые
 * Виртуальные
 * In memory
 * On disk
 * Userspace - FUSE
 * Точки монтирования

-> Проход по пути <-
====================
 * path - /path/to/some/file
 * Рекурсивный процесс
 * Начинаем с корня с inode 2, pathIndex - 0
    - Ищем запись директории с именем path[pathIndex]
    - inode - inode найденной записи
    - ++pathIndex
 * namei(name-inode) cache

-> Алгоритмы элеватора <-
=========================
  * FIFO
  * SSTF - Shortest Seek Time First
  * SCAN 
  * https://slideplayer.com/slide/5209336/

---

-> Системные вызовы <-
======================
  * creat, open, close, unlink
  * chdir, getcwd
  * read, write,  lseek
  * scattered, gathered IO
  * chmod, chown
  * getdents, mkdir, rmdir
  * mount, umount
  * cwd у процесса
  * Common pitfalls
    - Утечка дескрипторов
    - TOCTOU уязвимости и как правильно? openat, etc.
